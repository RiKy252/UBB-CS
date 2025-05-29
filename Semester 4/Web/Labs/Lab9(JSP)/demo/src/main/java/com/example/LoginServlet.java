package com.example;
import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle login logic here
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // Placeholder: Replace with DB check
        if ("player1".equals(username) && "pass".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("game.jsp");
        } else {
            request.setAttribute("error", "Invalid login");
            request.getRequestDispatcher("error.jsp").forward(request, response);
        }
    }
}
