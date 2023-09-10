const { execFile } = require('child_process');
const API = require('./API.js');
const queue = require('./queue.js')
var Q = new queue(256);

class Maze {
    constructor(rows,cols){
        this.rows = rows;
        this.cols = cols;
        this.H = new Array(cols);
        this.V = new Array(cols);
        this.D = new Array(cols);
        this.x = 0;
        this.y = 0;
        this.d = 0;
        for (let x = 0; x < cols; x++) {
            this.H[x] = new Array(rows);
            this.V[x] = new Array(rows);
            this.D[x] = new Array(rows);
        }
    }

    initialize (){
        API.setWall(1,0,'w');
        API.setColor(0, 0, 'G');
        API.setText(0, 0, "Start");
        API.setText(7, 7, "Goal");
        API.setColor(7, 7, 'B');
        for(let x = 0; x < this.cols; x++) {
            for(let y = 0; y < this.rows; y++) {
                if(y == 0){
                    this.H[x][y] = 1;
                    API.setWall(x,y,'s')
                }
                else if(y == 16){
                    this.H[x][y] = 1;
                    API.setWall(x,y-1,'n')
                }
                else{
                    this.H[x][y] = 0;
                }

                if(x == 0){
                    this.V[x][y] = 1;
                    API.setWall(x,y,'w')
                }
                else if(x == 16){
                    this.V[x][y] = 1;
                    API.setWall(x-1,y,'e')
                }
                else{
                    this.V[x][y] = 0;
                }
            }
        }
    }

    update (){
        for(var x = 0; x < this.cols; x++) {
            for(var y = 0; y < this.rows; y++) {
                if(this.H[x][y] == 1){
                    API.setWall(x,y,'s');
                }
                if(this.V[x][y] == 1){
                    API.setWall(x,y,'w');
                }
                API.setText(x,y,this.D[x][y]);
                API.setColor(x,y,'k');
            }
        }
        API.setText(0, 0, "Start");
        API.setText(7, 7, "End");
    }

    isValidIndex(x,y){
        if(x < 0 || x >= this.cols || y < 0 || y > this.rows){
            return false;
        }
        return true;
    }

    floodFill(){
        for(var x = 0; x < this.cols; x++){
            for(var y = 0; y < this.rows; y++){
                this.D[x][y] = -1;
            }
        }
        console.error('Starting flood fill');
        Q.enqueue([7,7]);
        this.D[7][7] = 0;
        while(!Q.isEmpty()){
            const [x,y] = Q.dequeue();
            if(this.isValidIndex(x,y+1,this.rows,this.cols) && !this.H[x][y+1] && this.D[x][y+1] == -1){
                Q.enqueue([x,y+1]);
                this.D[x][y+1] = this.D[x][y] + 1;
            }
            if(this.isValidIndex(x-1,y,this.rows,this.cols) && !this.V[x][y] && this.D[x-1][y] == -1){
                Q.enqueue([x-1,y]);
                this.D[x-1][y] = this.D[x][y] + 1;
            }
            if(this.isValidIndex(x,y-1,this.rows,this.cols) && !this.H[x][y] && this.D[x][y-1] == -1){
                Q.enqueue([x,y-1]);
                this.D[x][y-1] = this.D[x][y] + 1;
            }
            if(this.isValidIndex(x+1,y,this.rows,this.cols) && !this.V[x+1][y] && this.D[x+1][y] == -1){
                Q.enqueue([x+1,y]);
                this.D[x+1][y] = this.D[x][y] + 1;
            }
        }
    }

    findPath(x=this.x,y=this.y){
        let path = [];
        while(x != 7 || y != 7){
            if(this.isValidIndex(x,y+1) && this.D[x][y+1] == this.D[x][y] - 1 && this.H[x][y+1] == 0){
                path.push([x,y+1]);
                API.setColor(x, y+1, 'Y');
                y++;
            }
            else if(this.isValidIndex(x+1,y) && this.D[x+1][y] == this.D[x][y] - 1 && this.V[x+1][y] == 0){
                path.push([x+1,y]);
                API.setColor(x+1, y, 'Y');
                x++;
            }
            else if(this.isValidIndex(x,y-1) &&  this.D[x][y-1] == this.D[x][y] - 1 && this.H[x][y] == 0){
                path.push([x,y-1]);
                API.setColor(x, y-1, 'Y');
                y--;
            }
            else if(this.isValidIndex(x-1,y) && this.D[x-1][y] == this.D[x][y] - 1 && this.V[x][y] == 0){
                path.push([x-1,y]);
                API.setColor(x-1, y, 'Y');
                x--;
            }
            else{
                console.log("Cannot find path");
            }
        }
        return path;
    }

    turn(d){
        if(Math.abs(d-this.d) == 2){
            API.turnLeft();
            API.turnLeft();
        }
        else if(d-this.d == 1){
            API.turnRight();
        }
        else if(d-this.d == -1){
            API.turnLeft();
        }
        else if(d-this.d == 3){
            API.turnLeft();
        }
        else if(d-this.d == -3){
            API.turnRight();
        }
        this.d = d;
    }

