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

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            // Get JSON data
            $json = file_get_contents('php://input');
            $data = json_decode($json, true);

            if (!$data) {
                throw new Exception('Invalid JSON data');
            }

            $id = intval($data['id'] ?? 0);
            $location = trim($data['location'] ?? '');
            $country = trim($data['country'] ?? '');
            $description = trim($data['description'] ?? '');
            $targets = trim($data['tourist_targets'] ?? '');
            $cost = floatval($data['cost_per_day'] ?? 0);

            if ($id <= 0) {
                throw new Exception('Invalid destination ID');
            }

            // Server-side validation
            if (!$location || !$country || !$description || !$targets || $cost <= 0) {
                throw new Exception('All fields must be filled correctly');
            }

            $stmt = $conn->prepare("UPDATE destinations SET location=?, country=?, description=?, tourist_targets=?, cost_per_day=? WHERE id=?");
            if (!$stmt) {
                throw new Exception('Database prepare failed: ' . $conn->error);
            }

            $stmt->bind_param('ssssdi', $location, $country, $description, $targets, $cost, $id);
            
            if (!$stmt->execute()) {
                throw new Exception('Failed to execute query: ' . $stmt->error);
            }

            if ($stmt->affected_rows === 0) {
                throw new Exception('Destination not found or no changes made');
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
