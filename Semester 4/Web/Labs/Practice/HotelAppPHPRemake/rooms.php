<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $user = $_SESSION['user'];
    if (isset($_POST['checkIn']) && isset($_POST['checkOut'])) {
        $_SESSION['checkInDate'] = $_POST['checkIn'];
        $_SESSION['checkOutDate'] = $_POST['checkOut'];
        $checkInDate = $_SESSION['checkInDate'];
        $checkOutDate = $_SESSION['checkOutDate'];
        $rooms = $db->viewAvailableRooms($checkInDate, $checkOutDate);
        echo "<h3>Available Rooms:</h3>";
        foreach ($rooms as $room) {
            echo "<p>Room {$room['roomNumber']} (Capacity: {$room['capacity']}, Base Price: {$room['basePrice']})<br></p>";
            echo "<form method='POST'>
                <input type='hidden' name='roomId' value='{$room['roomId']}'>
                Number of persons: <input type='text' name='numberOfPersons'>
                <input type='submit' name='reserveRoom' value='Reserve Room'>
            </form>";
        }
    }
    if (isset($_POST['reserveRoom'])) {
        $roomId = (int)$_POST['roomId'];
        $room = $db->getRoomById($roomId);
        $guests = (int)$_POST['numberOfPersons'];

        $checkInDate = $_SESSION['checkInDate'];
        $checkOutDate = $_SESSION['checkOutDate'];

        $totalPrice = $db->calculateTotalPrice($checkInDate, $checkOutDate, $roomId);

        $db->makeReservation($user['userId'], $roomId, $checkInDate, $checkOutDate, $guests, $totalPrice);
        echo "Reservation successful. Total price: $totalPrice";
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
    <form method="POST">
        Check-In: <input type="date" name="checkIn" required>
        Check-Out: <input type="date" name="checkOut" required>
        <input type="submit" value="Search">
    </form>
    <p><a href="index.php">Back</a></p>
</body>
</html>