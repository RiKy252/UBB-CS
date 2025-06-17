<?php
    require 'db.php';
    require 'auth.php';

    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $stmt = $pdo->prepare("SELECT * FROM User WHERE username = ? AND password = ?");
        $stmt->execute([$_POST['username'], $_POST['password']]);
        $user = $stmt->fetch();

        if ($user) {
            $_SESSION['user_id'] = $user['id'];
            header('Location: index.php');
        } else {
            echo "Invalid credentials.";
        }
    }
?>

<form method="POST">
    Username: <input name="username"><br>
    Password: <input name="password" type="password"><br>
    <button>Login</button>
</form>
