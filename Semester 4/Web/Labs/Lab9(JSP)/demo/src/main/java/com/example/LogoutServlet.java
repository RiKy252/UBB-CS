package com.example;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import com.example.utils.DatabaseUtil;

@WebServlet("/LogoutServlet")
public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("user");
        
        if (username != null) {
            try {
                // Update user's playing status in database
                Connection conn = DatabaseUtil.getConnection();
                String sql = "UPDATE users SET is_playing = 0 WHERE username = ?";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.executeUpdate();
                pstmt.close();
                conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
        session.invalidate();
        response.sendRedirect("login.jsp");
    }
}