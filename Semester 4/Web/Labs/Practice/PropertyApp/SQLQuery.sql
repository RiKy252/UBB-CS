CREATE TABLE Users (
    userId INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    secretQuestion VARCHAR(255) NOT NULL,
    secretAnswer VARCHAR(255) NOT NULL
);

CREATE TABLE Property(
    propertyId INT AUTO_INCREMENT PRIMARY KEY,
    propertyAddress VARCHAR(255) NOT NULL,
    propertyDescription VARCHAR(255) NOT NULL 
);

CREATE TABLE UserToProperties(
    userToPropertiesId INT AUTO_INCREMENT PRIMARY KEY,
    userId int not null,
    propertyId int not null,
    FOREIGN KEY (userId) REFERENCES Users(userId),
    FOREIGN KEY (propertyId) REFERENCES Property(propertyId)
);

INSERT INTO Users (username, secretQuestion, secretAnswer) VALUES ('Alex', 'How are you?', 'Good'), ('Admin', 'Hoy are you?', 'Bad')
INSERT INTO Property (propertyAddress, propertyDescription) VALUES ('Property Addr 1', 'Property Descr 1'), ('Property Addr 2', 'Property Descr 2'), ('Property Addr 3', 'Property Descr 3')
INSERT INTO UserToProperties (userId, propertyId) VALUES (1, 1), (2, 2), (2, 3)
