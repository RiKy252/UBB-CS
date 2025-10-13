<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (isset($_POST['usernameSubmit'])) {
        $username = trim($_POST['username']);
        if (!empty($username)) {
            $user = $db->getUserByName($username);
            if ($user) {
                $_SESSION['temp_user'] = $user;
            } else {
                $error = "User not found. Please try again.";
            }
        }
    }

    if (isset($_POST['answerSubmit'])) {
        if (isset($_SESSION['temp_user'])) {
        $user = $_SESSION['temp_user'];
            if ($user['secretAnswer'] === $_POST['userAnswer']) {
                $_SESSION['user'] = $user;
                unset($_SESSION['temp_user']);
                header('Location: index.php');
                exit;
            } else {
                echo "Wrong answer.";
            }
        } else {
            echo "Session expired or invalid. Please start login again.";
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Property App</title>
</head>
<body>
    <?php if (!isset($_SESSION['temp_user'])): ?>
        <h2>Username login</h2>
        <form method="POST">
            <label>Username: <input type="text" name="username" required></label>
            <input type="submit" name="usernameSubmit" value="Next">
        </form>
    <?php else: ?>
        <?php $user = $_SESSION['temp_user']; ?>
        <h2>Secret Question Login</h2>
        <form method="POST">
            <label><?= htmlspecialchars($user['secretQuestion']) ?>: <input type="text" name="userAnswer" required></label>
            <input type="submit" name="answerSubmit" value="Login">
        </form>
    <?php endif; ?>
</body>
</html>