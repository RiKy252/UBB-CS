<?php
    require 'db.php';
    require 'auth.php';
    requireLogin();

    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $date = $_POST['date'];
        $stmt = $pdo->prepare("SELECT SUM(numberOfGuests) FROM Reservation 
            WHERE checkInDate <= ? AND checkOutDate > ?");
        $stmt->execute([$date, $date]);
        $count = $stmt->fetchColumn();
        echo "Total guests on $date: " . ($count ?: 0);
    }
?>

<form method="POST">
    Date: <input type="date" name="date" required>
    <button>Check</button>
</form>
