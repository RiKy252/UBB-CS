const size = 3;
let tiles = [0, 1, 2, 3, 4, 5, 6, 7, 8];

function isSolved() {
    return tiles.every((num, idx) => num === idx);
}

function shuffleTilesOnLoad() {
    while (isSolved())
        tiles = tiles.sort(() => Math.random() - 0.5);   
    renderTiles(); 
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
        // puts each part of the photo in the corresponding tile
        tile.style.backgroundPosition = `${col * -100}% ${row * -100}%`;
        
        tile.addEventListener("dragstart", (e) => {
            e.dataTransfer.setData("text/plain", idx);
        });
        
        // without this u can't drop
        tile.addEventListener("dragover", (e) => {
            e.preventDefault();      
        });
        
        tile.addEventListener("drop", (e) => {
            e.preventDefault(); // this allows the drop 
            const fromIndex = e.dataTransfer.getData("text/plain");
            const toIndex = idx;
            const aux = tiles[fromIndex];
            tiles[fromIndex] = tiles[toIndex];
            tiles[toIndex] = aux;
            renderTiles();
            if (isSolved()) {
                document.getElementById("message").textContent = "Well done!";
            }
        });
        
        puzzle.appendChild(tile);
    });
}


renderTiles();
shuffleTilesOnLoad();
