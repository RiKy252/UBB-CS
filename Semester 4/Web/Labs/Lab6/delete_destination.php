<?php
require_once 'config.php';

// Check if destination ID is provided
if(!isset($_GET['id']) || empty($_GET['id'])) {
    header("location: index.php");
    exit;
}

$destination_id = (int)$_GET['id'];

// Delete destination from database
$sql = "DELETE FROM destinations WHERE destination_id = ?";

if($stmt = mysqli_prepare($conn, $sql)) {
    mysqli_stmt_bind_param($stmt, "i", $destination_id);
    
    if(mysqli_stmt_execute($stmt)) {
        // Redirect to index page with success message
        header("location: index.php?deleted=true");
        exit;
    } else {
        // Redirect to index page with error message
        header("location: index.php?error=delete_failed");
        exit;
    }
    
    mysqli_stmt_close($stmt);
} else {
    // Redirect to index page with error message
    header("location: index.php?error=prepare_failed");
    exit;
}

// Close connection
mysqli_close($conn);
?>