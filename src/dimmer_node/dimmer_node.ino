#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

// todo: use modified TimerOne!!!
// todo: multiple channels to control individually...

enum
{
  RUN_MODE_IDLE = 0,  // lights entirely off no dimming...
  RUN_MODE_RUN,       // 
};

typedef struct
{
  uint8_t dim_level;  // 
}channel_t;

static volatile uint8_t g_run_mode = RUN_MODE_IDLE;

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
}

// timer interrupt handler to control dimming...
void zero_cross_interrupt_handler(void)
{
   
}

// timer interrupt handler to control dimming...
void dimming_timer_interrupt_handler(void)
{
  
}


