<?php
require 'db.php';
require 'auth.php';
requireLogin();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $roomId = $_POST['roomId'];
    $checkIn = $_POST['checkIn'];
    $checkOut = $_POST['checkOut'];
    $guests = $_POST['guests'];
    $userId = $_SESSION['user_id'];

    // Check for overlapping reservation
    $overlap = $pdo->prepare("SELECT * FROM Reservation WHERE userId = ? 
        AND NOT (checkOutDate <= ? OR checkInDate >= ?)");
    $overlap->execute([$userId, $checkIn, $checkOut]);

    if ($overlap->rowCount() > 0) {
        die("You already have a reservation that overlaps.");
    }

    // Count reservations in the range
    $roomCount = $pdo->query("SELECT COUNT(*) FROM HotelRoom")->fetchColumn();
    $booked = $pdo->prepare("SELECT COUNT(*) FROM Reservation 
        WHERE NOT (checkOutDate <= ? OR checkInDate >= ?)");
    $booked->execute([$checkIn, $checkOut]);
    $bookedCount = $booked->fetchColumn();

    $stmt = $pdo->prepare("SELECT basePrice FROM HotelRoom WHERE id = ?");
    $stmt->execute([$roomId]);
    $basePrice = $stmt->fetchColumn();

    $rate = 1.0;
    $occupancy = $bookedCount / $roomCount;
    if ($occupancy > 0.8) $rate = 1.5;
    elseif ($occupancy > 0.5) $rate = 1.2;

    $days = (strtotime($checkOut) - strtotime($checkIn)) / 86400;
    $totalPrice = $basePrice * $rate * $days;

    $insert = $pdo->prepare("INSERT INTO Reservation 
        (userId, roomId, checkInDate, checkOutDate, numberOfGuests, totalPrice) 
        VALUES (?, ?, ?, ?, ?, ?)");
    $insert->execute([$userId, $roomId, $checkIn, $checkOut, $guests, $totalPrice]);

    echo "Reservation successful. Total price: $totalPrice";
}
?>

<form method="POST">
    Room ID: <input name="roomId" required><br>
    Check-In: <input type="date" name="checkIn" required><br>
    Check-Out: <input type="date" name="checkOut" required><br>
    Guests: <input name="guests" type="number" required><br>
    <button>Reserve</button>
</form>
