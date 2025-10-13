<?php
    include 'db.php';
    session_start();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    else {
        $customer = $_SESSION['user'];
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Feedback App</title>
</head>
<body>
    <h1>Welcome, <?= htmlspecialchars($customer['customerName']) ?></h1>
    <p><a href="feedback_list.php">View all the feedbacks</p>
    <p><a href="submit_feedback.php">Add a new feedback</p>
    <p><a href="logout.php">Logout</a></p>
</body>
</html>