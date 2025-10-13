<?php
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    if (isset($_POST['guestsInADay'])) {
        $dayDate = $_POST['dayDate'];
        $count = $db->guestsStayingInADay($dayDate);
        echo "{$count} guests in {$dayDate}";
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hotel App1</title>
</head>
<body>
    <form method="POST">
        Date: <input type='date' name='dayDate' required>
        <input type='submit' name='guestsInADay' value='View number of guests for this date'>
    </form>
    <p><a href="index.php">Back</a></p>
</body>
</html>