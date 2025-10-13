<?php
    include 'db.php';
    session_start();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    else {
        $user = $_SESSION['user'];
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Property App</title>
</head>
<body>
    <h1>Welcome, <?= htmlspecialchars($user['username']) ?></h1>

    <form method="post" action="search.php">
        <input type="text" name="desc" placeholder="Search description">
        <input type="submit" value="Search">
    </form>

    <form method="post" action="add_property.php">
        <h3>Add Property</h3>
        <input name="address" placeholder="Address" required>
        <input name="description" placeholder="Description" required>
        <input type="submit" value="Add Property">
    </form>
    <p><a href="delete_property.php">Delete properties</a></p>
    <p><a href="shared_properties.php">View Shared Properties</a></p>
    <form method="post" action="search.php">
        <input type="hidden" name="popular" value="1">
        <input type="submit" value="Most Popular Searched Property This Session">
    </form>
    <p><a href="logout.php">Logout</a></p>
</body>
</html>