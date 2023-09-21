#include "maze.h"

void Maze::intialize()
{
  setWall(1, 0, 'w');
  setColor(0, 0, 'G');
  setText(0, 0, "Start");
  setText(targetx, targety, "Goal");
  setColor(targetx, targety, 'B');
  for (int x = 0; x < cols; x++)
  {
    for (int y = 0; y < rows; y++)
    {
      if (y == 0)
      {
        H[x][y] = 1;
        setWall(x, y, 's');
      }
      else if (y == 16)
      {
        H[x][y] = 1;
        setWall(x, y - 1, 'n');
      }
      else
      {
        H[x][y] = 0;
      }

      if (x == 0)
      {
        V[x][y] = 1;
        setWall(x, y, 'w');
      }
      else if (x == 16)
      {
        V[x][y] = 1;
        setWall(x - 1, y, 'e');
      }
      else
      {
        V[x][y] = 0;
      }
    }
  }
  path = new short int *[32];
  for (int i = 0; i < 32; i++)
  {
    path[i] = new short int[2];
    path[i][0] = -1;
    path[i][1] = -1;
  }
}

bool Maze::isFinished()
{
  return X == targetx && Y == targety;
}

void Maze::update()
{
  for (int x = 0; x < cols; x++)
  {
    for (int y = 0; y < rows; y++)
    {
      if (H[x][y] == 1)
      {
        setWall(x, y, 's');
      }
      if (V[x][y] == 1)
      {
        setWall(8, 8, 'w');
      }
      setText(x, y, String(D[x][y]));
      setColor(x, y, 'k');
    }
  }
  setText(0, 0, "Start");
  setText(7, 7, "End");
}

bool Maze::isValidIndex(int x, int y)
{
  if (x < 0 || x >= cols || y < 0 || y >= rows)
  {
    return false;
  }
  return true;
}

void Maze::floodFill()
{
  Circular_Queue Q;
  for (int x = 0; x < cols; x++)
  {
    for (int y = 0; y < rows; y++)
    {
      D[x][y] = -1;
    }
  }

  Q.insert(7, 7);
  D[7][7] = 0;
  while (!Q.isEmpty())
  {
    int *r = Q.del();
    int x = r[0];
    int y = r[1];

    if (isValidIndex(x, y + 1) && !H[x][y + 1] && D[x][y + 1] == -1)
    {
      Q.insert(x, y + 1);
      D[x][y + 1] = D[x][y] + 1;
    }
    if (isValidIndex(x - 1, y) && !V[x][y] && D[x - 1][y] == -1)
    {
      Q.insert(x - 1, y);
      D[x - 1][y] = D[x][y] + 1;
    }
    if (isValidIndex(x, y - 1) && !H[x][y] && D[x][y - 1] == -1)
    {
      Q.insert(x, y - 1);
      D[x][y - 1] = D[x][y] + 1;
    }
    if (isValidIndex(x + 1, y) && !V[x + 1][y] && D[x + 1][y] == -1)
    {
      Q.insert(x + 1, y);
      D[x + 1][y] = D[x][y] + 1;
    }
    delay(200);
  }
}

void Maze::turn(int dir)
{
  if (abs(dir - d) == 2)
  {
    turnLeft();
    turnLeft();
  }
  else if (dir - d == 1)
  {
    turnRight();
  }
  else if (dir - d == -1)
  {
    turnLeft();
  }
  else if (dir - d == 3)
  {
    turnLeft();
  }
  else if (dir - d == -3)
  {
    turnRight();
  }
  d = dir;
}

void Maze::findPath()
{
  int x = X;
  int y = Y;
  for (int i = 0; i < 32; i++)
  {
    path[i][0] = -1;
    path[i][1] = -1;
  }
  int k = 0;
  while (x != 7 || y != 7)
  {
    if (isValidIndex(x, y + 1) && D[x][y + 1] == D[x][y] - 1 && H[x][y + 1] == 0)
    {
      path[k][0] = x;
      path[k][1] = y + 1;
      k++;
      setColor(x, y + 1, 'Y');
      y++;
    }
    else if (isValidIndex(x + 1, y) && D[x + 1][y] == D[x][y] - 1 && V[x + 1][y] == 0)
    {
      path[k][0] = x + 1;
      path[k][1] = y;
      k++;
      setColor(x + 1, y, 'Y');
      x++;
    }
    else if (isValidIndex(x, y - 1) && D[x][y - 1] == D[x][y] - 1 && H[x][y] == 0)
    {
      path[k][0] = x;
      path[k][1] = y - 1;
      k++;
      setColor(x, y - 1, 'Y');
      y--;
    }
    else if (isValidIndex(x - 1, y) && D[x - 1][y] == D[x][y] - 1 && V[x][y] == 0)
    {
      path[k][0] = x - 1;
      path[k][1] = y;
      k++;
      setColor(x - 1, y, 'Y');
      x--;
    }
    else
    {
      log("Error: No path found");
      break;
    }
  }
  return path;
}

