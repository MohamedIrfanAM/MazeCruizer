#include "bot.h"

void setup()
{
  Bot bot;
  bot.initialize();
}

void loop()
{
  Bot bot;
  bot.initialize();
  bot.forward();
  bot.right();
  bot.left();
  bot.stop();
  bot.forward();
}