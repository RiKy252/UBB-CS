package com.example;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Random;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import com.example.utils.DatabaseUtil;

@WebServlet("/GameServlet")
public class GameServlet extends HttpServlet {
    private static final int BOARD_SIZE = 10;
    private static final int SHIPS_PER_PLAYER = 2;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("user");
        
        if (username == null) {
            response.getWriter().write("Not logged in");
            return;
        }

        // Clean up old games
        DatabaseUtil.cleanupOldGames();

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            
            // First, check if this player is already in a game
            String sql = "SELECT * FROM games WHERE (player1 = ? OR player2 = ?) AND status = 'active'";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, username);
            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                // Player is in an active game
                String currentPlayer = rs.getString("current_player");
                if (currentPlayer == null) {
                    response.getWriter().write("Waiting for opponent...");
                } else if (currentPlayer.equals(username)) {
                    response.getWriter().write("Your turn");
                } else {
                    response.getWriter().write("Opponent's turn");
                }
                return;
            }
            
            // Check if there's a waiting game that's not created by this player
            sql = "SELECT * FROM games WHERE status = 'waiting' AND player1 != ? LIMIT 1";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                // Join existing waiting game
                int gameId = rs.getInt("id");
                String player1 = rs.getString("player1");
                
                conn.setAutoCommit(false);
                try {
                    // Update game status
                    sql = "UPDATE games SET player2 = ?, current_player = ?, status = 'active' WHERE id = ?";
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, username);
                    pstmt.setString(2, player1); // First player starts
                    pstmt.setInt(3, gameId);
                    pstmt.executeUpdate();
                    
                    // Place ships for both players
                    placeShips(conn, gameId, player1);
                    placeShips(conn, gameId, username);
                    
                    conn.commit();
                    response.getWriter().write("Opponent's turn");
                } catch (Exception e) {
                    conn.rollback();
                    throw e;
                } finally {
                    conn.setAutoCommit(true);
                }
            } else {
                // Check if this player already has a waiting game
                sql = "SELECT * FROM games WHERE player1 = ? AND status = 'waiting'";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                rs = pstmt.executeQuery();
                
                if (!rs.next()) {
                    // Create new waiting game only if player doesn't have one
                    sql = "INSERT INTO games (player1, status) VALUES (?, 'waiting')";
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, username);
                    pstmt.executeUpdate();
                }
                
                response.getWriter().write("Waiting for opponent...");
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().write("Waiting for opponent...");
        } finally {
            if (rs != null) try { rs.close(); } catch (Exception e) {}
            if (pstmt != null) try { pstmt.close(); } catch (Exception e) {}
            if (conn != null) try { conn.close(); } catch (Exception e) {}
        }
    }
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("user");
        
        if (username == null) {
            response.getWriter().write("Not logged in");
            return;
        }

        String row = request.getParameter("row");
        String col = request.getParameter("col");
        
        if (row == null || col == null || row.trim().isEmpty() || col.trim().isEmpty()) {
            response.getWriter().write("Invalid move");
            return;
        }

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            conn.setAutoCommit(false);
            
            // Get current game
            String sql = "SELECT * FROM games WHERE (player1 = ? OR player2 = ?) AND status = 'active'";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, username);
            rs = pstmt.executeQuery();
            
            if (!rs.next()) {
                response.getWriter().write("No active game");
                return;
            }
            
            String currentPlayer = rs.getString("current_player");
            if (!username.equals(currentPlayer)) {
                response.getWriter().write("Not your turn");
                return;
            }
            
            int gameId = rs.getInt("id");
            String opponent = username.equals(rs.getString("player1")) ? rs.getString("player2") : rs.getString("player1");
            
            // Make the move
            int rowInt = Integer.parseInt(row);
            int colInt = Integer.parseInt(col);
            
            if (rowInt < 0 || rowInt >= BOARD_SIZE || colInt < 0 || colInt >= BOARD_SIZE) {
                response.getWriter().write("Invalid coordinates");
                return;
            }
            
            // Check if move was already made
            sql = "SELECT * FROM moves WHERE game_id = ? AND row = ? AND col = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setInt(2, rowInt);
            pstmt.setInt(3, colInt);
            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                response.getWriter().write("Move already made");
                return;
            }
            
            // Check if hit
            sql = "SELECT * FROM ships WHERE game_id = ? AND player = ? AND row = ? AND col = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, opponent);
            pstmt.setInt(3, rowInt);
            pstmt.setInt(4, colInt);
            rs = pstmt.executeQuery();
            
            boolean isHit = rs.next();
            
            // Record the move
            sql = "INSERT INTO moves (game_id, player, row, col, is_hit) VALUES (?, ?, ?, ?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, username);
            pstmt.setInt(3, rowInt);
            pstmt.setInt(4, colInt);
            pstmt.setBoolean(5, isHit);
            pstmt.executeUpdate();
            
            // Check if game is over
            sql = "SELECT COUNT(*) as total_ships FROM ships WHERE game_id = ? AND player = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, opponent);
            rs = pstmt.executeQuery();
            rs.next();
            int totalShips = rs.getInt("total_ships");
            
            sql = "SELECT COUNT(*) as hits FROM moves WHERE game_id = ? AND player = ? AND is_hit = true";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, username);
            rs = pstmt.executeQuery();
            rs.next();
            int hits = rs.getInt("hits");
            
            if (hits == totalShips) {
                // Game over - current player wins
                sql = "UPDATE games SET status = 'finished', winner = ? WHERE id = ?";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.setInt(2, gameId);
                pstmt.executeUpdate();
                conn.commit();
                response.getWriter().write("Game Over! You won!");
                return;
            }
            
            // Update current player
            sql = "UPDATE games SET current_player = ? WHERE id = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, opponent);
            pstmt.setInt(2, gameId);
            pstmt.executeUpdate();
            
            conn.commit();
            String result = isHit ? "Hit!" : "Miss!";
            response.getWriter().write(result);
        } catch (NumberFormatException e) {
            response.getWriter().write("Invalid coordinates");
        } catch (Exception e) {
            if (conn != null) {
                try {
                    conn.rollback();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
            e.printStackTrace();
            response.getWriter().write("Database error: " + e.getMessage());
        } finally {
            if (rs != null) try { rs.close(); } catch (Exception e) {}
            if (pstmt != null) try { pstmt.close(); } catch (Exception e) {}
            if (conn != null) try { conn.close(); } catch (Exception e) {}
        }
    }

    private void placeShips(Connection conn, int gameId, String player) throws Exception {
        Random random = new Random();
        int shipsPlaced = 0;
        
        while (shipsPlaced < SHIPS_PER_PLAYER) {
            int row = random.nextInt(BOARD_SIZE);
            int col = random.nextInt(BOARD_SIZE);
            
            // Try to place a ship of length 2
            if (col + 1 < BOARD_SIZE) {
                // Check if positions are free
                String sql = "SELECT COUNT(*) as count FROM ships WHERE game_id = ? AND player = ? AND ((row = ? AND col = ?) OR (row = ? AND col = ?))";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setInt(1, gameId);
                pstmt.setString(2, player);
                pstmt.setInt(3, row);
                pstmt.setInt(4, col);
                pstmt.setInt(5, row);
                pstmt.setInt(6, col + 1);
                ResultSet rs = pstmt.executeQuery();
                
                if (rs.next() && rs.getInt("count") == 0) {
                    // Place ship
                    sql = "INSERT INTO ships (game_id, player, row, col) VALUES (?, ?, ?, ?), (?, ?, ?, ?)";
                    pstmt = conn.prepareStatement(sql);
                    pstmt.setInt(1, gameId);
                    pstmt.setString(2, player);
                    pstmt.setInt(3, row);
                    pstmt.setInt(4, col);
                    pstmt.setInt(5, gameId);
                    pstmt.setString(6, player);
                    pstmt.setInt(7, row);
                    pstmt.setInt(8, col + 1);
                    pstmt.executeUpdate();
                    shipsPlaced++;
                }
                
                rs.close();
                pstmt.close();
            }
        }
    }
}