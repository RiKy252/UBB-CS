package com.authors;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/mostAuthors")
public class MostAuthorsDocument extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        try (Connection con = DBUtil.getConnection()) {
            Map<Integer, Integer> docCount = new HashMap<>();

            // Count how many times each document appears
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT documentList FROM Authors");
            while (rs.next()) {
                String docList = rs.getString("documentList");
                if (docList != null && !docList.isEmpty()) {
                    for (String idStr : docList.split(",")) {
                        int id = Integer.parseInt(idStr.trim());
                        docCount.put(id, docCount.getOrDefault(id, 0) + 1);
                    }
                }
            }

            // Find doc ID with max count
            int maxId = -1;
            int maxCount = -1;
            for (Map.Entry<Integer, Integer> entry : docCount.entrySet()) {
                if (entry.getValue() > maxCount) {
                    maxCount = entry.getValue();
                    maxId = entry.getKey();
                }
            }

            if (maxId != -1) {
                PreparedStatement docQuery = con.prepareStatement("SELECT * FROM Documents WHERE id = ?");
                docQuery.setInt(1, maxId);
                ResultSet docRs = docQuery.executeQuery();
                if (docRs.next()) {
                    req.setAttribute("docId", docRs.getInt("id"));
                    req.setAttribute("docName", docRs.getString("name"));
                    req.setAttribute("docContents", docRs.getString("contents"));
                    req.setAttribute("authorCount", maxCount);
                    req.getRequestDispatcher("mostAuthors.jsp").forward(req, res);
                    return;
                }
            }
            req.setAttribute("error", "No documents found.");
            req.getRequestDispatcher("mostAuthors.jsp").forward(req, res);
        } catch (Exception e) {
            e.printStackTrace();
            req.setAttribute("error", "Error retrieving document with most authors.");
            try {
                req.getRequestDispatcher("mostAuthors.jsp").forward(req, res);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}

