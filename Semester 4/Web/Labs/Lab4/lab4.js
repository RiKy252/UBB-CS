const size = 3;
let tiles = [...Array(size * size).keys()];

function isSolved() {
    return tiles.every((num, idx) => num === idx);
}

function shuffleTilesOnLoad() {
    while (isSolved())
        tiles = tiles.sort(() => Math.random() - 0.5);    
}

function renderTiles() {
    const puzzle = document.getElementById("puzzle");
    puzzle.innerHTML = "";
    tiles.forEach((num, idx) => {
        const tile = document.createElement("div");
        tile.className = "tile";
        tile.draggable = true;
        tile.dataset.index = idx;
        
        const row = Math.floor(num / size);
        const col = num % size;
        // m[0][1] => -100% 0%
        tile.style.backgroundPosition = `${col * -100}% ${row * -100}%`;
        
        tile.addEventListener("dragstart", (e) => {
            e.dataTransfer.setData("text/plain", idx);
        });
        
        tile.addEventListener("dragover", (e) => {
            e.preventDefault();         
        });
        
        tile.addEventListener("drop", (e) => {
            e.preventDefault();
            const fromIndex = e.dataTransfer.getData("text/plain");
            const toIndex = idx;
            [tiles[fromIndex], tiles[toIndex]] = [tiles[toIndex], tiles[fromIndex]];
            renderTiles();
            if (isSolved()) {
                document.getElementById("message").textContent = "Well done!";
            }
        });
        
        puzzle.appendChild(tile);
    });
}

shuffleTilesOnLoad();
renderTiles();