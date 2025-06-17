<?php
    require 'db.php';
    require 'auth.php';
    requireLogin();

    $stmt = $pdo->prepare("SELECT r.*, h.roomNumber FROM Reservation r 
        JOIN HotelRoom h ON r.roomId = h.id WHERE r.userId = ?");
    $stmt->execute([$_SESSION['user_id']]);
    $reservations = $stmt->fetchAll();

    echo "<h3>Your Reservations</h3>";
    foreach ($reservations as $res) {
        echo "Room: {$res['roomNumber']} | From: {$res['checkInDate']} to {$res['checkOutDate']} | Guests: {$res['numberOfGuests']} | Price: {$res['totalPrice']}<br>";
    }
?>