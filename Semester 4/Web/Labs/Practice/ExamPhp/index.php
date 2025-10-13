<?php
session_start();
require_once 'Database.php';

$db = new Database();

if (isset($_POST['login'])) {
    $username = trim($_POST['username']);
    if (!empty($username)) {
        $user = $db->getUserByUsername($username);
        if ($user) {
            $_SESSION['user_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];
            $_SESSION['cart'] = [];
        } else {
            $error = "User not found. Please try again.";
        }
    }
}

if (isset($_GET['logout'])) {
    session_destroy();
    header('Location: index.php');
    exit;
}

if (isset($_POST['add_to_cart']) && isset($_SESSION['user_id'])) {
    $productId = (int)$_POST['product_id'];
    $product = $db->getProductById($productId);
    
    if ($product) {
        $warning = checkCategoryWarning($db, $_SESSION['user_id'], $product['name']);
        
        $_SESSION['cart'][] = $product;
        $success = "Product added to cart!";
        
        if ($warning) {
            $warning_message = $warning;
        }
    }
}

if (isset($_GET['remove_from_cart'])) {
    $index = (int)$_GET['remove_from_cart'];
    if (isset($_SESSION['cart'][$index])) {
        unset($_SESSION['cart'][$index]);
        $_SESSION['cart'] = array_values($_SESSION['cart']);
    }
    header('Location: index.php');
    exit;
}

if (isset($_POST['confirm_order']) && isset($_SESSION['user_id']) && !empty($_SESSION['cart'])) {
    $cart = $_SESSION['cart'];
    $originalTotal = array_sum(array_column($cart, 'price'));
    
    $discounts = calculateDiscounts($cart);
    $finalTotal = $originalTotal - $discounts['total_discount'];
    
    $orderId = $db->createOrder($_SESSION['user_id'], $finalTotal);
    
    foreach ($cart as $product) {
        $db->createOrderItem($orderId, $product['id']);
    }
    
    $order_success = [
        'original_total' => $originalTotal,
        'discounts' => $discounts,
        'final_total' => $finalTotal,
        'order_id' => $orderId
    ];
    
    $_SESSION['cart'] = [];
}

function extractCategory($productName) {
    $parts = explode('-', $productName);
    return $parts[0];
}

function calculateDiscounts($cart) {
    $originalTotal = array_sum(array_column($cart, 'price'));
    $discounts = [
        'quantity_discount' => 0,
        'category_discount' => 0,
        'total_discount' => 0
    ];
    
    if (count($cart) >= 3) {
        $discounts['quantity_discount'] = $originalTotal * 0.10;
    }
    
    $categories = [];
    foreach ($cart as $product) {
        $category = extractCategory($product['name']);
        $categories[] = $category;
    }
    
    $categoryCounts = array_count_values($categories);
    $hasSameCategory = false;
    foreach ($categoryCounts as $count) {
        if ($count >= 2) {
            $hasSameCategory = true;
            break;
        }
    }
    
    if ($hasSameCategory) {
        $discounts['category_discount'] = $originalTotal * 0.05;
    }
    
    $discounts['total_discount'] = $discounts['quantity_discount'] + $discounts['category_discount'];
    
    return $discounts;
}

function checkCategoryWarning($db, $userId, $productName) {
    $category = extractCategory($productName);
    $lastThreeOrders = $db->getLastThreeOrders($userId);
    
    if (count($lastThreeOrders) < 3) {
        return false;
    }
    
    $categoryInAllOrders = true;
    
    foreach ($lastThreeOrders as $order) {
        $orderItems = $db->getOrderItems($order['id']);
        $orderCategories = [];
        
        foreach ($orderItems as $item) {
            $orderCategories[] = extractCategory($item['name']);
        }
        
        if (!in_array($category, $orderCategories)) {
            $categoryInAllOrders = false;
            break;
        }
    }
    
    if ($categoryInAllOrders) {
        return "You have purchased products from the '{$category}' for the pst 3 times. Maybe try smth else?";
    }
    
    return false;
}

$products = $db->getAllProducts();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Order Management System</title>
</head>
<body>
    <div class="container">
        <h1>Order Management System</h1>
        
        <?php if (!isset($_SESSION['user_id'])): ?>
            <!-- Login Form -->
            <div class="login-form">
                <h2>Login</h2>
                <?php if (isset($error)): ?>
                    <div class="message error"><?= htmlspecialchars($error) ?></div>
                <?php endif; ?>
                
                <form method="POST">
                    <div class="form-group">
                        <label for="username">Username:</label>
                        <input type="text" id="username" name="username" required>
                    </div>
                    <input type="submit" name="login" value="Login">
                </form>
            </div>
        <?php else: ?>
            <!-- User Info -->
            <div class="user-info">
                <strong>Welcome, <?= htmlspecialchars($_SESSION['username']) ?>!</strong>
                <a href="?logout=1" style="margin-left: 20px; color: black;">Logout</a>
            </div>
            
            <!-- Messages -->
            <?php if (isset($success)): ?>
                <div class="message success"><?= htmlspecialchars($success) ?></div>
            <?php endif; ?>
            
            <?php if (isset($warning_message)): ?>
                <div class="message warning"><?= htmlspecialchars($warning_message) ?></div>
            <?php endif; ?>
            
            <?php if (isset($order_success)): ?>
                <div class="message success">
                    <h3>Order Confirmed Successfully!</h3>
                    <p><strong>Order ID:</strong> <?= $order_success['order_id'] ?></p>
                    <p><strong>Original Total:</strong> $<?= number_format($order_success['original_total'], 2) ?></p>
                    
                    <?php if ($order_success['discounts']['quantity_discount'] > 0): ?>
                        <p><strong>Quantity Discount (10%):</strong> -$<?= number_format($order_success['discounts']['quantity_discount'], 2) ?></p>
                    <?php endif; ?>
                    
                    <?php if ($order_success['discounts']['category_discount'] > 0): ?>
                        <p><strong>Category Discount (5%):</strong> -$<?= number_format($order_success['discounts']['category_discount'], 2) ?></p>
                    <?php endif; ?>
                    
                    <p><strong>Final Total:</strong> $<?= number_format($order_success['final_total'], 2) ?></p>
                </div>
            <?php endif; ?>
            
            <!-- Products Section -->
            <div class="products-section">
                <h2>Available Products</h2>
                <div class="products-grid">
                    <?php foreach ($products as $product): ?>
                        <div class="product-card">
                            <div class="product-name"><?= htmlspecialchars($product['name']) ?></div>
                            <div class="product-price">$<?= number_format($product['price'], 2) ?></div>
                            <form method="POST" style="display: inline;">
                                <input type="hidden" name="product_id" value="<?= $product['id'] ?>">
                                <input type="submit" name="add_to_cart" value="Add to Cart">
                            </form>
                        </div>
                    <?php endforeach; ?>
                </div>
            </div>
            
            <!-- Cart Section -->
            <div class="cart-section">
                <h2>Shopping Cart</h2>
                
                <?php if (empty($_SESSION['cart'])): ?>
                    <p>Your cart is empty.</p>
                <?php else: ?>
                    <?php foreach ($_SESSION['cart'] as $index => $product): ?>
                        <div class="cart-item">
                            <span>
                                <strong><?= htmlspecialchars($product['name']) ?></strong> - 
                                $<?= number_format($product['price'], 2) ?>
                            </span>
                            <a href="?remove_from_cart=<?= $index ?>" style="color: black; text-decoration: underline;">Remove</a>
                        </div>
                    <?php endforeach; ?>
                    
                    <?php 
                    $cart = $_SESSION['cart'];
                    $originalTotal = array_sum(array_column($cart, 'price'));
                    $discounts = calculateDiscounts($cart);
                    $finalTotal = $originalTotal - $discounts['total_discount'];
                    ?>
                    
                    <div class="cart-total">
                        <p><strong>Original Total:</strong> $<?= number_format($originalTotal, 2) ?></p>
                        
                        <?php if ($discounts['quantity_discount'] > 0): ?>
                            <div class="discount-info">
                                <strong>Quantity Discount (3+ items):</strong> -$<?= number_format($discounts['quantity_discount'], 2) ?>
                            </div>
                        <?php endif; ?>
                        
                        <?php if ($discounts['category_discount'] > 0): ?>
                            <div class="discount-info">
                                <strong>Category Discount (2+ same category):</strong> -$<?= number_format($discounts['category_discount'], 2) ?>
                            </div>
                        <?php endif; ?>
                        
                        <p><strong>Final Total:</strong> $<?= number_format($finalTotal, 2) ?></p>
                        
                        <form method="POST" style="margin-top: 15px;">
                            <input type="submit" name="confirm_order" value="Confirm Order">
                        </form>
                    </div>
                <?php endif; ?>
            </div>
        <?php endif; ?>
    </div>
</body>
</html>
