package com.authors;
import java.sql.Connection;
import java.sql.DriverManager;

public class DBUtil {
    public static Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/author_documents_app";
        String username = "root";
        String password = "";
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, username, password);
    }
}
