<?php
    include 'db.php';
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $idUser = $_SESSION['user']['id'];
    $idProp = $_POST['property_id'];

    $stmt = $pdo->prepare("DELETE FROM UserToProperties WHERE idUser = ? AND idProperty = ?");
    $stmt->execute([$idUser, $idProp]);

    $stmt = $pdo->prepare("SELECT COUNT(*) FROM UserToProperties WHERE idProperty = ?");
    $stmt->execute([$idProp]);
    if ($stmt->fetchColumn() == 0) {
        $pdo->prepare("DELETE FROM Property WHERE id = ?")->execute([$idProp]);
    }

    header('Location: index.php');
?>