<?php
    require 'auth.php';
    session_destroy();
    header("Location: login.php");
?>