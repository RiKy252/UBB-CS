<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (isset($_POST['login'])) {
        $customerName = trim($_POST['customerName']);
        $email = trim($_POST['email']);
        if (!empty($customerName) && !empty($email)) {
            $customer = $db->getCustomerByName($customerName);
            if ($customer) {
                if ($db->checkCredentials($customerName, $email)) {
                    $_SESSION['user'] = $customer;
                    header('Location: index.php');
                    exit;
                }
            } else {
                echo "Invalid credentials. Please try again.";
            }
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Feedback App</title>
</head>
<body>
        <h2>Username login</h2>
        <form method="POST">
            <label>Username: <input type="text" name="customerName" required></label>
            <label>Email: <input type="text" name="email" required></label>
            <input type="submit" name="login" value="Login">
        </form>
</body>
</html>