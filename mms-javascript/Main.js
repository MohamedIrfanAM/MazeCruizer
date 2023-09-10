const API = require('./API');
const Maze = require('./maze.js');

function log(text) {
    console.error(text);
}

var rows = API.mazeHeight()+1;
var cols = API.mazeWidth()+1;

var maze = new Maze(rows,cols);

function main() {
    log("Running...");
    maze.initialize();
    maze.floodFill()
    maze.update()

    while (true) {
        if (!API.wallLeft()) {
            API.turnLeft();
        }
        while (API.wallFront()) {
            API.turnRight();
        }
        API.moveForward();
    }
}

main();
