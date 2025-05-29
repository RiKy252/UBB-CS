function sendMove(row, col) {
    const xhr = new XMLHttpRequest();
    xhr.open("POST", "GameServlet", true);
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.onload = function() {
        document.getElementById("game-board").innerHTML = xhr.responseText;
    };
    xhr.send("row=" + row + "&col=" + col);
}