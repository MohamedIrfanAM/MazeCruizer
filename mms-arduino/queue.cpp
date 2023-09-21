#include "queue.h"
#define MAX 255

Circular_Queue::Circular_Queue()
{
  rear = front = -1;
  cqueue_arr = new short int *[MAX];
  for (int i = 0; i < MAX; i++)
  {
    cqueue_arr[i] = new short int[2];
  }
}

void Circular_Queue::insert(int x, int y)
{
  if ((front == 0 && rear == MAX - 1) || (front == rear + 1))
  {
    return;
  }
  if (front == -1)
  {
    front = 0;
    rear = 0;
  }
  else
  {
    if (rear == MAX - 1)
      rear = 0;
    else
      rear = rear + 1;
  }
  cqueue_arr[rear][0] = x;
  cqueue_arr[rear][1] = y;
}

short int *Circular_Queue::del()
{
  if (front == -1)
  {
    Serial.println("Queue Underflow\n");
    return -1;
  }
  return cqueue_arr[front];
  if (front == rear)
  {
    front = -1;
    rear = -1;
  }
  else
  {
    if (front == MAX - 1)
      front = 0;
    else
      front = front + 1;
  }
};

bool Circular_Queue::isEmpty()
{
  return front == -1;
}