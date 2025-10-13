<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }

    if (isset($_POST['popular'])) {
        $count = array_count_values($_SESSION['search_log'] ?? []);
        arsort($count);
        $mostPopular = array_key_first($count);
        if ($mostPopular) {
            $property = $db->getPropertyById($mostPopular);
            echo "<h3>Most Popular Property</h3>";
            echo "{$property['propertyAddress']} – {$property['propertyDescription']}";
        } else {
            echo "No searches yet.";
        }
        echo "<p><a href='index.php'>Back</a></p>";
        exit;
    }

    $description = $_POST['desc'] ?? '';
    $properties = $db->searchProperties($description);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Property App</title>
</head>
<body>
    <h2>Search result:</h2>
    <?php foreach ($properties as $p): ?>
        <p>ID <?= $p['propertyId'] ?>: <?= $p['propertyAddress'] ?> - <?= $p['propertyDescription'] ?></p>
        <?php $_SESSION['search_log'][] = $p['propertyId'] ?>
    <?php endforeach; ?>
    <p><a href='index.php'>Back</p>
</body>
</html>