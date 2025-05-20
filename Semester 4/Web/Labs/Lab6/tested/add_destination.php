<?php
require_once 'config.php';

// Initialize variables
$location_name = $description = $tourist_targets = $cost_per_day = "";
$country_id = 0;
$errors = [];
$success_message = "";

// Process form submission
if($_SERVER["REQUEST_METHOD"] == "POST") {
    // Validate and sanitize inputs
    if(empty(trim($_POST["location_name"]))) {
        $errors[] = "Please enter a location name.";
    } else {
        $location_name = sanitize($conn, $_POST["location_name"]);
    }
    
    if(empty(trim($_POST["country_id"])) || $_POST["country_id"] == "0") {
        $errors[] = "Please select a country.";
    } else {
        $country_id = (int)$_POST["country_id"];
    }
    
    $description = sanitize($conn, $_POST["description"]);
    $tourist_targets = sanitize($conn, $_POST["tourist_targets"]);
    
    if(empty(trim($_POST["cost_per_day"]))) {
        $errors[] = "Please enter cost per day.";
    } else if(!is_numeric($_POST["cost_per_day"]) || $_POST["cost_per_day"] <= 0) {
        $errors[] = "Cost per day must be a positive number.";
    } else {
        $cost_per_day = (float)$_POST["cost_per_day"];
    }
    
    // If no errors, insert destination into database
    if(empty($errors)) {
        $sql = "INSERT INTO destinations (country_id, location_name, description, tourist_targets, cost_per_day) 
                VALUES (?, ?, ?, ?, ?)";
                
        if($stmt = mysqli_prepare($conn, $sql)) {
            mysqli_stmt_bind_param($stmt, "isssd", $country_id, $location_name, $description, $tourist_targets, $cost_per_day);
            
            if(mysqli_stmt_execute($stmt)) {
                $success_message = "Destination added successfully!";
                $location_name = $description = $tourist_targets = $cost_per_day = "";
                $country_id = 0;
            } else {
                $errors[] = "Something went wrong. Please try again later.";
            }
            
            mysqli_stmt_close($stmt);
        }
    }
}

// Get all countries for the dropdown
$countries_query = "SELECT * FROM countries ORDER BY country_name";
$countries_result = mysqli_query($conn, $countries_query);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Add Destination</title>
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
            <h2>Add New Destination</h2>
            
            <?php if(!empty($success_message)): ?>
                <div class="success-message"><?php echo $success_message; ?></div>
            <?php endif; ?>
            
            <?php if(!empty($errors)): ?>
                <div class="error-message">
                    <ul>
                        <?php foreach($errors as $error): ?>
                            <li><?php echo $error; ?></li>
                        <?php endforeach; ?>
                    </ul>
                </div>
            <?php endif; ?>
            
            <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post" id="addDestinationForm">
                <div class="form-group">
                    <label for="country_id">Country:</label>
                    <select name="country_id" id="country_id" required>
                        <option value="0">Select a country</option>
                        <?php while($country = mysqli_fetch_assoc($countries_result)): ?>
                            <option value="<?php echo $country['country_id']; ?>" <?php if($country_id == $country['country_id']) echo 'selected'; ?>>
                                <?php echo htmlspecialchars($country['country_name']); ?>
                            </option>
                        <?php endwhile; ?>
                    </select>
                </div>
                
                <div class="form-group">
                    <label for="location_name">Location Name:</label>
                    <input type="text" name="location_name" id="location_name" value="<?php echo htmlspecialchars($location_name); ?>" required>
                </div>
                
                <div class="form-group">
                    <label for="description">Description:</label>
                    <textarea name="description" id="description"><?php echo htmlspecialchars($description); ?></textarea>
                </div>
                
                <div class="form-group">
                    <label for="tourist_targets">Tourist Targets:</label>
                    <textarea name="tourist_targets" id="tourist_targets"><?php echo htmlspecialchars($tourist_targets); ?></textarea>
                </div>
                
                <div class="form-group">
                    <label for="cost_per_day">Cost per Day ($):</label>
                    <input type="number" name="cost_per_day" id="cost_per_day" step="0.01" min="0.01" value="<?php echo htmlspecialchars($cost_per_day); ?>" required>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-success">Add Destination</button>
                    <button type="button" class="btn" onclick="window.location.href='index.php'">Cancel</button>
                </div>
            </form>
        </div>
    </div>
    
    <script>
        // Client-side form validation
        $(document).ready(function() {
            $("#addDestinationForm").submit(function(e) {
                let isValid = true;
                const locationName = $("#location_name").val().trim();
                const countryId = $("#country_id").val();
                const costPerDay = $("#cost_per_day").val().trim();
                
                // Reset previous error messages
                $(".error").remove();
                
                // Validate location name
                if (locationName === "") {
                    $("#location_name").after('<div class="error">Please enter a location name</div>');
                    isValid = false;
                }
                
                // Validate country selection
                if (countryId === "0") {
                    $("#country_id").after('<div class="error">Please select a country</div>');
                    isValid = false;
                }
                
                // Validate cost per day
                if (costPerDay === "") {
                    $("#cost_per_day").after('<div class="error">Please enter cost per day</div>');
                    isValid = false;
                } else if (isNaN(costPerDay) || parseFloat(costPerDay) <= 0) {
                    $("#cost_per_day").after('<div class="error">Cost must be a positive number</div>');
                    isValid = false;
                }
                
                if (!isValid) {
                    e.preventDefault();
                }
            });
        });
    </script>
</body>
</html>