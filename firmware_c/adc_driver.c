#include "nios2_control.h"
#include "chario.h"
#include "adc.h"
#include "leds.h"

/* place additional #define macros here */
#ifndef _NIOS2_CONTROL_H_
#define _NIOS2_CONTROL_H_

#define NIOS2_WRITE_STATUS(value)  (__builtin_wrctl (0, value))

#define NIOS2_READ_IENABLE()	   (__builtin_rdctl (3))

#define NIOS2_WRITE_IENABLE(value) (__builtin_wrctl (3, value))

#define NIOS2_READ_IPENDING()	   (__builtin_rdctl (4))


#endif /* _NIOS2_CONTROL_H_ */


/*-----------------------------------------------------------------*/

#ifndef _TIMER_H_
#define _TIMER_H_


/* define pointer macros for accessing the timer interface registers */

// timer 1 is bit 14

#define TIMER1_STATUS	((volatile unsigned int *) 0x10004020)

#define TIMER1_CONTROL	((volatile unsigned int *) 0x10004024)

#define TIMER1_START_LO	((volatile unsigned int *) 0x10004028)

#define TIMER1_START_HI	((volatile unsigned int *) 0x1000402C)

#define TIMER1_SNAP_LO	((volatile unsigned int *) 0x10004030)

#define TIMER1_SNAP_HI	((volatile unsigned int *) 0x10004034)


// timer 2 is bit 15

//#define TIMER2_STATUS	((volatile unsigned int *) 0x10004040)

//#define TIMER2_CONTROL	((volatile unsigned int *) 0x10004044)

//#define TIMER2_START_LO	((volatile unsigned int *) 0x10004048)

//#define TIMER2_START_HI	((volatile unsigned int *) 0x1000404C)

//#define TIMER2_SNAP_LO	((volatile unsigned int *) 0x10004050)

//#define TIMER2_SNAP_HI	((volatile unsigned int *) 0x10004054)


// timer 3 is bit 16

#define TIMER3_STATUS	((volatile unsigned int *) 0x10004060)

#define TIMER3_CONTROL	((volatile unsigned int *) 0x10004064)

#define TIMER3_START_LO	((volatile unsigned int *) 0x10004068)

#define TIMER3_START_HI	((volatile unsigned int *) 0x1000406C)

#define TIMER3_SNAP_LO	((volatile unsigned int *) 0x10004070)

#define TIMER3_SNAP_HI	((volatile unsigned int *) 0x10004074)

/* define a bit pattern reflecting the position of the timeout (TO) bit
   in the timer status register */

#define TIMER_TO_BIT 0x1


#endif /* _TIMER_H_ */






/*-----------------------------------------------------------------*/

//#define LEDS	((volatile unsigned int *) 0x10000010)


#define TIMER1_INTERVAL 6250000		// 0.125s

#define TIMER3_INTERVAL 12500000	// 0.25s

#define SWITCHES_DATA (volatile unsigned int *) 0x10000040

#define HEX_DISPLAYS (volatile unsigned int ...


/* define global program variables here */

static unsigned int LED_pattern1 = 0x00000303u;
static unsigned int LED_pattern2 = 0x00000186u;
static unsigned int LED_pattern3 = 0x000000CCu;
static unsigned int LED_pattern4 = 0x00000078u;

static unsigned int LED_pattern5 = 0x00000030u;
static unsigned int LED_pattern6 = 0x00000078u;
static unsigned int LED_pattern7 = 0x000000CCu;
static unsigned int LED_pattern8 = 0x00000186u;


unsigned int dash_pattern = 0x40;	// '------'



unsigned int timer_count = 0;
int flag = 0;
int flag2 = 0;

volatile unsigned int ADC_HEX1 = 0;
volatile unsigned int ADC_HEX2 = 0;
volatile unsigned int timer_1_flag = 0;
volatile unsigned int switchSet = 0;
volatile unsigned int show_dash = 0;


*LEDS = LED_pattern1;

/* place additional functions here */



/*-----------------------------------------------------------------*/

