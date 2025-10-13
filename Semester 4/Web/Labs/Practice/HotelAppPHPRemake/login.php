<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (isset($_POST['login'])) {
        $username = trim($_POST['username']);
        $password = trim($_POST['password']);
        if (!empty($username) && !empty($password)) {
            $user = $db->getUserByName($username);
            if ($user) {
                if ($db->checkCredentials($username, $password)) {
                    $_SESSION['user'] = $user;
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
    <title>Hotel App</title>
</head>
<body>
    <?php if (!isset($_SESSION['user'])): ?>
        <h2>Username login</h2>
        <form method="POST">
            <label>Username: <input type="text" name="username" required></label>
            <label>Password: <input type="password" name="password" required></label>
            <input type="submit" name="login" value="Next">
        </form>
    <?php endif; ?>
</body>
</html>