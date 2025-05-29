package com.example;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/GameServlet")
public class GameServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Placeholder for handling moves
        String user = (String) request.getSession().getAttribute("user");
        if (user == null) {
            response.getWriter().write("Not logged in.");
            return;
        }

        String row = request.getParameter("row");
        String col = request.getParameter("col");

        // Process move
        response.getWriter().write("Move registered at: " + row + ", " + col);
    }
}