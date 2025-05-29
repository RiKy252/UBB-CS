<%@ page session="true" %>
<%
    String user = (String) session.getAttribute("user");
    if (user == null) {
        response.sendRedirect("login.jsp");
        return;
    }
%>
<html>
<head>
    <title>Battleship Game</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <h1>Welcome, <%= user %></h1>
    <div id="game-board">Game board goes here</div>
    <a href="LogoutServlet">Logout</a>
</body>
</html>