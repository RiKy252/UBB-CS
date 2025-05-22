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
            $id = intval($_POST['id'] ?? 0);
            
            if ($id <= 0) {
                throw new Exception('Invalid destination ID');
            }

            $stmt = $conn->prepare("DELETE FROM destinations WHERE id = ?");
            if (!$stmt) {
                throw new Exception('Database prepare failed: ' . $conn->error);
            }

            $stmt->bind_param("i", $id);
            
            if (!$stmt->execute()) {
                throw new Exception('Failed to execute query: ' . $stmt->error);
            }

            if ($stmt->affected_rows === 0) {
                throw new Exception('Destination not found');
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