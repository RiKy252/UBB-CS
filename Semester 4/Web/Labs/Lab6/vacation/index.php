<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Vacation Destinations</title>
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
              <div>
                <h3>${dest.location} (${dest.country})</h3>
                <p>${dest.description}</p>
                <p><strong>Targets:</strong> ${dest.tourist_targets}</p>
                <p><strong>Cost/Day:</strong> $${dest.cost_per_day}</p>
              </div><hr>
            `;
          });

          document.getElementById('page-info').innerText = `Page ${data.page}`;
          currentPage = data.page;
        });
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
  <h1>Vacation Destinations</h1>
  
  <label for="filter">Filter by country:</label>
  <input type="text" id="filter" onkeyup="fetchDestinations(this.value)">
  
  <div id="results"></div>
  
  <button onclick="prevPage()">Previous</button>
  <span id="page-info">Page 1</span>
  <button onclick="nextPage()">Next</button>
</body>
</html>
