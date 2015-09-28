#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

void setup() 
{
  // put your setup code here, to run once:

  // todo: init comm...
  // - interrupt...

  // todo: init dimming...
  // - zero cross detect pin
  // - triac control pin(s)
  // - zero cross interrupt!?
  // - timer with interrupt for dimming
}

void loop() 
{
  // put your main code here, to run repeatedly:

  // todo: handle incoming comm...

  // todo: loop to control dimming...
}
