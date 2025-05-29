package com.example.utils;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class DatabaseUtil {
    private static final String URL = "jdbc:mysql://localhost:3306/battleships?useSSL=false&serverTimezone=UTC";
    private static final String USER = "root";
    private static final String PASSWORD = "";

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            initializeTables();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }

    private static void initializeTables() {
        try (Connection conn = getConnection()) {
            // Drop existing tables if they exist
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("DROP TABLE IF EXISTS moves");
                stmt.execute("DROP TABLE IF EXISTS ships");
                stmt.execute("DROP TABLE IF EXISTS games");
                stmt.execute("DROP TABLE IF EXISTS users");
            }

            // Create users table
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("CREATE TABLE users (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "username VARCHAR(50) UNIQUE NOT NULL," +
                    "password VARCHAR(50) NOT NULL," +
                    "is_playing BOOLEAN DEFAULT FALSE," +
                    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP" +
                    ")");
                
                // Insert default users with passwords
                stmt.execute("INSERT INTO users (username, password) VALUES ('player1', 'pass1')");
                stmt.execute("INSERT INTO users (username, password) VALUES ('player2', 'pass2')");
            }

            // Create games table
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("CREATE TABLE games (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "player1 VARCHAR(50) NOT NULL," +
                    "player2 VARCHAR(50)," +
                    "current_player VARCHAR(50)," +
                    "status ENUM('waiting', 'active', 'finished') DEFAULT 'waiting'," +
                    "winner VARCHAR(50)," +
                    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP," +
                    "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP," +
                    "FOREIGN KEY (player1) REFERENCES users(username)," +
                    "FOREIGN KEY (player2) REFERENCES users(username)," +
                    "FOREIGN KEY (current_player) REFERENCES users(username)," +
                    "FOREIGN KEY (winner) REFERENCES users(username)" +
                    ")");
            }

            // Create ships table
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("CREATE TABLE ships (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "game_id INT NOT NULL," +
                    "player VARCHAR(50) NOT NULL," +
                    "row INT NOT NULL," +
                    "col INT NOT NULL," +
                    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP," +
                    "FOREIGN KEY (game_id) REFERENCES games(id) ON DELETE CASCADE," +
                    "FOREIGN KEY (player) REFERENCES users(username)" +
                    ")");
            }

            // Create moves table
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("CREATE TABLE moves (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "game_id INT NOT NULL," +
                    "player VARCHAR(50) NOT NULL," +
                    "row INT NOT NULL," +
                    "col INT NOT NULL," +
                    "is_hit BOOLEAN NOT NULL," +
                    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP," +
                    "FOREIGN KEY (game_id) REFERENCES games(id) ON DELETE CASCADE," +
                    "FOREIGN KEY (player) REFERENCES users(username)" +
                    ")");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void cleanupOldGames() {
        try (Connection conn = getConnection()) {
            // Delete games older than 1 hour
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("DELETE FROM games WHERE created_at < DATE_SUB(NOW(), INTERVAL 1 HOUR)");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void closeConnection(Connection conn) {
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
} 