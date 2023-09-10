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
            }
        }
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
}

module.exports = Maze;