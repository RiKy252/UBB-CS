package com.authors;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Arrays;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/auth")
public class AuthServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String name = request.getParameter("name");
        String authItem = request.getParameter("authItem");

        try (Connection con = DBUtil.getConnection()) {
            PreparedStatement ps = con.prepareStatement("SELECT * FROM Authors WHERE name = ?");
            ps.setString(1, name);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                String docList = rs.getString("documentList");
                String movieList = rs.getString("movieList");

                boolean valid = false;
                String[] docs = docList != null ? docList.split(",") : new String[0];
                String[] movies = movieList != null ? movieList.split(",") : new String[0];

                for (String d : docs) {
                    if (d.equals(authItem)) valid = true;
                }
                for (String m : movies) {
                    if (m.equals(authItem)) valid = true;
                }

                if (!valid) {
                    // Try matching by document or movie name
                    PreparedStatement dp = con.prepareStatement("SELECT id FROM Documents WHERE name = ?");
                    dp.setString(1, authItem);
                    ResultSet drs = dp.executeQuery();
                    while (drs.next()) {
                        String id = String.valueOf(drs.getInt("id"));
                        if (Arrays.asList(docs).contains(id)) valid = true;
                    }

                    PreparedStatement mp = con.prepareStatement("SELECT id FROM Movies WHERE title = ?");
                    mp.setString(1, authItem);
                    ResultSet mrs = mp.executeQuery();
                    while (mrs.next()) {
                        String id = String.valueOf(mrs.getInt("id"));
                        if (Arrays.asList(movies).contains(id)) valid = true;
                    }
                }

                if (valid) {
                    request.getSession().setAttribute("authorId", rs.getInt("id"));
                    request.getSession().setAttribute("authorName", name);
                    response.sendRedirect("dashboard.jsp");
                } else {
                    request.setAttribute("error", "Authentication failed. Please try again.");
                    request.getRequestDispatcher("index.jsp").forward(request, response);
                }
            } else {
                request.setAttribute("error", "User not found.");
                request.getRequestDispatcher("index.jsp").forward(request, response);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

