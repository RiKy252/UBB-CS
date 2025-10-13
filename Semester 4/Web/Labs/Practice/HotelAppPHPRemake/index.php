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
    <title>Hotel App</title>
</head>
<body>
    <h1>Welcome, <?= htmlspecialchars($user['username']) ?></h1>
    <p><a href="rooms.php">View available rooms</p>
    <p><a href="reservations.php">View your reservations</p>
    <p><a href="guests.php">Guests in a specific day</p>
    <p><a href="logout.php">Logout</a></p>
</body>
</html>