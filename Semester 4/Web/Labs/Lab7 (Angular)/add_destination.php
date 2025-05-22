<?php
    // Prevent any output before headers
    ob_start();

    // Set headers
    header('Access-Control-Allow-Origin: *');
    header('Access-Control-Allow-Methods: POST, OPTIONS');
    header('Access-Control-Allow-Headers: Content-Type');
    header('Content-Type: application/json');

    if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
        ob_end_clean();
        exit(0);
    }

    try {
        require 'database.php';

        function clean($data) {
            return trim($data);
        }

        if ($_SERVER["REQUEST_METHOD"] === "POST") {
            // Get JSON data
            $json = file_get_contents('php://input');
            $data = json_decode($json, true);

            if (!$data) {
                throw new Exception('Invalid JSON data');
            }

            $location = clean($data['location'] ?? '');
            $country = clean($data['country'] ?? '');
            $description = clean($data['description'] ?? '');
            $targets = clean($data['tourist_targets'] ?? '');
            $cost = floatval($data['cost_per_day'] ?? 0);

            // Server-side validation
            if (!$location || !$country || !$description || !$targets || $cost <= 0) {
                throw new Exception('All fields must be filled correctly');
            }

            $stmt = $conn->prepare("INSERT INTO destinations (location, country, description, tourist_targets, cost_per_day) VALUES (?, ?, ?, ?, ?)");
            if (!$stmt) {
                throw new Exception('Database prepare failed: ' . $conn->error);
            }

            $stmt->bind_param('ssssd', $location, $country, $description, $targets, $cost);
            
            if (!$stmt->execute()) {
                throw new Exception('Failed to execute query: ' . $stmt->error);
            }

            ob_end_clean();
            echo json_encode(['success' => true]);
            exit;
        } else {
            throw new Exception('Method not allowed');
        }
    } catch (Exception $e) {
        ob_end_clean();
        http_response_code(400);
        echo json_encode(['error' => $e->getMessage()]);
        exit;
    }
?>

<!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="UTF-8">
    <title>Add Vacation Destination</title>
    <script>
        function validateForm() {
        const form = document.forms["addForm"];
        const fields = ["location", "country", "description", "tourist_targets", "cost_per_day"];
        for (let field of fields) {
            if (form[field].value.trim() === "") {
            alert("All fields are required.");
            return false;
            }
        }
        const cost = parseFloat(form["cost_per_day"].value);
        if (isNaN(cost) || cost <= 0) {
            alert("Cost per day must be a positive number.");
            return false;
        }
        return true;
        }
    </script>
    </head>
    <body>
    <h1>Add New Destination</h1>

    <?php if ($success): ?>
        <p style="color: green;">Destination added successfully.</p>
    <?php endif; ?>

    <?php if (!empty($errors)): ?>
        <ul style="color: red;">
        <?php foreach ($errors as $error): ?>
            <li><?= $error ?></li>
        <?php endforeach; ?>
        </ul>
    <?php endif; ?>

    <form name="addForm" method="POST" onsubmit="return validateForm()">
        <label>Location (City):</label><br>
        <input type="text" name="location" required><br><br>

        <label>Country:</label><br>
        <input type="text" name="country" required><br><br>

        <label>Description:</label><br>
        <textarea name="description" required></textarea><br><br>

        <label>Tourist Targets:</label><br>
        <input type="text" name="tourist_targets" required><br><br>

        <label>Estimated Cost Per Day ($):</label><br>
        <input type="number" name="cost_per_day" step="0.01" min="0.01" required><br><br>

        <input type="submit" value="Add Destination">
    </form>

    <br><a href="index.php">Back to Listing</a>
    </body>
</html>