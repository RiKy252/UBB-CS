<?php
    require 'database.php';

    function clean($data) {
        return htmlspecialchars(trim($data));
    }

    $location = clean($_POST['location'] ?? '');
    $country = clean($_POST['country'] ?? '');
    $description = clean($_POST['description'] ?? '');
    $targets = clean($_POST['tourist_targets'] ?? '');
    $cost = floatval($_POST['cost_per_day'] ?? 0);

    if (!$location || !$country || !$description || !$targets || $cost <= 0) {
        die("Invalid input. Please go back and fill all fields correctly.");
    }

    $sql = "INSERT INTO destinations (location, country, description, tourist_targets, cost_per_day)
            VALUES (?, ?, ?, ?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param('ssssd', $location, $country, $description, $targets, $cost);
    $stmt->execute();

    header("Location: index.html");
    exit;
?>