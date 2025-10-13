<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $customer = $_SESSION['user'];
    $feedbacks = $db->getAllFeedbacks();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Feedback App</title>
</head>
<body>
    <?php foreach ($feedbacks as $feedback): ?>
        <?php if ($feedback['customerId'] == $customer['customerId']): ?>
            <p><strong>FeedbackId: <?= $feedback['feedbackId'] ?> -> <?= $feedback['feedbackMessage'] ?></strong></p>
        <?php else: ?>
            <p>FeedbackId: <?= $feedback['feedbackId'] ?> -> <?= $feedback['feedbackMessage'] ?></p>
        <?php endif; ?>
    <?php endforeach; ?>
    <p><a href="index.php">Back</a></p>
</body>
</html>