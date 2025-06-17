<?php
    include 'db.php';
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }

    if (isset($_POST['popular'])) {
        $count = array_count_values($_SESSION['search_log'] ?? []);
        arsort($count);
        $mostPopular = array_key_first($count);
        if ($mostPopular) {
            $stmt = $pdo->prepare("SELECT * FROM Property WHERE id = ?");
            $stmt->execute([$mostPopular]);
            $property = $stmt->fetch();
            echo "<h3>Most Popular Property</h3>";
            echo "{$property['address']} – {$property['description']}";
        } else {
            echo "No searches yet.";
        }
        echo "<p><a href='index.php'>Back</a></p>";
        exit;
    }

    $desc = $_POST['desc'] ?? '';
    $stmt = $pdo->prepare("SELECT * FROM Property WHERE description LIKE ?");
    $stmt->execute(["%$desc%"]);
    $results = $stmt->fetchAll();

    echo "<h3>Search Results</h3>";
    foreach ($results as $p) {
        echo "<p><strong>ID {$p['id']}</strong>: {$p['address']} – {$p['description']}</p>";
        $_SESSION['search_log'][] = $p['id'];
    }
    echo "<p><a href='index.php'>Back</a></p>";
?>
