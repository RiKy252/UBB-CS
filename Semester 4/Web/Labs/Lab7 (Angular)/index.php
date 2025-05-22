<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Vacation Destinations</title>
  <style>
    .destination { margin-bottom: 20px; }
    .actions { margin-top: 10px; }
    input[type="text"] { width: 200px; }
  </style>
  <script>
    let currentPage = 1;

    function fetchDestinations(country = '', page = 1) {
      fetch(`get_destinations.php?country=${country}&page=${page}`)
        .then(response => response.json())
        .then(data => {
          let container = document.getElementById('results');
          container.innerHTML = '';
          data.destinations.forEach(dest => {
            container.innerHTML += `
              <div class="destination">
                <h3>${dest.location} (${dest.country})</h3>
                <p>${dest.description}</p>
                <p><strong>Targets:</strong> ${dest.tourist_targets}</p>
                <p><strong>Cost/Day:</strong> $${dest.cost_per_day}</p>
                <div class="actions">
                  <button onclick="editDestination(${dest.id})">Edit</button>
                  <button onclick="deleteDestination(${dest.id})">Delete</button>
                </div>
              </div>
            `;
          });

          document.getElementById('page-info').innerText = `Page ${data.page}`;
          currentPage = data.page;
        });
    }

    function deleteDestination(id) {
      if (confirm('Are you sure you want to delete this destination?')) {
        const formData = new FormData();
        formData.append('id', id);
 
        fetch('delete_destination.php', {
          method: 'POST',
          body: formData
        })
        .then(response => response.json())
        .then(data => {
          if (data.success) {
            fetchDestinations(document.getElementById('filter').value, currentPage);
          } else {
            alert('Failed to delete destination');
          }
        })
        .catch(error => {
          console.error('Error:', error);
          alert('An error occurred while deleting the destination');
        });
      }
    }

    function editDestination(id) {
      window.location.href = `edit_destination.php?id=${id}`;
    }

    function nextPage() {
      fetchDestinations(document.getElementById('filter').value, currentPage + 1);
    }

    function prevPage() {
      if (currentPage > 1)
        fetchDestinations(document.getElementById('filter').value, currentPage - 1);
    }
  </script>
</head>
<body onload="fetchDestinations()">
  <div class="container">
    <h1>Vacation Destinations</h1>
    
    <label for="filter">Filter by country:</label>
    <input type="text" id="filter" onkeyup="fetchDestinations(this.value)">
    
    <div id="results"></div>
    
    <button onclick="prevPage()">Previous</button>
    <span id="page-info">Page 1</span>
    <button onclick="nextPage()">Next</button>
    <br><br>
    <a href="add_destination.php">Add a New Destination</a>
  </div>
</body>
</html>