void Maze::setWallDir(int dir)
{
  if (d == 0)
  {
    if (dir == 0)
    {
      H[X][Y + 1] = 1;
      setWall(X, Y, 'n');
    }
    else if (dir == 1)
    {
      V[X + 1][Y] = 1;
      setWall(X, Y, 'e');
    }
    else if (dir == 2)
    {
      H[X][Y] = 1;
      setWall(X, Y, 's');
    }
    else if (dir == 3)
    {
      V[X][Y] = 1;
      setWall(X, Y, 'w');
    }
  }
  else if (d == 1)
  {
    if (dir == 0)
    {
      V[X + 1][Y] = 1;
      setWall(X, Y, 'e');
    }
    else if (dir == 1)
    {
      H[X][Y] = 1;
      setWall(X, Y, 's');
    }
    else if (dir == 2)
    {
      V[X][Y] = 1;
      setWall(X, Y, 'w');
    }
    else if (dir == 3)
    {
      H[X][Y + 1] = 1;
      setWall(X, Y, 'n');
    }
  }
  else if (d == 2)
  {
    if (dir == 0)
    {
      H[X][Y] = 1;
      setWall(X, Y, 's');
    }
    else if (dir == 1)
    {
      V[X][Y] = 1;
      setWall(X, Y, 'w');
    }
    else if (dir == 2)
    {
      H[X][Y + 1] = 1;
      setWall(X, Y, 'n');
    }
    else if (dir == 3)
    {
      V[X + 1][Y] = 1;
      setWall(X, Y, 'e');
    }
  }
  else if (d == 3)
  {
    if (dir == 0)
    {
      V[X][Y] = 1;
      setWall(X, Y, 'w');
    }
    else if (dir == 1)
    {
      H[X][Y + 1] = 1;
      setWall(X, Y, 'n');
    }
    else if (dir == 2)
    {
      V[X + 1][Y] = 1;
      setWall(X, Y, 'e');
    }
    else if (dir == 3)
    {
      H[X][Y] = 1;
      setWall(X, Y, 's');
    }
  }
}

bool Maze::getWall(int dir)
{
  if (d == 0)
  {
    if (dir == 0)
    {
      return wallFront();
    }
    else if (dir == 1)
    {
      return wallRight();
    }
    else if (dir == 2)
    {
      return 0;
    }
    else if (dir == 3)
    {
      return wallLeft();
    }
  }
  else if (d == 1)
  {
    if (dir == 0)
    {
      return wallLeft();
    }
    else if (dir == 1)
    {
      return wallFront();
    }
    else if (dir == 2)
    {
      return wallRight();
    }
    else if (dir == 3)
    {
      return 0;
    }
  }
  else if (d == 2)
  {
    if (dir == 0)
    {
      return 0;
    }
    else if (dir == 1)
    {
      return wallLeft();
    }
    else if (dir == 2)
    {
      return wallFront();
    }
    else if (dir == 3)
    {
      return wallRight();
    }
  }
  else if (d == 3)
  {
    if (dir == 0)
    {
      return wallRight();
    }
    else if (dir == 1)
    {
      return 0;
    }
    else if (dir == 2)
    {
      return wallLeft();
    }
    else if (dir == 3)
    {
      return wallFront();
    }
  }
}

void Maze::moveForward()
{
  moveForward();
  if (wallLeft())
  {
    setColor(X, Y, 'G');
    setWallDir(3);
  }
  if (wallRight())
  {
    setColor(X, Y, 'G');
    setWallDir(1);
  }
  if (wallFront())
  {
    setColor(X, Y, 'G');
    setWallDir(0);
  }
}

void Maze::explore()
{
  findPath();
  int pathLength = sizeof(path) / sizeof(path[0]);
  for (int i = 0; i < pathLength; i++)
  {
    int x = path[i][0];
    int y = path[i][1];
    bool wallFound = false;
    // console.error(`Current - (${this.x}, ${this.y}), Target - (${x}, ${y})Direction - $ { this.d }`);
    if ((y - Y) == 1)
    {
      if (getWall(0))
      {
        H[X][Y + 1] = 1;
        wallFound = true;
      }
      else
      {
        turn(0);
        Y++;
        moveForward();
      }
    }
    else if (y - Y == -1)
    {
      if (getWall(2))
      {
        H[X][Y] = 1;
        wallFound = true;
      }
      else
      {
        turn(2);
        Y--;
        moveForward();
      }
    }
    else if (x - X == 1)
    {
      if (getWall(1))
      {
        V[X + 1][Y] = 1;
        wallFound = true;
      }
      else
      {
        turn(1);
        X++;
        moveForward();
      }
    }
    else if (x - X == -1)
    {
      if (getWall(3))
      {
        V[X][Y] = 1;
        wallFound = true;
      }
      else
      {
        turn(3);
        X--;
        moveForward();
      }
    }
    if (wallFound)
    {
      // console.error(`Wall found at(${x}, ${y})`);
      break;
    }
  }
}
