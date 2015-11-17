// AC Control V1.1
//
// This arduino sketch is for use with the heater 
// control circuit board which includes a zero 
// crossing detect fucntion and an opto-isolated triac.
//
// AC Phase control is accomplished using the internal 
// hardware timer1 in the arduino
//
// Timing Sequence
// * timer is set up but disabled
// * zero crossing detected on pin 2
// * timer starts counting from zero
// * comparator set to "delay to on" value
// * counter reaches comparator value
// * comparator ISR turns on triac gate
// * counter set to overflow - pulse width
// * counter reaches overflow
// * overflow ISR truns off triac gate
// * triac stops conducting at next zero cross


// The hardware timer runs at 16MHz. Using a
// divide by 256 on the counter each count is 
// 16 microseconds.  1/2 wave of a 60Hz AC signal
// is about 520 counts (8,333 microseconds).

#include <TimerOne.h>
#include <TimerThree.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>

// todo: update to match pin mapping and/or possibly update pin mapping!s
#define DETECT 2  //zero cross detect
#define GATE 9    //triac gate
#define PULSE 4   //trigger pulse width (counts)
int i=483;

static volatile uint16_t g_timer_counter        = 0;
static volatile uint16_t g_triac_pulse_on_time  = 0;
static volatile uint16_t g_triac_pulse_length   = 0;

void setup()
{
  // set up pins
  pinMode(DETECT, INPUT);     //zero cross detect
  digitalWrite(DETECT, HIGH); //enable pull-up resistor
  pinMode(GATE, OUTPUT);      //triac gate control

/*
  // set up Timer1 
  //(see ATMEGA 328 data sheet pg 134 for more details)
  OCR1A = 100;      //initialize the comparator
  TIMSK1 = 0x03;    //enable comparator A and overflow interrupts
  TCCR1A = 0x00;    //timer control registers set for
  TCCR1B = 0x00;    //normal operation, timer disabled
*/
  // wake up every ...
  Timer3.initialize(100);
  Timer3.attachInterrupt(timerInterruptHandler);
/*
  // set up zero crossing interrupt
  attachInterrupt(0, zeroCrossingInterrupt, RISING);    
    //IRQ0 is pin 2. Call zeroCrossingInterrupt 
    //on rising signal
*/
  attachInterrupt(DETECT, zeroCrossingInterrupt, RISING);
}  

// Interrupt Service Routines

void zeroCrossingInterrupt()
{ //zero cross detect
/*
  TCCR1B=0x04; //start timer with divide by 256 input
  TCNT1 = 0;   //reset timer - count from zero
*/
  // if off then just return...
  if (g_triac_pulse_on_time >= 100)
  {
    return;
  }

  g_timer_counter = 0;
  Timer3.restart();
}

void timerInterruptHandler()
{
  g_timer_counter++;
  
  // check if we meet turn-on condition...
  if (g_timer_counter > g_triac_pulse_on_time + g_triac_pulse_length)
  {
    // turn off triac...
    digitalWrite(GATE, LOW);

    // turn off timer...
    Timer3.stop();
  }
  else if (g_timer_counter > g_triac_pulse_on_time)
  {
    // turn on triac...
    digitalWrite(GATE, LOW);
  }
  else
  {
    // do nothing right!?
  }
}

/*
ISR(TIMER1_COMPA_vect)
{ //comparator match
  digitalWrite(GATE, HIGH);  //set triac gate to high
  TCNT1 = 65536-PULSE;      //trigger pulse width
}

ISR(TIMER1_OVF_vect)
{ //timer1 overflow
  digitalWrite(GATE,LOW); //turn off triac gate
  TCCR1B = 0x00;          //disable timer stopd unintended triggers
}
*/

void set_dim_level(uint8_t dim_level)
{
  // sanity...
  if (dim_level > 100)
  {
    dim_level = 100;
  }

  // set the dime level...
  noInterrupts();
  // todo: do we need to reset everything!?
  g_triac_pulse_on_time = 100 - dim_level;
  interrupts();
}

void loop()
{ // sample code to exercise the circuit
 /*
  i--;
  OCR1A = i;     //set the compare register brightness desired.
  if (i<65){i=483;}                      
  delay(15);
 */
 uint8_t i;
 for (i = 0; i<=100; i++)
 {
  set_dim_level(i);
 }

  for (i = 0; i<=100; i++)
  {
   set_dim_level(100-i);
  }
                         
}

