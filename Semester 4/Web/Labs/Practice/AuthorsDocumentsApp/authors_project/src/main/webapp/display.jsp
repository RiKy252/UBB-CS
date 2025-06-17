<%@ page import="java.util.List" %>
<%
    List<String> results = (List<String>) request.getAttribute("results");
    if (results != null && !results.isEmpty()) {
        for (String item : results) {
%>
            <p><%= item %></p>
<%
        }
    } else {
%>
        <p>No authored documents or movies.</p>
<%
    }
%>
<a href="dashboard.jsp">Back to Dashboard</a>
