<?php
include 'db.php';
if (!isset($_SESSION['user'])) {
    header('Location: login.php');
    exit;
}
$user = $_SESSION['user'];
?>

<h1>Welcome, <?= htmlspecialchars($user['name']) ?></h1>

<form method="post" action="search.php">
    <input type="text" name="desc" placeholder="Search description">
    <input type="submit" value="Search">
</form>

<form method="post" action="add_property.php">
    <h3>Add Property</h3>
    <input name="address" placeholder="Address">
    <input name="description" placeholder="Description">
    <input type="submit" value="Add Property">
</form>

<form method="post" action="delete_property.php">
    <h3>Delete Property by ID</h3>
    <input name="property_id" placeholder="Property ID" required>
    <input type="submit" value="Delete">
</form>

<form method="post" action="multi_owner.php">
    <input type="submit" value="Show Properties with Multiple Owners">
</form>

<form method="post" action="search.php">
    <input type="hidden" name="popular" value="1">
    <input type="submit" value="Most Popular Searched Property This Session">
</form>

<p><a href="logout.php">Logout</a></p>
