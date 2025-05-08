<?php
require_once 'config.php';

// Check if country ID is provided
if(!isset($_GET['id']) || empty($_GET['id'])) {
    header("location: manage_countries.php");
    exit;
}

$country_id = (int)$_GET['id'];

// Delete country from database
// Note: Due to ON DELETE CASCADE in the foreign key constraint,
// all destinations associated with this country will also be deleted
$sql = "DELETE FROM countries WHERE country_id = ?";

if($stmt = mysqli_prepare($conn, $sql)) {
    mysqli_stmt_bind_param($stmt, "i", $country_id);
    
    if(mysqli_stmt_execute($stmt)) {
        // Redirect to manage countries page with success message
        header("location: manage_countries.php?deleted=true");
        exit;
    } else {
        // Redirect to manage countries page with error message
        header("location: manage_countries.php?error=delete_failed");
        exit;
    }
    
    mysqli_stmt_close($stmt);
} else {
    // Redirect to manage countries page with error message
    header("location: manage_countries.php?error=prepare_failed");
    exit;
}

// Close connection
mysqli_close($conn);
?>