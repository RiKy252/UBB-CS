<?php
    include 'db.php';
    session_start();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $user = $_SESSION['user'];
    $db = new Database();
    $addr = $_POST['address'];
    $desc = $_POST['description'];
    $existing = $db->checkPropertyExists($addr, $desc);
    if ($existing) {
        $propertyId = $existing['propertyId'];
    }
    else {
        $propertyId = $db->addProperty($addr, $desc);
    }
    $notOk = $db->checkLinkingExists($user['userId'], $propertyId);
    if (!$notOk)
        $db->linkUserToProperty($user['userId'], $propertyId);
    header('Location: index.php');
?>