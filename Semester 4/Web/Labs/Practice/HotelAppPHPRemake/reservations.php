<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $user = $_SESSION['user'];
    $reservations = $db->getUsersReservations($user['userId']);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hotel App</title>
</head>
<body>
    <?php foreach ($reservations as $reservation): ?>
        <p>RoomId: <?= $reservation['roomId'] ?> -- check-in -> <?= $reservation['checkInDate'] ?> - <?= $reservation['checkOutDate'] ?> <- check-out: <?= $reservation['numberOfGuests'] ?> guests. Total price: <?= $reservation['totalPrice'] ?></p>
    <?php endforeach; ?>
    <p><a href="index.php">Back</a></p>
</body>
</html>