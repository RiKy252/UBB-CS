<?php
class Database {
    private $host = 'localhost';
    private $dbname = 'propertyapp';
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

    public function searchProperties($desc) {
        $stmt = $this->pdo->prepare("SELECT * FROM Property WHERE propertyDescription LIKE ?");
        $stmt->execute(["%$desc%"]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    public function getPropertyById($id) {
        $stmt = $this->pdo->prepare("SELECT * FROM Property WHERE propertyId = ?");
        $stmt->execute([$id]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }

    public function checkUselessProperty($propertyId) {
        $stmt = $this->pdo->prepare("SELECT * FROM UserToProperties WHERE propertyId = ?");
        $stmt->execute([$propertyId]);
        $exists = $stmt->fetch(PDO::FETCH_ASSOC);
        if ($exists)
            return false;
        return true;
    }

    public function checkPropertyExists($addr, $desc) {
        $stmt = $this->pdo->prepare("SELECT propertyId FROM Property WHERE propertyAddress = ? AND propertyDescription = ?");
        $stmt->execute([$addr, $desc]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }

    public function addProperty($address, $description) {
        $stmt = $this->pdo->prepare("INSERT INTO Property (propertyAddress, propertyDescription) VALUES (?, ?)");
        $stmt->execute([$address, $description]);
        return $this->pdo->lastInsertId();
    }

    public function checkLinkingExists($userId, $propertyId) {
        $stmt = $this->pdo->prepare("SELECT * FROM UserToProperties WHERE userId = ? AND propertyId = ?");
        $stmt->execute([$userId, $propertyId]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }

    public function linkUserToProperty($userId, $propertyId) {
        $stmt = $this->pdo->prepare("INSERT INTO UserToProperties (userId, propertyId) VALUES (?, ?)");
        $stmt->execute([$userId, $propertyId]);
    }

    public function deleteProperty($propertyId) {
        $stmt = $this->pdo->prepare("DELETE FROM Property WHERE propertyId = ?");
        $stmt->execute([$propertyId]);
    }

    public function deleteUserProperty($userId, $propertyId) {
        $stmt = $this->pdo->prepare("DELETE FROM UserToProperties WHERE userId = ? AND propertyId = ?");
        $stmt->execute([$userId, $propertyId]);
    }

    public function getUserProperties($userId) {
        $stmt = $this->pdo->prepare("
            SELECT p.* FROM Property p
            JOIN UserToProperties utp ON p.propertyId = utp.propertyId
            WHERE utp.userId = ?
        ");
        $stmt->execute([$userId]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    public function getSharedProperties() {
        $stmt = $this->pdo->query("
            SELECT p.*, COUNT(utp.userId) as owners
            FROM Property p
            JOIN UserToProperties utp ON p.propertyId = utp.propertyId
            GROUP BY p.propertyId
            HAVING owners > 1
        ");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
}
?>
