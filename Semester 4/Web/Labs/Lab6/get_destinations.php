<?php
require_once 'config.php';

// Get country ID from request
$country_id = isset($_GET['country_id']) ? (int)$_GET['country_id'] : 0;

// Initialize variables for pagination
$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
$limit = 4; // 4 destinations per page
$offset = ($page - 1) * $limit;

// Prepare the SQL query based on whether a country is selected
if($country_id > 0) {
    // Get total number of destinations for this country
    $total_query = "SELECT COUNT(*) as total FROM destinations WHERE country_id = $country_id";
    
    // Get destinations for the selected country with pagination
    $query = "SELECT d.*, c.country_name 
              FROM destinations d
              JOIN countries c ON d.country_id = c.country_id
              WHERE d.country_id = $country_id
              ORDER BY d.location_name
              LIMIT $offset, $limit";
} else {
    // Get total number of all destinations
    $total_query = "SELECT COUNT(*) as total FROM destinations";
    
    // Get all destinations with pagination
    $query = "SELECT d.*, c.country_name 
              FROM destinations d
              JOIN countries c ON d.country_id = c.country_id
              ORDER BY c.country_name, d.location_name
              LIMIT $offset, $limit";
}

// Execute total query
$total_result = mysqli_query($conn, $total_query);
$total_row = mysqli_fetch_assoc($total_result);
$total_destinations = $total_row['total'];
$total_pages = ceil($total_destinations / $limit);

// Execute destinations query
$result = mysqli_query($conn, $query);

// Check if there are any destinations
if(mysqli_num_rows($result) > 0) {
    // Output destinations
    while($row = mysqli_fetch_assoc($result)) {
        echo '<div class="destination-card">';
        echo '<h3>' . htmlspecialchars($row['location_name']) . ', ' . htmlspecialchars($row['country_name']) . '</h3>';
        echo '<p><strong>Description:</strong> ' . htmlspecialchars($row['description']) . '</p>';
        echo '<p><strong>Tourist Targets:</strong> ' . htmlspecialchars($row['tourist_targets']) . '</p>';
        echo '<p><strong>Cost per day:</strong> $' . htmlspecialchars($row['cost_per_day']) . '</p>';
        echo '<div class="actions">';
        echo '<a href="edit_destination.php?id=' . $row['destination_id'] . '" class="btn btn-warning">Edit</a>';
        echo '<button class="btn btn-danger" onclick="confirmDelete(' . $row['destination_id'] . ')">Delete</button>';
        echo '</div>';
        echo '</div>';
    }
    
    // Output pagination links
    echo '<div class="pagination">';
    if($page > 1) {
        echo '<a href="javascript:void(0)" onclick="loadPage(' . ($page-1) . ')">&laquo; Previous</a>';
    }
    
    for($i = 1; $i <= $total_pages; $i++) {
        echo '<a href="javascript:void(0)" onclick="loadPage(' . $i . ')"';
        if($i == $page) echo ' class="active"';
        echo '>' . $i . '</a>';
    }
    
    if($page < $total_pages) {
        echo '<a href="javascript:void(0)" onclick="loadPage(' . ($page+1) . ')">Next &raquo;</a>';
    }
    echo '</div>';
    
    // Add JavaScript function for loading pages
    echo '<script>
        function loadPage(pageNum) {
            var countryId = document.getElementById("countrySelector").value;
            $.ajax({
                url: "get_destinations.php",
                type: "GET",
                data: { country_id: countryId, page: pageNum },
                success: function(data) {
                    $("#destinationsContainer").html(data);
                },
                error: function() {
                    alert("Error loading destinations. Please try again.");
                }
            });
        }
        
        function confirmDelete(destinationId) {
            if(confirm("Are you sure you want to delete this destination?")) {
                window.location.href = "delete_destination.php?id=" + destinationId;
            }
        }
    </script>';
} else {
    echo '<p>No destinations found.</p>';
}
?>