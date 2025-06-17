CREATE TABLE User (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50),
    password VARCHAR(50)
);

CREATE TABLE HotelRoom (
    id INT AUTO_INCREMENT PRIMARY KEY,
    roomNumber VARCHAR(10),
    capacity INT,
    basePrice INT
);

CREATE TABLE Reservation (
    id INT AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    roomId INT,
    checkInDate DATE,
    checkOutDate DATE,
    numberOfGuests INT,
    totalPrice INT,
    FOREIGN KEY (userId) REFERENCES User(id),
    FOREIGN KEY (roomId) REFERENCES HotelRoom(id)
);

-- Insert sample users
INSERT INTO User (username, password) VALUES
('alice', '1234'),
('bob', '5678'),
('charlie', 'pass');

-- Insert sample hotel rooms
INSERT INTO HotelRoom (roomNumber, capacity, basePrice) VALUES
('101', 2, 100),
('102', 2, 100),
('103', 3, 120),
('201', 4, 150),
('202', 2, 100),
('203', 1, 80),
('301', 3, 130),
('302', 4, 160),
('303', 2, 110),
('401', 1, 90);

-- Insert sample reservations
-- Example: Bob has a reservation in Room 101
INSERT INTO Reservation (userId, roomId, checkInDate, checkOutDate, numberOfGuests, totalPrice) VALUES
(2, 1, '2025-06-20', '2025-06-22', 2, 200),
(1, 2, '2025-06-20', '2025-06-23', 2, 300),
(3, 3, '2025-06-21', '2025-06-22', 3, 120),
(1, 4, '2025-06-25', '2025-06-27', 3, 300);

