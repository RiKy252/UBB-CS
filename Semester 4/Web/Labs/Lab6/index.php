<?php
require_once 'config.php';

// Initialize variables for pagination
$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
$limit = 4; // 4 destinations per page
$offset = ($page - 1) * $limit;

// Get total number of destinations
$total_query = "SELECT COUNT(*) as total FROM destinations";
$total_result = mysqli_query($conn, $total_query);
$total_row = mysqli_fetch_assoc($total_result);
$total_destinations = $total_row['total'];
$total_pages = ceil($total_destinations / $limit);

// Get all countries for the dropdown
$countries_query = "SELECT * FROM countries ORDER BY country_name";
$countries_result = mysqli_query($conn, $countries_query);

// Get destinations with pagination
$query = "SELECT d.*, c.country_name 
          FROM destinations d
          JOIN countries c ON d.country_id = c.country_id
          ORDER BY c.country_name, d.location_name
          LIMIT $offset, $limit";
$result = mysqli_query($conn, $query);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vacation Destinations</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <header>
        <h1>Vacation Destinations Manager</h1>
    </header>
    
    <nav>
        <ul>
            <li><a href="index.php">Home</a></li>
            <li><a href="add_destination.php">Add New Destination</a></li>
            <li><a href="manage_countries.php">Manage Countries</a></li>
            <li><a href="search.php">Search Destinations</a></li>
            <li><a href="about.php">About</a></li>
        </ul>
    </nav>
    
    <div class="container">
        <div class="card">
            <h2>Browse Destinations</h2>
            
            <div class="filter-section">
                <label for="countrySelector">Filter by Country:</label>
                <select id="countrySelector" onchange="loadDestinationsByCountry()">
                    <option value="0">All Countries</option>
                    <?php while($country = mysqli_fetch_assoc($countries_result)): ?>
                        <option value="<?php echo $country['country_id']; ?>"><?php echo htmlspecialchars($country['country_name']); ?></option>
                    <?php endwhile; ?>
                </select>
            </div>
            
            <div id="destinationsContainer">
                <?php if(mysqli_num_rows($result) > 0): ?>
                    <?php while($row = mysqli_fetch_assoc($result)): ?>
                        <div class="destination-card">
                            <h3><?php echo htmlspecialchars($row['location_name']); ?>, <?php echo htmlspecialchars($row['country_name']); ?></h3>
                            <p><strong>Description:</strong> <?php echo htmlspecialchars($row['description']); ?></p>
                            <p><strong>Tourist Targets:</strong> <?php echo htmlspecialchars($row['tourist_targets']); ?></p>
                            <p><strong>Cost per day:</strong> $<?php echo htmlspecialchars($row['cost_per_day']); ?></p>
                            <div class="actions">
                                <a href="edit_destination.php?id=<?php echo $row['destination_id']; ?>" class="btn btn-warning">Edit</a>
                                <button class="btn btn-danger" onclick="confirmDelete(<?php echo $row['destination_id']; ?>)">Delete</button>
                            </div>
                        </div>
                    <?php endwhile; ?>
                    
                    <div class="pagination">
                        <?php if($page > 1): ?>
                            <a href="?page=<?php echo $page-1; ?>">&laquo; Previous</a>
                        <?php endif; ?>
                        
                        <?php for($i = 1; $i <= $total_pages; $i++): ?>
                            <a href="?page=<?php echo $i; ?>" <?php if($i == $page) echo 'class="active"'; ?>><?php echo $i; ?></a>
                        <?php endfor; ?>
                        
                        <?php if($page < $total_pages): ?>
                            <a href="?page=<?php echo $page+1; ?>">Next &raquo;</a>
                        <?php endif; ?>
                    </div>
                <?php else: ?>
                    <p>No destinations found.</p>
                <?php endif; ?>
            </div>
        </div>
    </div>
    
    <script>
        // Function to confirm delete action
        function confirmDelete(destinationId) {
            if(confirm("Are you sure you want to delete this destination?")) {
                window.location.href = "delete_destination.php?id=" + destinationId;
            }
        }
        
        // Function to load destinations by country using AJAX
        function loadDestinationsByCountry() {
            var countryId = document.getElementById("countrySelector").value;
            
            $.ajax({
                url: "get_destinations.php",
                type: "GET",
                data: { country_id: countryId, page: 1 },
                success: function(data) {
                    $("#destinationsContainer").html(data);
                },
                error: function() {
                    alert("Error loading destinations. Please try again.");
                }
            });
        }
    </script>
</body>
</html>