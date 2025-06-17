package com.authors;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/addDocument")
public class AddDocumentServlet extends HttpServlet {
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String name = req.getParameter("name");
        String contents = req.getParameter("contents");
        int authorId = (int) req.getSession().getAttribute("authorId");

        try (Connection con = DBUtil.getConnection()) {
            // Insert new document
            PreparedStatement insertDoc = con.prepareStatement(
                "INSERT INTO Documents (name, contents) VALUES (?, ?)", Statement.RETURN_GENERATED_KEYS);
            insertDoc.setString(1, name);
            insertDoc.setString(2, contents);
            insertDoc.executeUpdate();

            ResultSet keys = insertDoc.getGeneratedKeys();
            if (keys.next()) {
                int docId = keys.getInt(1);

                // Update Author's documentList
                PreparedStatement getAuthor = con.prepareStatement("SELECT documentList FROM Authors WHERE id = ?");
                getAuthor.setInt(1, authorId);
                ResultSet rs = getAuthor.executeQuery();
                if (rs.next()) {
                    String docList = rs.getString("documentList");
                    if (docList == null || docList.isEmpty()) {
                        docList = String.valueOf(docId);
                    } else {
                        docList += "," + docId;
                    }
                    PreparedStatement updateAuthor = con.prepareStatement("UPDATE Authors SET documentList = ? WHERE id = ?");
                    updateAuthor.setString(1, docList);
                    updateAuthor.setInt(2, authorId);
                    updateAuthor.executeUpdate();
                }
            }
            res.sendRedirect("dashboard.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            res.getWriter().println("Error adding document.");
        }
    }
}

