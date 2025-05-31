package com.example;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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
    private static final int SHIP_SIZE = 2;
    private Random random = new Random();
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("user");
        
        if (username == null) {
            response.getWriter().write("Not logged in");
            return;
        }

        String action = request.getParameter("action");
        if ("getBoardState".equals(action)) {
            getBoardState(request, response, username);
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
                    
                    // Place ships randomly for both players
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
            sql = "SELECT * FROM moves WHERE game_id = ? AND player = ? AND row = ? AND col = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, username);
            pstmt.setInt(3, rowInt);
            pstmt.setInt(4, colInt);
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
            
            sql = "SELECT COUNT(DISTINCT s.row, s.col) as hits FROM ships s " +
                  "JOIN moves m ON s.game_id = m.game_id AND s.row = m.row AND s.col = m.col " +
                  "WHERE s.game_id = ? AND s.player = ? AND m.player = ? AND m.is_hit = true";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, opponent);
            pstmt.setString(3, username);
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
        String sql = "INSERT INTO ships (game_id, player, row, col) VALUES (?, ?, ?, ?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        
        Random random = new Random();

        for (int ship = 0; ship < SHIPS_PER_PLAYER; ship++) {
            boolean placed = false;
            while (!placed) {
                // Try to place ship horizontally or vertically
                boolean isHorizontal = random.nextBoolean();
                int row, col;

                if (isHorizontal) {
                    row = random.nextInt(BOARD_SIZE);
                    col = random.nextInt(BOARD_SIZE - SHIP_SIZE + 1);
                } else {
                    row = random.nextInt(BOARD_SIZE - SHIP_SIZE + 1);
                    col = random.nextInt(BOARD_SIZE);
                }
                
                // Check if space is available
                boolean spaceAvailable = true;
                for (int i = 0; i < SHIP_SIZE; i++) {
                    int checkRow = isHorizontal ? row : row + i;
                    int checkCol = isHorizontal ? col + i : col;

                    String checkSql = "SELECT COUNT(*) FROM ships WHERE game_id = ? AND player = ? AND row = ? AND col = ?";
                    PreparedStatement checkStmt = null; // Initialize to null
                    ResultSet rsCheck = null; // Use a different variable name
                    try {
                         checkStmt = conn.prepareStatement(checkSql);
                         checkStmt.setInt(1, gameId);
                         checkStmt.setString(2, player);
                         checkStmt.setInt(3, checkRow);
                         checkStmt.setInt(4, checkCol);
                         rsCheck = checkStmt.executeQuery();
                         rsCheck.next();
                         if (rsCheck.getInt(1) > 0) {
                             spaceAvailable = false;
                             break;
                         }
                    } finally {
                        if (rsCheck != null) try { rsCheck.close(); } catch (Exception e) {} // Close ResultSet
                        if (checkStmt != null) try { checkStmt.close(); } catch (Exception e) {} // Close PreparedStatement
                    }
                }
                
                if (spaceAvailable) {
                    // Place the ship
                    for (int i = 0; i < SHIP_SIZE; i++) {
                         int placeRow = isHorizontal ? row : row + i;
                         int placeCol = isHorizontal ? col + i : col;
                        pstmt.setInt(1, gameId);
                        pstmt.setString(2, player);
                        pstmt.setInt(3, placeRow);
                        pstmt.setInt(4, placeCol);
                        pstmt.executeUpdate();
                    }
                    placed = true;
                }
            }
        }
        if (pstmt != null) try { pstmt.close(); } catch (Exception e) {} // Close PreparedStatement after loop
    }

    private void getBoardState(HttpServletRequest request, HttpServletResponse response, String username) 
            throws IOException {
         Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            
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
            
            int gameId = rs.getInt("id");
            String opponent = username.equals(rs.getString("player1")) ? rs.getString("player2") : rs.getString("player1");
            
            StringBuilder boardState = new StringBuilder();
            
            // Get player's ships
            sql = "SELECT row, col FROM ships WHERE game_id = ? AND player = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, username);
            rs = pstmt.executeQuery();
            
            System.out.println("Getting ships for player: " + username + " in game: " + gameId);
            while (rs.next()) {
                int row = rs.getInt("row");
                int col = rs.getInt("col");
                String shipData = "ship," + row + "," + col + ";";
                boardState.append(shipData);
                System.out.println("Found ship at: " + row + "," + col);
            }

            // Get opponent's moves
            sql = "SELECT row, col, is_hit FROM moves WHERE game_id = ? AND player = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, gameId);
            pstmt.setString(2, opponent);
            rs = pstmt.executeQuery();
            
            System.out.println("Getting moves for opponent: " + opponent + " in game: " + gameId);
            while (rs.next()) {
                int row = rs.getInt("row");
                int col = rs.getInt("col");
                boolean isHit = rs.getBoolean("is_hit");
                String moveData = "move," + row + "," + col + "," + isHit + ";";
                boardState.append(moveData);
                System.out.println("Found move at: " + row + "," + col + " isHit: " + isHit);
            }
            
            String finalState = boardState.toString();
            System.out.println("Final board state: " + finalState);
            response.getWriter().write(finalState);
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().write("Error getting board state: " + e.getMessage());
        } finally {
            if (rs != null) try { rs.close(); } catch (Exception e) {}
            if (pstmt != null) try { pstmt.close(); } catch (Exception e) {}
            if (conn != null) try { conn.close(); } catch (Exception e) {}
        }
    }
}