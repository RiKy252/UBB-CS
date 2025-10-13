<?php 
    include 'db.php';
    session_start();
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    $customer = $_SESSION['user'];
    if (isset($_POST['message'])) {
        $message = $_POST['message'];
        $_SESSION['message'] = $message;
        $blockedWords = $db->getAllBlockedWords();
        $count = 0;
        $highlightedMessage = $message;
        foreach ($blockedWords as $blockedWord) {
            $pattern = '/' . $blockedWord['pattern'] . '/';
            // $pattern = "/{$blockedWord['pattern']}/";
            $currentCount = preg_match_all($pattern, $highlightedMessage);
            if ($currentCount) {
                $count += $currentCount;
                $highlightedMessage = preg_replace($pattern, '<strong>$0</strong>', $highlightedMessage);
            }
        }
        $flag = false;
        if ($count > 3) {
            $flag = true;
        }
        $_SESSION['flag'] = $flag;
        $_SESSION['highlightedMessage'] = $highlightedMessage;
        echo "<form method='POST'><button name='remove_blocked_words'>Remove existing blocked words</button></form>";
        if ($flag) {
            echo 'Warning: we found ' . $count . ' blocked words inside your message: ';
            echo $highlightedMessage;
            echo "<form method='POST'>
                    Updated message: <input type='text' name='updatedMessage' required>
                    <input type='submit' value='Update message'>
                    </form>";
        }
        else {
            echo "<form method='POST'><button name='add_feedback'>Add feedback</button></form>";
        }
    }
    if (isset($_POST['updatedMessage'])) {
        echo "<form method='POST'><button name='add_feedback'>Add feedback</button></form>";
        $_SESSION['finalMessage'] = $_POST['updatedMessage'];
    }
    if (isset($_POST['remove_blocked_words'])) {
        $newPattern = '/<strong>.*?<\/strong>/';
        $finalMessage = preg_replace($newPattern, '', $_SESSION['highlightedMessage']);
        $_SESSION['finalMessage'] = $finalMessage;
        if (isset($_SESSION['flag'])) {
            echo "<form method='POST'><button name='add_feedback'>Add feedback</button></form>";
        }
    }
    if (isset($_POST['add_feedback'])) {
        if (isset($_SESSION['finalMessage']))
            $db->addNewFeedback($customer['customerId'], $_SESSION['finalMessage']);
        else
            $db->addNewFeedback($customer['customerId'], $_SESSION['message']);
        echo 'Feedback added successfully!';
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
    <form method="POST">
        Feedback message: <input type="text" name="message" required>
        <input type="submit" value="Check">
    </form>
    <p><a href="index.php">Back</a></p>
</body>
</html>