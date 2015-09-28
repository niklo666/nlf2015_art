#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <Adafruit_NeoPixel.h>


/*
  light node
  lighting behaviour needed/wanted:
  - "static" color, used for dna strand, only subject to dimming and possibly "living" colors i.e. glimmering effect using random colors from palette 
  - "static" color, used for strands, possibly more vivid than dna otherwise same or similar
  - "static" colors, used for mouths and eyes, probably only dimming with one static color per item

  communication could be by CAN as it can handle distance and is quite resistant to disturbances *AND* is bidirectional.
  
  possibly separate applications distributed over several nodes for differens areas.
  in that case a lib should be developed and used.
  a big issue is the not very user-friendlyness of the arduino ide in that you cannot:
  - have several source files
  - cannot easily compile from commandline
  - no real control of library versions etc.

*/

void setup()
{
  // put your setup code here, to run once:

  // todo: init lighting stuff...
  // - init power control io and see to that power is turned off
  // - init ws2801 control io and see to that leds are off
  // - init datastructures

  // todo: init comm stuff...
  // - ...
}

void loop() 
{
  // put your main code here, to run repeatedly:

  // todo: react on comm inputs...

  // todo: do autonomous stuff e.g. dimming, contingency/"idle" mode behaviour...

  // todo: update lighting...

}
