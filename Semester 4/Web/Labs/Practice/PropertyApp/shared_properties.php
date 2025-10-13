<?php 
    include 'db.php';
    session_start();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $db = new Database();
    $properties = $db->getSharedProperties();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Property App</title>
</head>
<body>
    <h2>Shared properties:</h2>
    <?php foreach ($properties as $p): ?>
        <p>ID <?= $p['propertyId'] ?>: <?= $p['propertyAddress'] ?> - <?= $p['propertyDescription'] ?></p>
    <?php endforeach; ?>
    <p><a href='index.php'>Back</p>
</body>
</html>