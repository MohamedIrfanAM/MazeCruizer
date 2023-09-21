#ifndef QUEUE_H
#define QUEUE_H
#include <Arduino.h>

class Circular_Queue
{
private:
  int **cqueue_arr;
  int front, rear;

public:
  Circular_Queue();
  void insert(int x, int y);
  short int *del();
  bool isEmpty();
};
#endif