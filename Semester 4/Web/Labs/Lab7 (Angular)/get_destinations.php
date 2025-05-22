<?php
    // Prevent any output before headers
    ob_start();

    // Set headers
    header('Access-Control-Allow-Origin: *');
    header('Access-Control-Allow-Methods: GET, OPTIONS');
    header('Access-Control-Allow-Headers: Content-Type');
    header('Content-Type: application/json');

    if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
        ob_end_clean();
        exit(0);
    }

    try {
        require 'database.php';

        if ($_SERVER['REQUEST_METHOD'] === 'GET') {
            $country = $_GET['country'] ?? '';
            $page = intval($_GET['page'] ?? 1);
            $limit = 4;
            $offset = ($page - 1) * $limit;

            // First, get total count
            $countSql = "SELECT COUNT(*) as total FROM destinations WHERE country LIKE ?";
            $countStmt = $conn->prepare($countSql);
            if (!$countStmt) {
                throw new Exception('Database prepare failed: ' . $conn->error);
            }

            $like = "%$country%";
            $countStmt->bind_param('s', $like);
            if (!$countStmt->execute()) {
                throw new Exception('Failed to execute count query: ' . $countStmt->error);
            }

            $totalResult = $countStmt->get_result();
            $totalRow = $totalResult->fetch_assoc();
            $total = $totalRow['total'];

            // Then get the paginated results
            $sql = "SELECT * FROM destinations WHERE country LIKE ? LIMIT ? OFFSET ?";
            $stmt = $conn->prepare($sql);
            if (!$stmt) {
                throw new Exception('Database prepare failed: ' . $conn->error);
            }

            $stmt->bind_param('sii', $like, $limit, $offset);
            if (!$stmt->execute()) {
                throw new Exception('Failed to execute query: ' . $stmt->error);
            }

            $result = $stmt->get_result();
            $destinations = [];
            while ($row = $result->fetch_assoc()) {
                $destinations[] = $row;
            }

            $totalPages = ceil($total / $limit);

            ob_end_clean();
            echo json_encode([
                'destinations' => $destinations,
                'page' => $page,
                'totalPages' => $totalPages,
                'total' => $total
            ]);
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