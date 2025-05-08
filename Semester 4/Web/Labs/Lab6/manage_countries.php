<?php
require_once 'config.php';

// Initialize variables
$country_name = "";
$edit_id = 0;
$errors = [];
$success_message = "";

// Process add/edit form submission
if($_SERVER["REQUEST_METHOD"] == "POST") {
    // Validate and sanitize inputs
    if(empty(trim($_POST["country_name"]))) {
        $errors[] = "Please enter a country name.";
    } else {
        $country_name = sanitize($conn, $_POST["country_name"]);
        
        // Check if country already exists
        $check_sql = "SELECT country_id FROM countries WHERE country_name = ? AND country_id != ?";
        if($check_stmt = mysqli_prepare($conn, $check_sql)) {
            $edit_id = isset($_POST["edit_id"]) ? (int)$_POST["edit_id"] : 0;
            mysqli_stmt_bind_param($check_stmt, "si", $country_name, $edit_id);
            
            if(mysqli_stmt_execute($check_stmt)) {
                $check_result = mysqli_stmt_get_result($check_stmt);
                
                if(mysqli_num_rows($check_result) > 0) {
                    $errors[] = "This country already exists.";
                }
            }
            
            mysqli_stmt_close($check_stmt);
        }
    }
    
    // If no errors, insert or update country
    if(empty($errors)) {
        if(isset($_POST["edit_id"]) && $_POST["edit_id"] > 0) {
            // Update existing country
            $sql = "UPDATE countries SET country_name = ? WHERE country_id = ?";
            
            if($stmt = mysqli_prepare($conn, $sql)) {
                mysqli_stmt_bind_param($stmt, "si", $country_name, $_POST["edit_id"]);
                
                if(mysqli_stmt_execute($stmt)) {
                    $success_message = "Country updated successfully!";
                    $country_name = "";
                    $edit_id = 0;
                } else {
                    $errors[] = "Something went wrong. Please try again later.";
                }
                
                mysqli_stmt_close($stmt);
            }
        } else {
            // Insert new country
            $sql = "INSERT INTO countries (country_name) VALUES (?)";
            
            if($stmt = mysqli_prepare($conn, $sql)) {
                mysqli_stmt_bind_param($stmt, "s", $country_name);
                
                if(mysqli_stmt_execute($stmt)) {
                    $success_message = "Country added successfully!";
                    $country_name = "";
                } else {
                    $errors[] = "Something went wrong. Please try again later.";
                }
                
                mysqli_stmt_close($stmt);
            }
        }
    }
}

// Get country for editing
if(isset($_GET['edit']) && !empty($_GET['edit'])) {
    $edit_id = (int)$_GET['edit'];
    
    $edit_sql = "SELECT * FROM countries WHERE country_id = ?";
    
    if($edit_stmt = mysqli_prepare($conn, $edit_sql)) {
        mysqli_stmt_bind_param($edit_stmt, "i", $edit_id);
        
        if(mysqli_stmt_execute($edit_stmt)) {
            $edit_result = mysqli_stmt_get_result($edit_stmt);
            
            if(mysqli_num_rows($edit_result) == 1) {
                $edit_row = mysqli_fetch_assoc($edit_result);
                $country_name = $edit_row['country_name'];
            } else {
                // Country not found
                header("location: manage_countries.php");
                exit;
            }
        }
        
        mysqli_stmt_close($edit_stmt);
    }
}

// Get all countries
$countries_query = "SELECT * FROM countries ORDER BY country_name";
$countries_result = mysqli_query($conn, $countries_query);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Manage Countries</title>
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
            <h2><?php echo $edit_id > 0 ? 'Edit' : 'Add'; ?> Country</h2>
            
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
            
            <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post" id="countryForm">
                <?php if($edit_id > 0): ?>
                    <input type="hidden" name="edit_id" value="<?php echo $edit_id; ?>">
                <?php endif; ?>
                
                <div class="form-group">
                    <label for="country_name">Country Name:</label>
                    <input type="text" name="country_name" id="country_name" value="<?php echo htmlspecialchars($country_name); ?>" required>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-success"><?php echo $edit_id > 0 ? 'Update' : 'Add'; ?> Country</button>
                    <?php if($edit_id > 0): ?>
                        <a href="manage_countries.php" class="btn">Cancel</a>
                    <?php endif; ?>
                </div>
            </form>
        </div>
        
        <div class="card">
            <h2>Countries List</h2>
            
            <table>
                <thead>
                    <tr>
                        <th>Country Name</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <tbody>
                    <?php if(mysqli_num_rows($countries_result) > 0): ?>
                        <?php while($row = mysqli_fetch_assoc($countries_result)): ?>
                            <tr>
                                <td><?php echo htmlspecialchars($row['country_name']); ?></td>
                                <td class="actions">
                                    <a href="manage_countries.php?edit=<?php echo $row['country_id']; ?>" class="btn btn-warning">Edit</a>
                                    <button class="btn btn-danger" onclick="confirmDeleteCountry(<?php echo $row['country_id']; ?>, '<?php echo htmlspecialchars($row['country_name']); ?>')">Delete</button>
                                </td>
                            </tr>
                        <?php endwhile; ?>
                    <?php else: ?>
                        <tr>
                            <td colspan="2">No countries found.</td>
                        </tr>
                    <?php endif; ?>
                </tbody>
            </table>
        </div>
    </div>
    
    <script>
        // Function to confirm delete action
        function confirmDeleteCountry(countryId, countryName) {
            if(confirm("Are you sure you want to delete '" + countryName + "'? This will also delete all destinations in this country!")) {
                window.location.href = "delete_country.php?id=" + countryId;
            }
        }
        
        // Client-side form validation
        $(document).ready(function() {
            $("#countryForm").submit(function(e) {
                let isValid = true;
                const countryName = $("#country_name").val().trim();
                
                // Reset previous error messages
                $(".error").remove();
                
                // Validate country name
                if (countryName === "") {
                    $("#country_name").after('<div class="error">Please enter a country name</div>');
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