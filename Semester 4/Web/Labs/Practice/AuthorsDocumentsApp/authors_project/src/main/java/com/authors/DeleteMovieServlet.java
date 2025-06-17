package com.authors;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/deleteMovie")
public class DeleteMovieServlet extends HttpServlet {
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        int authorId = (int) req.getSession().getAttribute("authorId");
        String movieIdStr = req.getParameter("movieId");

        try (Connection con = DBUtil.getConnection()) {
            int movieId = Integer.parseInt(movieIdStr);

            // Check if movie exists in author's list
            PreparedStatement getAuthor = con.prepareStatement("SELECT movieList FROM Authors WHERE id = ?");
            getAuthor.setInt(1, authorId);
            ResultSet rs = getAuthor.executeQuery();
            if (rs.next()) {
                String movieList = rs.getString("movieList");
                if (movieList != null && !movieList.isEmpty()) {
                    List<String> movieIds = new ArrayList<>(Arrays.asList(movieList.split(",")));
                    if (movieIds.contains(movieIdStr)) {
                        // Delete movie from Movies table
                        PreparedStatement deleteMovie = con.prepareStatement("DELETE FROM Movies WHERE id = ?");
                        deleteMovie.setInt(1, movieId);
                        deleteMovie.executeUpdate();

                        // Remove from author’s list
                        movieIds.remove(movieIdStr);
                        String updatedList = String.join(",", movieIds);
                        PreparedStatement updateAuthor = con.prepareStatement("UPDATE Authors SET movieList = ? WHERE id = ?");
                        updateAuthor.setString(1, updatedList);
                        updateAuthor.setInt(2, authorId);
                        updateAuthor.executeUpdate();

                        res.sendRedirect("dashboard.jsp");
                        return;
                    }
                }
            }

            res.getWriter().println("Movie not found or not authored by you.");
        } catch (Exception e) {
            e.printStackTrace();
            res.getWriter().println("Error deleting movie.");
        }
    }
}

