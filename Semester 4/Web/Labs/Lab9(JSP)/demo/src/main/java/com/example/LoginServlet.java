package com.example;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import com.example.utils.DatabaseUtil;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (username == null || password == null || username.trim().isEmpty() || password.trim().isEmpty()) {
            response.sendRedirect("login.jsp?error=empty");
            return;
        }

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            
            // Check if user exists and password is correct
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                // User exists and password is correct
                HttpSession session = request.getSession();
                session.setAttribute("user", username);
                response.sendRedirect("game.jsp");
            } else {
                // Invalid username or password
                response.sendRedirect("login.jsp?error=invalid");
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("login.jsp?error=database");
        } finally {
            if (rs != null) try { rs.close(); } catch (Exception e) {}
            if (pstmt != null) try { pstmt.close(); } catch (Exception e) {}
            if (conn != null) try { conn.close(); } catch (Exception e) {}
        }
    }
}
