<?php
    include 'db.php';
    if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_SESSION['temp_user'])) {
        if ($_POST['answer'] === $_SESSION['temp_user']['secretAnswer']) {
            $_SESSION['user'] = $_SESSION['temp_user'];
            $_SESSION['search_log'] = [];
            unset($_SESSION['temp_user']);
            header('Location: index.php');
        } else {
            echo "Wrong answer. <a href='login.php'>Try again</a>";
        }
    }
?>