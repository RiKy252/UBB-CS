<?php
    require 'db.php';

    $country = $_GET['country'] ?? '';
    $page = max(1, intval($_GET['page'] ?? 1));
    $limit = 4;
    $offset = ($page - 1) * $limit;

    $sql = "SELECT * FROM destinations WHERE country LIKE ? LIMIT ? OFFSET ?";
    $stmt = $conn->prepare($sql);
    $like = "%$country%";
    $stmt->bind_param('sii', $like, $limit, $offset);
    $stmt->execute();
    $result = $stmt->get_result();

    $destinations = [];
    while ($row = $result->fetch_assoc()) {
        $destinations[] = $row;
    }

    echo json_encode(['destinations' => $destinations, 'page' => $page]);
?>