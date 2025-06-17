<?php
    include 'db.php';
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $address = $_POST['address'];
    $desc = $_POST['description'];
    $idUser = $_SESSION['user']['id'];

    $stmt = $pdo->prepare("SELECT id FROM Property WHERE address = ? AND description = ?");
    $stmt->execute([$address, $desc]);
    $existing = $stmt->fetch();

    if ($existing) {
        $idProperty = $existing['id'];
    } else {
        $stmt = $pdo->prepare("INSERT INTO Property (address, description) VALUES (?, ?)");
        $stmt->execute([$address, $desc]);
        $idProperty = $pdo->lastInsertId();
    }

    $stmt = $pdo->prepare("INSERT INTO UserToProperties (idUser, idProperty) VALUES (?, ?)");
    $stmt->execute([$idUser, $idProperty]);

    header('Location: index.php');
?>