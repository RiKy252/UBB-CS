<?php
    require 'auth.php';
    requireLogin();
?>

<h1>Welcome to Hotel App</h1>
<ul>
    <li><a href="rooms.php">View Available Rooms</a></li>
    <li><a href="reserve.php">Reserve Room</a></li>
    <li><a href="reservations.php">My Reservations</a></li>
    <li><a href="guests.php">Guests on a Date</a></li>
    <li><a href="logout.php">Logout</a></li>
</ul>