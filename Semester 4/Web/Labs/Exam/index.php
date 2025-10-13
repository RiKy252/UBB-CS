<?php
    session_start();
    require 'db.php';
    $db = new Database();
    if (!isset($_SESSION['user'])) {
        header('Location: login.php');
        exit;
    }
    else {
        $user = $_SESSION['user'];
    }
    echo "<p>Here are all the tasks:<br></p>";
    $todoTasks = $db->getTasksByStatus('todo');
    echo "<h2>To do tasks:<br></h2>";
    foreach ($todoTasks as $task) {
        $newUser = $db->getUserById($task['assignedTo']);
        $username = $newUser['username'];
        echo "<p>{$task['taskTitle']} -> assigned to: {$username}</p>";
        echo "<form method='POST'>
                <input type='hidden' name='taskId' value='{$task['taskId']}'>
                New Status: <input type='text' name='newStatus'>
                <input type='submit' name='moveTask' value='Move task'>
            </form>";
    }
    echo "<br>";
    $inProgressTasks = $db->getTasksByStatus('in_progress');
    echo "<h2>In progress tasks:<br></h2>";
    foreach ($inProgressTasks as $task) {
        $newUser = $db->getUserById($task['assignedTo']);
        $username = $newUser['username'];
        echo "<p>{$task['taskTitle']} -> assigned to: {$username}</p>";
        echo "<form method='POST'>
                <input type='hidden' name='taskId' value='{$task['taskId']}'>
                New Status: <input type='text' name='newStatus'>
                <input type='submit' name='moveTask' value='Move task'>
            </form>";
    }
    echo "<br>";
    $doneTasks = $db->getTasksByStatus('done');
    echo "<h2>Done tasks:<br></h2>";
    foreach ($doneTasks as $task) {
        $newUser = $db->getUserById($task['assignedTo']);
        $username = $newUser['username'];
        echo "<p>{$task['taskTitle']} -> assigned to: {$username}</p>";
        echo "<form method='POST'>
                <input type='hidden' name='taskId' value='{$task['taskId']}'>
                New Status: <input type='text' name='newStatus'>
                <input type='submit' name='moveTask' value='Move task'>
            </form>";
    }
    echo "<br>";

    if (isset($_POST['moveTask'])) {
        $newStatus = $_POST['newStatus'];
        $taskId = (int)$_POST['taskId'];
        $task = $db->getTaskById($taskId);
        $oldStatus = $task['taskStatus'];
        if ($newStatus == $oldStatus) {
            echo "The task is already: {$oldStatus}";
        } else {
            if ($newStatus == "todo" || $newStatus == "in_progress" || $newStatus == "done") {
                $db->changeTaskStatus($taskId, $newStatus);
                $db->addTaskLogTable($taskId, $user['userId'], $oldStatus, $newStatus);
                $taskLog = $db->getTaskLogOfUserMoingTask($user['userId'], $taskId);
                header('Location: index.php');
                exit;
            } else {
                echo "Invalid status (valid: todo, in_progress, done)";
            }
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Management App</title>
</head>
<body>
    <p><a href="logout.php">Logout</a></p>
</body> 
</html>