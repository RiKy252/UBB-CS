<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Document with Most Authors</title>
</head>
<body>
<% if (request.getAttribute("error") != null) { %>
    <div style="color:red;"><%= request.getAttribute("error") %></div>
<% } else { %>
    <h3>Document with Most Authors</h3>
    <b>ID:</b> <%= request.getAttribute("docId") %><br/>
    <b>Name:</b> <%= request.getAttribute("docName") %><br/>
    <b>Contents:</b> <%= request.getAttribute("docContents") %><br/>
    <b>Number of Authors:</b> <%= request.getAttribute("authorCount") %><br/>
<% } %>
<a href="dashboard.jsp">Back to Dashboard</a>
</body>
</html> 