/* this routine is called from the_exception() in exception_handler.c */

void interrupt_handler(void)
{
	unsigned int ipending;

	/* read current value in ipending register */

	ipending = NIOS2_READ_IPENDING();

	/* do one or more checks for different sources using ipending value */

   if (ipending & (1<<14)){		//bit 14, timer 1

	  // cause two leds to move to the right by two positions, wrapping to the left when needed
      
      /* remember to clear interrupt sources */
      *TIMER1_STATUS = TIMER_TO_BIT;
	
		
	  //LED_pattern = ((LED_pattern >> 2) | (LED_pattern << 8)) & 0x3FFu;
	  //*LEDS = LED_pattern;
	  
	  
	  //_________
	  
	  if (*LEDS == LED_pattern1) {
		 *LEDS = LED_pattern2;
	  } else if (*LEDS == LED_pattern2) {
		 *LEDS = LED_pattern3;
	  } else if (*LEDS == LED_pattern3) {
		 *LEDS = LED_pattern4;
	  } else if (*LEDS == LED_pattern4) {
		 *LEDS = LED_pattern5;
	  } else if (*LEDS == LED_pattern5) {
		 *LEDS = LED_pattern6;
	  } else if (*LEDS == LED_pattern6) {
		 *LEDS = LED_pattern7;
	  } else if (*LEDS == LED_pattern7) {
		 *LEDS = LED_pattern8;
	  } else if (*LEDS == LED_pattern8) {
		 *LEDS = LED_pattern1;
	  }
	
	
	
   }
   
   if (ipending & (1 << 16)) {
		flag2 = 1;
   }
   
   

}

/*-----------------------------------------------------------------*/

void Init (void)
{
	/* initialize software variables */
	timer_count = 0;
	flag = 0;
	flag2 = 0;

	/* set up each hardware interface */
	*TIMER1_START_LO = TIMER1_INTERVAL & 0xFFFF;
	*TIMER1_START_HI = (TIMER1_INTERVAL >> 16) & 0xFFFF;
   
	*TIMER3_START_LO = TIMER3_INTERVAL & 0xFFFF;
	*TIMER3_START_HI = (TIMER3_INTERVAL >> 16) & 0xFFFF;

	*TIMER1_CONTROL = 0x7; /* start timer, enable interrupts, continuous mode */
	*TIMER3_CONTROL = 0x7; /* start timer, enable interrupts, continuous mode */

	InitADC(2,2);
	

	/* set up ienable */
	NIOS2_WRITE_IENABLE((1 << 16) | (1<<14) | (1<<15));
	

	/* enable global recognition of interrupts in procr. status reg. */
	NIOS2_WRITE_STATUS(1);
}

/*-----------------------------------------------------------------*/

int main (void)
{
	Init ();	/* perform software/hardware initialization */
	
	PrintString("before");
	unsigned int c = GetChar();
	
	if (c == '-') {
	
		int show_dash = 1;
		
	} else {
		int show_dash = 0;
	}
	
	PrintChar('\n');
	PrintString("ELEC 371 LAB 4 by Emily, Nadia");

	PrintChar('\n');
	PrintString("Hexadecimal result from A/D conversion : 0x??");
	

	
	

	while (1)
	{
		/* fill in body of infinite loop */
		if (timer_3_flag){
			ADC_result = ADConvert();
			ADC_HEX1 = (ADC_result >> 16);
			ADC_HEX2 = ADC_result &  0x0F;
			PrintChar('\b');
			PrintChar('\b');
			PrintHexDigit(ADC_HEX1);
			PrintHexDigit(ADC_HEX2);
		} 
	
		if (timer_1_flag){
			switchSet = *SWITCHES_DATA & 0xF;
			if (show_dash == 1){
				unsigned int dash = dash_pattern;
			
				if (switchSet & 0x1){
					*HEX_DISPLAYS = dash_pattern;
				}
				*HEX_DISPLAYS = (dash) | (dash<<8) | (dash<<16) | (dash<<24);
			}	
		}
	}

	return 0;	/* never reached, but main() must return a value */
}
