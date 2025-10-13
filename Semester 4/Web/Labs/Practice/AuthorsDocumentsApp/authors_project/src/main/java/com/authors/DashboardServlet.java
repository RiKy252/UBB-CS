package com.authors;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/work")
public class DashboardServlet extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException {
        int authorId = (int) req.getSession().getAttribute("authorId");

        try (Connection con = DBUtil.getConnection()) {
            PreparedStatement ps = con.prepareStatement("SELECT * FROM Authors WHERE id = ?");
            ps.setInt(1, authorId);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                String[] docIds = rs.getString("documentList").split(",");
                String[] movieIds = rs.getString("movieList").split(",");

                List<String> results = new ArrayList<>();
                int max = Math.max(docIds.length, movieIds.length);

                for (int i = 0; i < max; i++) {
                    if (i < docIds.length) {
                        PreparedStatement dp = con.prepareStatement("SELECT * FROM Documents WHERE id = ?");
                        dp.setInt(1, Integer.parseInt(docIds[i]));
                        ResultSet drs = dp.executeQuery();
                        if (drs.next()) {
                            results.add("Document: " + drs.getString("name") + " - " + drs.getString("contents"));
                        }
                    }
                    if (i < movieIds.length) {
                        PreparedStatement mp = con.prepareStatement("SELECT * FROM Movies WHERE id = ?");
                        mp.setInt(1, Integer.parseInt(movieIds[i]));
                        ResultSet mrs = mp.executeQuery();
                        if (mrs.next()) {
                            results.add("Movie: " + mrs.getString("title") + " - Duration: " + mrs.getInt("duration"));
                        }
                    }
                }

                req.setAttribute("results", results);
                req.getRequestDispatcher("display.jsp").forward(req, res);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

