<?php 
    include 'db.php';
    session_start();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $db = new Database();
    $user = $_SESSION['user'];
    $userProps = $db->getUserProperties($user['userId']);
    if (isset($_POST['delete_property'])) {
        $propertyId = (int)$_POST['property_id'];
        $db->deleteUserProperty($user['userId'], $propertyId);
        if ($db->checkUselessProperty($propertyId))
            $db->deleteProperty($propertyId);
        header('Location: delete_property.php');
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Property App</title>
</head>
<body>
    <h2>Here are your owned properties:</h2>
    <?php foreach ($userProps as $p): ?>
        <p>ID <?= $p['propertyId'] ?>: <?= $p['propertyAddress'] ?> - <?= $p['propertyDescription'] ?></p>
        <form method="POST">
            <input type="hidden" name="property_id" value="<?= $p['propertyId'] ?>">
            <input type="submit" name="delete_property" value="Delete Property">
        </form>
    <?php endforeach; ?>
    <p><a href='index.php'>Back</p>
</body>
</html>
