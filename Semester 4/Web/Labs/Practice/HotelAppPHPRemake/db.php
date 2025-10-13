<?php
    class Database {
        private $host = 'localhost';
        private $dbname = 'hotel_res';
        private $username = 'root';
        private $password = '';
        private $pdo;

        public function __construct() {
            try {
                $this->pdo = new PDO(
                    "mysql:host={$this->host};dbname={$this->dbname};charset=utf8",
                    $this->username,
                    $this->password,
                    [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]
                );
            } catch (PDOException $e) {
                die("Connection failed: " . $e->getMessage());
            }
        }

        public function getUserByName($name) {
            $stmt = $this->pdo->prepare("SELECT * FROM Users WHERE username = ?");
            $stmt->execute([$name]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function getRoomById($id) {
            $stmt = $this->pdo->prepare("SELECT * FROM HotelRooms WHERE roomId = ?");
            $stmt->execute([$id]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function makeReservation($userId, $roomId, $checkIn, $checkOut, $guests, $price) {
            $stmt = $this->pdo->prepare("INSERT INTO Reservations (userId, roomId, checkInDate, checkOutDate, numberOfGuests, totalPrice) VALUES (?, ?, ?, ?, ?, ?)");
            $stmt->execute([$userId, $roomId, $checkIn, $checkOut, $guests, $price]);
            return $this->pdo->lastInsertId();
        }

        public function calculateTotalPrice($checkIn, $checkOut, $roomId) {
            $roomCount = $this->pdo->query("SELECT COUNT(*) FROM HotelRooms")->fetchColumn();  
            $booked = $this->pdo->prepare("SELECT COUNT(*) FROM Reservations 
                                        WHERE NOT (checkOutDate <= ? OR checkInDate >= ?)");
            $booked->execute([$checkIn, $checkOut]);
            $bookedCount = $booked->fetchColumn();
            $stmt = $this->pdo->prepare("SELECT basePrice FROM HotelRooms WHERE roomId = ?");
            $stmt->execute([$roomId]);
            $basePrice = $stmt->fetchColumn();
            $rate = 1.0;
            $occupancy = $bookedCount / $roomCount;
            if ($occupancy > 0.8) $rate = 1.5;
            elseif ($occupancy > 0.5) $rate = 1.2;

            $days = (strtotime($checkOut) - strtotime($checkIn)) / 86400;
            $totalPrice = $basePrice * $rate * $days;
            return $totalPrice;
        }

        public function getUsersReservations($userId) {
            $stmt = $this->pdo->prepare("SELECT * FROM Reservations WHERE userId = ?");
            $stmt->execute([$userId]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        }

        public function guestsStayingInADay($dayDate) {
            $stmt = $this->pdo->prepare("SELECT SUM(numberOfGuests) FROM Reservations 
                                         WHERE checkInDate <= ? AND checkOutDate > ?");
            $stmt->execute([$dayDate, $dayDate]);
            return $stmt->fetchColumn();
        }

        public function checkCredentials($name, $password) {
            $stmt = $this->pdo->prepare("SELECT * FROM Users WHERE username = ? AND password = ?");
            $stmt->execute([$name, $password]);
            $user = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($user) {
                return true;
            }
            return false;
        }

        public function viewAvailableRooms($checkIn, $checkOut) {
            $stmt = $this->pdo->prepare("SELECT *
                                         FROM HotelRooms 
                                         WHERE roomId NOT IN 
                                         (SELECT roomId 
                                         from Reservations
                                        WHERE checkInDate < ? AND checkOutDate > ?)");
            $stmt->execute([$checkOut, $checkIn]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        }
    }
?>