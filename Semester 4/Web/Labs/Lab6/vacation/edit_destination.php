<?php
require 'db.php';

$id = intval($_GET['id'] ?? 0);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $location = htmlspecialchars(trim($_POST['location']));
    $country = htmlspecialchars(trim($_POST['country']));
    $description = htmlspecialchars(trim($_POST['description']));
    $targets = htmlspecialchars(trim($_POST['tourist_targets']));
    $cost = floatval($_POST['cost_per_day']);

    if (!$location || !$country || !$description || !$targets || $cost <= 0) {
        die("Invalid input.");
    }

    $stmt = $conn->prepare("UPDATE destinations SET location=?, country=?, description=?, tourist_targets=?, cost_per_day=? WHERE id=?");
    $stmt->bind_param("ssssdi", $location, $country, $description, $targets, $cost, $id);
    $stmt->execute();

    header("Location: index.html");
    exit;
}

// GET: Fetch destination to edit
$stmt = $conn->prepare("SELECT * FROM destinations WHERE id = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$result = $stmt->get_result();
$data = $result->fetch_assoc();

if (!$data) {
    die("Destination not found.");
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Edit Destination</title>
</head>
<body>
  <h1>Edit Destination</h1>
  <form action="edit.php?id=<?= $id ?>" method="POST">
    <label>Location (City):</label><br>
    <input type="text" name="location" value="<?= htmlspecialchars($data['location']) ?>" required><br><br>

    <label>Country:</label><br>
    <input type="text" name="country" value="<?= htmlspecialchars($data['country']) ?>" required><br><br>

    <label>Description:</label><br>
    <textarea name="description" required><?= htmlspecialchars($data['description']) ?></textarea><br><br>

    <label>Tourist Targets:</label><br>
    <input type="text" name="tourist_targets" value="<?= htmlspecialchars($data['tourist_targets']) ?>" required><br><br>

    <label>Estimated Cost Per Day ($):</label><br>
    <input type="number" name="cost_per_day" step="0.01" min="0.01" value="<?= $data['cost_per_day'] ?>" required><br><br>

    <input type="submit" value="Update Destination">
  </form>
  <br>
  <a href="index.html">Back to Listing</a>
</body>
</html>
