<?php
class Database {
    private $host = 'localhost';
    private $dbname = 'order_management';
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
            die("Database connection failed: " . $e->getMessage());
        }
    }

    public function getConnection() {
        return $this->pdo;
    }
    
    public function getUserByUsername($username) {
        $stmt = $this->pdo->prepare("SELECT * FROM User WHERE username = ?");
        $stmt->execute([$username]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }
    
    public function getAllProducts() {
        $stmt = $this->pdo->query("SELECT * FROM Product ORDER BY name");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function getProductById($id) {
        $stmt = $this->pdo->prepare("SELECT * FROM Product WHERE id = ?");
        $stmt->execute([$id]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }
    
    public function createOrder($userId, $totalPrice) {
        $stmt = $this->pdo->prepare("INSERT INTO `Order` (userId, totalPrice) VALUES (?, ?)");
        $stmt->execute([$userId, $totalPrice]);
        return $this->pdo->lastInsertId();
    }
    
    public function createOrderItem($orderId, $productId) {
        $stmt = $this->pdo->prepare("INSERT INTO OrderItem (orderId, productId) VALUES (?, ?)");
        $stmt->execute([$orderId, $productId]);
    }
    
    public function getLastThreeOrders($userId) {
        $stmt = $this->pdo->prepare("
            SELECT o.id, o.totalPrice, o.createdAt 
            FROM `Order` o 
            WHERE o.userId = ? 
            ORDER BY o.createdAt DESC 
            LIMIT 3
        ");
        $stmt->execute([$userId]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function getOrderItems($orderId) {
        $stmt = $this->pdo->prepare("
            SELECT oi.*, p.name, p.price 
            FROM OrderItem oi 
            JOIN Product p ON oi.productId = p.id 
            WHERE oi.orderId = ?
        ");
        $stmt->execute([$orderId]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
}
?>
