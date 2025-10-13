<?php
session_start();
require 'db.php';

// Handle username submission
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['username'])) {
    $_SESSION['username'] = trim($_POST['username']);
    // Fetch user ID
    $stmt = $pdo->prepare("SELECT id FROM User WHERE username = ?");
    $stmt->execute([$_SESSION['username']]);
    $_SESSION['user_id'] = $stmt->fetchColumn();

    // If user doesn't exist in DB, show error
    if (!$_SESSION['user_id']) {
        echo "<p>User not found in database.</p>";
        session_destroy();
        exit;
    }

    header("Location: index.php");
    exit;
}

// If not logged in, show login form and exit
if (!isset($_SESSION['username'])) {
    ?>
    <form method="POST">
        <label>Enter your username:</label>
        <input type="text" name="username" required />
        <button type="submit">Continue</button>
    </form>
    <?php
    exit;
}

// User is logged in — continue
if (!isset($_SESSION['cart'])) {
    $_SESSION['cart'] = [];
}

// Add to cart
if (isset($_GET['add'])) {
    $_SESSION['cart'][] = (int) $_GET['add'];
    header("Location: index.php");
    exit;
}

// Confirm order
if (isset($_POST['confirm'])) {
    $cart = $_SESSION['cart'];
    if (empty($cart)) {
        echo "<p>Your cart is empty!</p>";
    } else {
        $placeholders = implode(',', array_fill(0, count($cart), '?'));
        $stmt = $pdo->prepare("SELECT * FROM Products WHERE id IN ($placeholders)");
        $stmt->execute($cart);
        $products = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $total = 0;
        $categoryCount = [];
        foreach ($products as $product) {
            $total += $product['price'];
            $category = explode('-', $product['name'])[0];
            $categoryCount[$category] = ($categoryCount[$category] ?? 0) + 1;
        }

        $discount = 0;
        if (count($products) >= 3) $discount += 10;
        if (max($categoryCount) >= 2) $discount += 5;
        if ($discount > 15) $discount = 15;

        $finalTotal = round($total * (1 - $discount / 100), 2);

        $stmt = $pdo->prepare("INSERT INTO `Order` (userId, totalPrice) VALUES (?, ?)");
        $stmt->execute([$_SESSION['user_id'], $finalTotal]);
        $orderId = $pdo->lastInsertId();

        foreach ($cart as $productId) {
            $stmt = $pdo->prepare("INSERT INTO OrderItem (orderId, productId) VALUES (?, ?)");
            $stmt->execute([$orderId, $productId]);
        }

        echo "<p>Order confirmed! Total: $$finalTotal (Discount: $discount%)</p>";
        $_SESSION['cart'] = [];
    }
}

// Display product list
echo "<h2>Welcome, {$_SESSION['username']}!</h2>";
echo "<h3>Available Products:</h3>";
$stmt = $pdo->query("SELECT * FROM Products");
foreach ($stmt as $product) {
    echo "{$product['name']} - \${$product['price']} 
          <a href='?add={$product['id']}'>Add to Cart</a><br>";
}

// Show cart
echo "<h3>Your Cart:</h3>";
if (!empty($_SESSION['cart'])) {
    $placeholders = implode(',', array_fill(0, count($_SESSION['cart']), '?'));
    $stmt = $pdo->prepare("SELECT * FROM Products WHERE id IN ($placeholders)");
    $stmt->execute($_SESSION['cart']);
    $products = $stmt->fetchAll(PDO::FETCH_ASSOC);

    $total = 0;
    foreach ($products as $product) {
        echo "{$product['name']} - \${$product['price']}<br>";
        $total += $product['price'];
    }

    echo "<p>Total before discount: \$$total</p>";
    echo "<form method='POST'><button name='confirm'>Confirm Order</button></form>";
} else {
    echo "<p>Your cart is empty.</p>";
}
?>
