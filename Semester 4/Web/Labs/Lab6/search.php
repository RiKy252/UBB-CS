<?php
require_once 'config.php';

// Initialize variables
$search_term = "";
$min_cost = "";
$max_cost = "";
$country_id = 0;
$results = [];

// Process search form submission
if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET["search_term"])) {
    $search_term = sanitize($conn, $_GET["search_term"]);
    $min_cost = !empty($_GET["min_cost"]) ? (float)$_GET["min_cost"] : "";
    $max_cost = !empty($_GET["max_cost"]) ? (float)$_GET["max_cost"] : "";
    $country_id = !empty($_GET["country_id"]) ? (int)$_GET["country_id"] : 0;
    
    // Build SQL query based on search parameters
    $query = "SELECT d.*, c.country_name 
              FROM destinations d
              JOIN countries c ON d.country_id = c.country_id
              WHERE 1=1";
    
    $params = [];
    $types = "";
    
    // Add search term condition if provided
    if (!empty($search_term)) {
        $query .= " AND (d.location_name LIKE ? OR d.description LIKE ? OR d.tourist_targets LIKE ?)";
        $search_param = "%{$search_term}%";
        $params[] = $search_param;
        $params[] = $search_param;
        $params[] = $search_param;
        $types .= "sss";
    }
    
    // Add country condition if provided
    if ($country_id > 0) {
        $query .= " AND d.country_id = ?";
        $params[] = $country_id;
        $types .= "i";
    }
    
    // Add min cost condition if provided
    if ($min_cost !== "") {
        $query .= " AND d.cost_per_day >= ?";
        $params[] = $min_cost;
        $types .= "d";
    }
    
    // Add max cost condition if provided
    if ($max_cost !== "") {
        $query .= " AND d.cost_per_day <= ?";
        $params[] = $max_cost;
        $types .= "d";
    }
    
    // Add order by clause
    $query .= " ORDER BY c.country_name, d.location_name";
    
    // Prepare and execute the query
    $stmt = $conn->prepare($query);
    
    if ($stmt) {
        // Bind parameters if any
        if (!empty($params)) {
            // Convert params array to references for bind_param
            $bind_params = [];
            $bind_params[] = &$types;
            
            foreach ($params as &$param) {
                $bind_params[] = &$param;
            }
            
            call_user_func_array([$stmt, 'bind_param'], $bind_params);
        }
        
        // Execute the query
        $stmt->execute();
        $result = $stmt->get_result();
        
        // Fetch all results
        while ($row = $result->fetch_assoc()) {
            $results[] = $row;
        }
        
        // Close statement
        $stmt->close();
    } else {
        // Handle error
        echo "Error preparing statement: " . $conn->error;
    }
}

// Function to sanitize input
function sanitize($conn, $data) {
    return htmlspecialchars(strip_tags(trim($conn->real_escape_string($data))));
}

// Get list of countries for the dropdown
$countries = [];
$country_query = "SELECT country_id, country_name FROM countries ORDER BY country_name";
$country_result = $conn->query($country_query);

if ($country_result) {
    while ($country = $country_result->fetch_assoc()) {
        $countries[] = $country;
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Search Travel Destinations</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <div class="container">
        <h1>Search Travel Destinations</h1>
        
        <!-- Search Form -->
        <form method="GET" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" class="search-form">
            <div class="form-group">
                <label for="search_term">Search:</label>
                <input type="text" id="search_term" name="search_term" value="<?php echo $search_term; ?>" placeholder="Enter location or keywords">
            </div>
            
            <div class="form-group">
                <label for="country_id">Country:</label>
                <select id="country_id" name="country_id">
                    <option value="0">All Countries</option>
                    <?php foreach ($countries as $country): ?>
                    <option value="<?php echo $country['country_id']; ?>" <?php echo ($country_id == $country['country_id']) ? 'selected' : ''; ?>>
                        <?php echo $country['country_name']; ?>
                    </option>
                    <?php endforeach; ?>
                </select>
            </div>
            
            <div class="form-row">
                <div class="form-group">
                    <label for="min_cost">Min Cost (per day):</label>
                    <input type="number" id="min_cost" name="min_cost" value="<?php echo $min_cost; ?>" step="0.01" min="0">
                </div>
                
                <div class="form-group">
                    <label for="max_cost">Max Cost (per day):</label>
                    <input type="number" id="max_cost" name="max_cost" value="<?php echo $max_cost; ?>" step="0.01" min="0">
                </div>
            </div>
            
            <button type="submit" class="btn-search">Search</button>
            <a href="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" class="btn-reset">Reset</a>
        </form>
        
        <!-- Search Results -->
        <?php if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET["search_term"])): ?>
            <div class="search-results">
                <h2>Search Results</h2>
                <?php if (empty($results)): ?>
                    <p class="no-results">No destinations found matching your criteria.</p>
                <?php else: ?>
                    <p class="result-count"><?php echo count($results); ?> destination(s) found.</p>
                    
                    <div class="results-grid">
                        <?php foreach ($results as $destination): ?>
                            <div class="destination-card">
                                <h3><?php echo $destination['location_name']; ?></h3>
                                <h4><?php echo $destination['country_name']; ?></h4>
                                
                                <?php if (!empty($destination['image_url'])): ?>
                                    <img src="<?php echo htmlspecialchars($destination['image_url']); ?>" alt="<?php echo htmlspecialchars($destination['location_name']); ?>">
                                <?php endif; ?>
                                
                                <div class="destination-info">
                                    <p class="cost">
                                        <strong>Cost per day:</strong> $<?php echo number_format($destination['cost_per_day'], 2); ?>
                                    </p>
                                    
                                    <?php if (!empty($destination['best_time_to_visit'])): ?>
                                        <p>
                                            <strong>Best time to visit:</strong> <?php echo $destination['best_time_to_visit']; ?>
                                        </p>
                                    <?php endif; ?>
                                    
                                    <p class="description"><?php echo nl2br($destination['description']); ?></p>
                                    
                                    <?php if (!empty($destination['tourist_targets'])): ?>
                                        <p>
                                            <strong>Must visit:</strong> <?php echo $destination['tourist_targets']; ?>
                                        </p>
                                    <?php endif; ?>
                                    
                                    <a href="destination.php?id=<?php echo $destination['destination_id']; ?>" class="btn-details">View Details</a>
                                </div>
                            </div>
                        <?php endforeach; ?>
                    </div>
                <?php endif; ?>
            </div>
        <?php endif; ?>
    </div>
    
    <footer>
        <p>&copy; <?php echo date('Y'); ?> Travel Destinations Directory</p>
    </footer>
    
    <script src="js/script.js"></script>
</body>
</html>