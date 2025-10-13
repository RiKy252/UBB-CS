<?php
    class Database {
        private $host = 'localhost';
        private $dbname = 'task_management';
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

        public function getUserByName($username) {
            $stmt = $this->pdo->prepare("SELECT * FROM Users WHERE username = ?");
            $stmt->execute([$username]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function getUserById($userId) {
            $stmt = $this->pdo->prepare("SELECT * FROM Users WHERE userId = ?");
            $stmt->execute([$userId]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function getTasksByStatus($status) {
            $stmt = $this->pdo->prepare("SELECT * FROM Tasks WHERE taskStatus = ?");
            $stmt->execute([$status]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        }

        public function changeTaskStatus($taskId, $status) {
            $stmt = $this->pdo->prepare("UPDATE Tasks SET taskStatus = ?, lastUpdated = ? WHERE taskId = ?");
            $now = date("Y/m/d H:i:s");
            $stmt->execute([$status, $now, $taskId]);
        }

        public function addTaskLogTable($taskId, $userId, $oldStatus, $newStatus) {
            $stmt = $this->pdo->prepare("INSERT INTO TaskLogs (taskId, userId, oldStatus, newStatus, taskLogTimestamp) VALUES (?, ?, ?, ?, ?)");
            $now = date("Y/m/d H:i:s");
            $stmt->execute([$taskId, $userId, $oldStatus, $newStatus, $now]);
            return $this->pdo->lastInsertId();
        }

        public function getTaskById($taskId) {
            $stmt = $this->pdo->prepare("SELECT * FROM Tasks WHERE taskId = ?");
            $stmt->execute([$taskId]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function getTaskLogOfUserMoingTask($userId, $taskId) {
            $stmt = $this->pdo->prepare("SELECT * FROM TaskLogs WHERE taskId = ? AND userId = ? ORDER BY taskLogTimestamp DESC LIMIT 1");
            $stmt->execute([$taskId, $userId]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }

        public function getTaskLogsOfSpecificTask($taskId) {
            $stmt = $this->pdo->prepare("SELECT * FROM Tasklogs WHERE taskId = ?");
            $stmt->execute([$taskId]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }
    }
?>