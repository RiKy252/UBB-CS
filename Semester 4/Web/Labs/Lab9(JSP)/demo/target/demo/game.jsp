<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    String username = (String) session.getAttribute("user");
    if (username == null) {
        response.sendRedirect("login.jsp");
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Battleships Game</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f0f0f0;
        }
        .game-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        .boards-container {
            display: flex;
            justify-content: center;
            gap: 50px;
            margin: 20px 0;
        }
        .board {
            display: inline-block;
            background-color: #e8e8e8;
            padding: 10px;
            border-radius: 5px;
        }
        .cell {
            width: 40px;
            height: 40px;
            border: 1px solid #999;
            display: inline-block;
            text-align: center;
            line-height: 40px;
            cursor: pointer;
            background-color: #fff;
            transition: background-color 0.3s;
        }
        .cell:hover {
            background-color: #e0e0e0;
        }
        .row {
            display: block;
        }
        .hit {
            background-color: #ff4444 !important;
            color: white;
        }
        .miss {
            background-color: #4444ff !important;
            color: white;
        }
        .ship {
            background-color: #666;
        }
        #status {
            margin: 20px;
            padding: 15px;
            border: 1px solid #ccc;
            background-color: #f8f8f8;
            text-align: center;
            border-radius: 5px;
            font-size: 1.2em;
            min-width: 200px;
        }
        .user-info {
            margin: 10px 0;
            text-align: center;
            font-size: 1.2em;
            color: #333;
        }
        .logout {
            margin: 10px 0;
            text-align: center;
        }
        .logout a {
            color: #333;
            text-decoration: none;
            padding: 8px 15px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f8f8f8;
            transition: background-color 0.3s;
        }
        .logout a:hover {
            background-color: #e0e0e0;
        }
        .legend {
            margin: 20px 0;
            padding: 10px;
            background-color: #f8f8f8;
            border-radius: 5px;
            text-align: center;
        }
        .legend-item {
            display: inline-block;
            margin: 0 10px;
        }
        .legend-color {
            display: inline-block;
            width: 20px;
            height: 20px;
            margin-right: 5px;
            vertical-align: middle;
        }
    </style>
</head>
<body>
    <div class="game-container">
        <h1>Battleships Game</h1>
        
        <div class="user-info">
            Logged in as: <%= username %>
        </div>

        <div class="boards-container">
            <div>
                <h2>Your Board</h2>
                <div class="board" id="playerBoard">
                    <% for(int i = 0; i < 10; i++) { %>
                        <div class="row">
                            <% for(int j = 0; j < 10; j++) { %>
                                <div class="cell" data-row="<%=i%>" data-col="<%=j%>"></div>
                            <% } %>
                        </div>
                    <% } %>
                </div>
            </div>

            <div>
                <h2>Opponent's Board</h2>
                <div class="board" id="opponentBoard">
                    <% for(int i = 0; i < 10; i++) { %>
                        <div class="row">
                            <% for(int j = 0; j < 10; j++) { %>
                                <div class="cell" data-row="<%=i%>" data-col="<%=j%>" onclick="makeMove(this)"></div>
                            <% } %>
                        </div>
                    <% } %>
                </div>
            </div>
        </div>

        <div class="legend">
            <div class="legend-item">
                <span class="legend-color" style="background-color: #ff4444;"></span>
                Hit
            </div>
            <div class="legend-item">
                <span class="legend-color" style="background-color: #4444ff;"></span>
                Miss
            </div>
            <div class="legend-item">
                <span class="legend-color" style="background-color: #666;"></span>
                Ship
            </div>
        </div>

        <div id="status">Waiting for opponent...</div>

        <div class="logout">
            <a href="LogoutServlet">Logout</a>
        </div>
    </div>

    <script>
        function makeMove(cell) {
            if (cell.classList.contains('hit') || cell.classList.contains('miss')) {
                return; // Cell already played
            }
            
            const row = cell.getAttribute('data-row');
            const col = cell.getAttribute('data-col');
            
            fetch('GameServlet', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: `row=${row}&col=${col}`
            })
            .then(response => response.text())
            .then(result => {
                console.log('Move result:', result); // Debug log
                if(result.includes('Hit')) {
                    cell.classList.add('hit');
                } else if(result.includes('Miss')) {
                    cell.classList.add('miss');
                } else if(result.includes('Not your turn')) {
                    alert('Not your turn!');
                } else if(result.includes('Move already made')) {
                    alert('This move was already made!');
                } else if(result.includes('No active game')) {
                    alert('No active game found!');
                } else if(result.includes('Game Over')) {
                    alert(result);
                    location.reload(); // Reload page when game is over
                }
                document.getElementById('status').textContent = result;
            })
            .catch(error => {
                console.error('Error:', error); // Debug log
                document.getElementById('status').textContent = 'Error: ' + error;
            });
        }

        // Poll for game updates
        setInterval(() => {
            fetch('GameServlet')
            .then(response => response.text())
            .then(status => {
                console.log('Status update:', status); // Debug log
                document.getElementById('status').textContent = status;
                
                // If game is over, reload the page
                if(status.includes('Game Over')) {
                    location.reload();
                }
            })
            .catch(error => {
                console.error('Status error:', error); // Debug log
            });
        }, 2000);
    </script>
</body>
</html>