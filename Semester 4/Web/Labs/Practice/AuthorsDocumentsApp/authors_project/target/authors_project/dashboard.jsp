<h2>Welcome, <%= session.getAttribute("authorName") %></h2>
<a href="work">View My Work</a><br/>
<a href="addDocument.jsp">Add Document</a><br/>
<a href="mostAuthors">Show Document With Most Authors</a><br/>
<form action="deleteMovie" method="post">
    Movie ID to delete: <input type="text" name="movieId" />
    <input type="submit" value="Delete Movie" />
</form>