    setWall(d){
        if(this.d == 0){
            if(d == 0){
                this.H[this.x][this.y+1] = 1;
                API.setWall(this.x,this.y,'n');
            }
            else if(d == 1){
                this.V[this.x+1][this.y] = 1;
                API.setWall(this.x,this.y,'e');
            }
            else if(d == 2){
                this.H[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'s');
            }
            else if(d == 3){
                this.V[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'w');
            }
        }
        else if(this.d == 1){
            if(d == 0){
                this.V[this.x+1][this.y] = 1;
                API.setWall(this.x,this.y,'e');
            }
            else if(d == 1){
                this.H[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'s');
            }
            else if(d == 2){
                this.V[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'w');
            }
            else if(d == 3){
                this.H[this.x][this.y+1] = 1;
                API.setWall(this.x,this.y,'n');
            }
        }
        else if(this.d == 2){
            if(d == 0){
                this.H[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'s');
            }
            else if(d == 1){
                this.V[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'w');
            }
            else if(d == 2){
                this.H[this.x][this.y+1] = 1;
                API.setWall(this.x,this.y,'n');
            }
            else if(d == 3){
                this.V[this.x+1][this.y] = 1;
                API.setWall(this.x,this.y,'e');
            }
        }
        else if(this.d == 3){
            if(d == 0){
                this.V[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'w');
            }
            else if(d == 1){
                this.H[this.x][this.y+1] = 1;
                API.setWall(this.x,this.y,'n');
            }
            else if(d == 2){
                this.V[this.x+1][this.y] = 1;
                API.setWall(this.x,this.y,'e');
            }
            else if(d == 3){
                this.H[this.x][this.y] = 1;
                API.setWall(this.x,this.y,'s');
            }
        }
    }

    getWall(d){
        if(this.d == 0){
            if(d == 0){
                return API.wallFront();
            }
            else if(d == 1){
                return API.wallRight();
            }
            else if(d == 2){
                return 0;
            }
            else if(d == 3){
                return API.wallLeft();
            }
        }
        else if(this.d == 1){
            if(d == 0){
                return API.wallLeft();
            }
            else if(d == 1){
                return API.wallFront();
            }
            else if(d == 2){
                return API.wallRight();
            }
            else if(d == 3){
                return 0;
            }
        }
        else if(this.d == 2){
            if(d == 0){
                return 0;
            }
            else if(d == 1){
                return API.wallLeft();
            }
            else if(d == 2){
                return API.wallFront();
            }
            else if(d == 3){
                return API.wallRight();
            }
        }
        else if(this.d == 3){
            if(d == 0){
                return API.wallRight();
            }
            else if(d == 1){
                return 0;
            }
            else if(d == 2){
                return API.wallLeft();
            }
            else if(d == 3){
                return API.wallFront();
            }
        }
    }

    moveForward(){
        API.moveForward();
        if(API.wallLeft()){
            API.setColor(this.x,this.y,'G');
            this.setWall(3);
        }
        if(API.wallRight()){
            API.setColor(this.x,this.y,'G');
            this.setWall(1);
        }
        if(API.wallFront()){
            API.setColor(this.x,this.y,'G');
            this.setWall(0);
        }
    }

    explore(){
        let path = this.findPath();
        console.log(path)
        for(let i = 0; i < path.length; i++){
            let [x,y] = path[i];
            let wallFound = false;
            console.error(`Current - (${this.x},${this.y}), Target - (${x},${y}) Direction - ${this.d}`);
            if((y-this.y) == 1){
                if(this.getWall(0)){
                    this.H[this.x][this.y+1] = 1;
                    wallFound = true;
                }
                else{
                    this.turn(0);
                    this.y++;
                    this.moveForward();
                }
            }
            else if(y-this.y == -1){
                if(this.getWall(2)){
                    this.H[this.x][this.y] = 1;
                    wallFound = true;
                }
                else{
                    this.turn(2);
                    this.y--;
                    this.moveForward();
                }
            }
            else if(x-this.x == 1){
                if(this.getWall(1)){
                    this.V[this.x+1][this.y] = 1;
                    wallFound = true;
                }
                else{
                    this.turn(1);
                    this.x++;
                    this.moveForward();
                }
            }
            else if(x-this.x == -1){
                if(this.getWall(3)){
                    this.V[this.x][this.y] = 1;
                    wallFound = true;
                }
                else{
                    this.turn(3);
                    this.x--;
                    this.moveForward();
                }
            }
            if(wallFound){
                console.error(`Wall found at (${x},${y})`);
                break;
            }
        }
    }

    isFinished(){
        if(this.x == 7 && this.y == 7){
            return true;
        }
        return false;
    }
}

module.exports = Maze;