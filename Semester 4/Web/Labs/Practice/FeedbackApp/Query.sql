CREATE TABLE Customers (
    customerId INT AUTO_INCREMENT PRIMARY KEY,
    customerName VARCHAR(255) NOT NULL,
    customerEmail VARCHAR(255) NOT NULL
);

CREATE TABLE Feedbacks (
    feedbackId INT AUTO_INCREMENT PRIMARY KEY,
    customerId INT NOT NULL,
    feedbackMessage VARCHAR(255) NOT NULL,
    timestamp datetime,
    FOREIGN KEY (customerId) REFERENCES Customers(customerId)
);

CREATE TABLE BlockedWords (
    blockedWordId INT AUTO_INCREMENT PRIMARY KEY,
    pattern VARCHAR(255) NOT NULL
);

INSERT INTO Customers (customerName, customerEmail) VALUES ('test', 'test@test.com'), ('admin', 'admin@admin.com');
INSERT INTO BlockedWords (pattern) VALUES ('brainless'), ('\b(fool|idiot|stupid)\b');
INSERT INTO Feedbacks (customerId, feedbackMessage) VALUES (1, 'I am so fool'), (1, 'This is a clean fooleash message');
