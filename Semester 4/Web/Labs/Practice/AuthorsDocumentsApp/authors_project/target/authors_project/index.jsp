<% if (request.getAttribute("error") != null) { %>
    <div style="color:red;"><%= request.getAttribute("error") %></div>
<% } %>

<form action="auth" method="post">
    Name: <input type="text" name="name" /><br/>
    Document or Movie ID/Name: <input type="text" name="authItem" /><br/>
    <input type="submit" value="Login" />
</form>
