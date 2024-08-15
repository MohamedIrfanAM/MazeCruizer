#include "bot.h"

Bot bot;
void setup()
{
  bot.initialize();
  Serial.begin(9600);
}

void loop()
{
  delay(10);
}