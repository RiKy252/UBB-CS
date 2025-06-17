<?php
    include 'db.php';
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $stmt = $pdo->prepare("SELECT * FROM User WHERE name = ?");
        $stmt->execute([$_POST['name']]);
        $user = $stmt->fetch();
        if ($user) {
            $_SESSION['temp_user'] = $user;
            echo "<form method='post' action='authenticate.php'>
                    <p>Secret Question: {$user['secretQuestion']}</p>
                    <input type='text' name='answer' required>
                    <input type='submit' value='Login'>
                </form>";
        } else {
            echo "User not found. <a href='login.php'>Try again</a>";
        }
    }
?>
