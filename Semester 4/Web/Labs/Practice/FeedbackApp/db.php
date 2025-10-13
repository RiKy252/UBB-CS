<?php
    class Database {
        private $host = 'localhost';
        private $dbname = 'feedback_app';
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

        public function getCustomerByName($name) {
            $stmt = $this->pdo->prepare("SELECT * FROM Customers WHERE customerName = ?");
            $stmt->execute([$name]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function checkCredentials($name, $email) {
            $stmt = $this->pdo->prepare("SELECT * FROM Customers WHERE customerName = ? AND customerEmail = ?");
            $stmt->execute([$name, $email]);
            $user = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($user) {
                return true;
            }
            return false;
        }

        public function getAllFeedbacks() {
            return $this->pdo->query("SELECT * FROM Feedbacks");
        }

        public function getAllBlockedWords() {
            return $this->pdo->query("SELECT * FROM BlockedWords");
        }

        public function addNewFeedback($customerId, $feedbackMessage) {
            $stmt = $this->pdo->prepare("INSERT INTO Feedbacks (customerId, feedbackMessage) VALUES (?, ?)");
            $stmt->execute([$customerId, $feedbackMessage]);
            return $this->pdo->lastInsertId();
        }

    }
?>