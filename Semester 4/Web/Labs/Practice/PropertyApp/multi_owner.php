<?php
    include 'db.php';
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }

    $stmt = $pdo->query("
        SELECT p.id, p.address, p.description, COUNT(utp.idUser) as owners
        FROM Property p
        JOIN UserToProperties utp ON p.id = utp.idProperty
        GROUP BY p.id
        HAVING owners > 1
    ");

    echo "<h3>Properties with Multiple Owners</h3>";
    foreach ($stmt as $p) {
        echo "<p><strong>ID {$p['id']}</strong>: {$p['address']} – {$p['description']} (Owners: {$p['owners']})</p>";
    }
    echo "<p><a href='index.php'>Back</a></p>";
?>
