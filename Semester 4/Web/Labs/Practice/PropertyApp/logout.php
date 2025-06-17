<?php
    include 'db.php';
    session_destroy();
    header('Location: login.php');
?>
