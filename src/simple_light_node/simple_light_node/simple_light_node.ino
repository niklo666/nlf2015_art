

// pin definitions...
const int activity_led_pin      = 13; // the number of the LED pin

const int light_channel0_clock  = 3; 
const int light_channel0_data   = 2;
const int light_channel1_clock  = 5;
const int light_channel1_data   = 4;
const int light_channel2_clock  = 7;
const int light_channel2_data   = 6;
const int light_channel3_clock  = 9;
const int light_channel3_data   = 8;
const int light_channel4_clock  = 11;
const int light_channel4_data   = 10;
const int light_channel5_clock  = 13;   // todo: possible collision with activity LED...
const int light_channel5_data   = 12;


// led data...
const int strands_front_number_of_leds  = 100;      // split in half...
const int strands_rear_number_of_leds   = 100;      // split in half...
const int eyes_number_of_leds           = 100;      // for now assume both symbols use 50 LEDs and are in serial...
const int lips_number_of_leds           = 150;      // for now assume all three symbols use 50 LEDs and are in serial...
const int text0_number_of_leds          = 50;       // one strand to light up "In Lust"...
const int text1_number_of_leds          = 50;       // one strand to light up "We Trust"...
CRGB front_strand_leds[strands_front_number_of_leds];           // number of leds in the strands...
CRGB rear_strand_leds[strands_rear_number_of_leds];           // number of leds in the strands...
CRGB eyes_leds[eyes_number_of_leds];                // number of leds in the strands...
CRGB lips_leds[lips_number_of_leds];                // number of leds in the strands...
CRGB text0_leds[text0_number_of_leds];              // number of leds in the strands...
CRGB text1_leds[text1_number_of_leds];              // number of leds in the strands...


void setup() 
{
 // init on-board teensy LED to use as activity indicator...
  pinMode(activity_led_pin, OUTPUT);

  // init lighting stuff...
  // - todo: init mains power control(dimmer) io and see to that power is turned off...
  // - todo: init camera node power control...
  // - init ws2801 control io and see to that leds are off...
  FastLED.addLeds<WS2801, light_channel0_data, light_channel0_clock, RGB>(front_strand_leds, strands_front_number_of_leds);
  FastLED.addLeds<WS2801, light_channel1_data, light_channel1_clock, RGB>(rear_strand_leds, strands_rear_number_of_leds);
  FastLED.addLeds<WS2801, light_channel2_data, light_channel2_clock, RGB>(eyes_leds, eyes_number_of_leds);
  FastLED.addLeds<WS2801, light_channel3_data, light_channel3_clock, RGB>(lips_leds, lips_number_of_leds);
  FastLED.addLeds<WS2801, light_channel4_data, light_channel4_clock, RGB>(text0_leds, text0_number_of_leds);
  FastLED.addLeds<WS2801, light_channel5_data, light_channel5_clock, RGB>(text1_leds, text1_number_of_leds);

  // init datastructures...
  // todo: clear command buffer...
  // todo: clear reponse buffer...
  
  // init debug serial port...
  // for use on mac/pc...
  Serial.begin(9600);

  // init rpi communication port...
  // todo: select proper serial port speed...
  // trial and error tells that 115200 works ok!
  // used for live input from teensy...
  Serial1.begin(115200, SERIAL_8N1);
}


void lips(CRGB color);
void eyes(CRGB color);


void loop() 
{
  /*
    vad som ska hända:
    - läpparna "slänger kyssar"...
      tänd en i taget sen lyser alla
      byt färg och lys med alla
      byt färg och lys med alla

    - ögonen stirrar i några sekunder...

    - texten
      tänd IN LUST
      släck
      tänd WE TRUST
      släck
      tänd båda
      upprepa tre gånger häng kvar på båda längre sista gången...
      upprepa med 1-2 mn mellanrum

    - slingorna
      lys i en färg (blå)
      skift blå - lila
      skift lila - röd
      skift röd - orange
      skift orange - gul
      skift gul - grön
      skift grön - turkos
      skift turkos - blå
      utför under ca 3min
      avsluta med slump i ca en minut...

      
      
    
   */
  
}
