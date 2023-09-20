#ifndef MAZE_H
#define MAZE_H
#include <Arduino.h>
#include "api.h"

class Maze
{

  int rows = 17;
  int cols = 17;
  int targetx = 7;
  int targety = 7;
  int X = 0;
  int Y = 0;
  int H[17][17];
  int V[17][17];
  int D[17][17];

public:
  bool isFinished();

  void intialize();

  void update();

  bool isValidIndex(int x, int y);
};
#endif