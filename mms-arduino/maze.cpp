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
        setWall(x, y, 'w');
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
  if (x < 0 || x >= cols || y < 0 || y > rows)
  {
    return false;
  }
  return true;
}