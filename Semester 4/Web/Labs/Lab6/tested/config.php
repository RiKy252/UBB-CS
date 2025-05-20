<?php
define('DB_SERVER', 'www.scs.ubbcluj.ro');
define('DB_USERNAME', 'brie3483'); 
define('DB_PASSWORD', 'NDFi-DE3ZThh'); 
define('DB_NAME', 'brie3483'); 

$conn = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

if($conn === false){
    die("ERROR: Could not connect to database. " . mysqli_connect_error());
}

mysqli_set_charset($conn, "utf8mb4");

// Function to prevent SQL injection
function sanitize($conn, $data) {
    return mysqli_real_escape_string($conn, trim($data));
}
?>