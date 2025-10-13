<?php
    require 'db.php';
    require 'auth.php';
    requireLogin();

    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $checkIn = $_POST['checkIn'];
        $checkOut = $_POST['checkOut'];

        // Fetch available rooms
        $sql = "SELECT * FROM HotelRoom WHERE id NOT IN (
                    SELECT roomId FROM Reservation 
                    WHERE NOT (checkOutDate <= ? OR checkInDate >= ?)
                )";
        $stmt = $pdo->prepare($sql);
        $stmt->execute([$checkIn, $checkOut]);
        $available = $stmt->fetchAll();

        echo "<h3>Available Rooms:</h3>";
        foreach ($available as $room) {
            echo "Room {$room['roomNumber']} (Capacity: {$room['capacity']}, Base Price: {$room['basePrice']})<br>";
        }
    }
?>

<form method="POST">
    Check-In: <input type="date" name="checkIn" required>
    Check-Out: <input type="date" name="checkOut" required>
    <button>Search</button>
</form>
