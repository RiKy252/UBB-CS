CREATE DATABASE IF NOT EXISTS order_management;
USE order_management;

CREATE TABLE User (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE Product (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE `Order` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    userId INT NOT NULL,
    totalPrice DECIMAL(10, 2) NOT NULL,
    createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (userId) REFERENCES User(id)
);

CREATE TABLE OrderItem (
    id INT AUTO_INCREMENT PRIMARY KEY,
    orderId INT NOT NULL,
    productId INT NOT NULL,
    FOREIGN KEY (orderId) REFERENCES `Order`(id),
    FOREIGN KEY (productId) REFERENCES Product(id)
);

INSERT INTO User (username) VALUES 
('john_doe'),
('jane_smith'),
('admin');

INSERT INTO Product (name, price) VALUES 
('BOOK-Mathematics', 25.99),
('BOOK-Physics', 32.50),
('BOOK-Chemistry', 28.75),
('TOY-Car', 15.99),
('TOY-Doll', 12.50),
('TOY-Robot', 45.00),
('ELECTRONICS-Phone', 599.99),
('ELECTRONICS-Laptop', 899.99),
('ELECTRONICS-Headphones', 79.99),
('CLOTHING-Shirt', 19.99),
('CLOTHING-Jeans', 49.99),
('CLOTHING-Jacket', 89.99);
