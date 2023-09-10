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

    while(!maze.isFinished()) {
        maze.floodFill()
        maze.update();
        maze.explore();

        maze.floodFill();
        maze.update();
        maze.explore();

        maze.floodFill();
        maze.update();
        maze.explore();
    }
    // maze.floodFill();
    // maze.update();
    // maze.findPath(0,0);
}

main();
