#include "bot.h"

Bot bot;
void setup()
{
  bot.initialize();
}

void loop()
{
  if (bot.frontWall())
  {
    Serial.println("Front Wall");
    bot.right(175);
    delay(100);
    bot.forward();
  }
  else if (bot.rightWall())
  {
    bot.right(45);
    Serial.println("No Wall,going forward");
  }
  else if (bot.leftWall())
  {
    bot.left(45);
    Serial.println("No Wall,going forward");
  }
  else if(!bot.frontWall()){
    bot.forward();
  }
  delay(100);
}