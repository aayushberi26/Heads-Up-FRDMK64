#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <fsl_debug_console.h>
#include <fsl_device_registers.h>
#include <board.h>

//#include "ledmatrix.h"
//#include "accelerometer.h"

ACCELEROMETER_STATE state;
int seconds;
int words_correct;
int words_incorrect;
//MAGNETOMETER_STATE mstate;

void timer_setup (void) {
	NVIC_EnableIRQ(PIT0_IRQn);
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT->MCR = (0 << 1);
	PIT->CHANNEL[0].LDVAL = 61500000;
	PIT->CHANNEL[0].TCTRL = (3 << 0); // Enable timer and also enable interrupt
}

void game_over(void) {
	debug_printf("game over\r\n");
	debug_printf("%d", words_correct); debug_printf(" words correct\r\n");
	debug_printf("%d", words_incorrect); debug_printf(" words incorrect\r\n");
	while(1);
}

void PIT0_IRQHandler(void)
{
	  /* code goes here */
	seconds++;
	if (seconds==59) game_over();
	else {
		PIT->CHANNEL[0].LDVAL = 61500000;
		PIT->CHANNEL[0].TCTRL = (3 << 0);
		PIT->CHANNEL[0].TFLG =1;
	}
}

int main() {
	hardware_init();
	Accelerometer_Initialize();
	seconds=0;
	words_correct=0;
	words_incorrect=0;
	timer_setup();
	//Magnetometer_Initialize();
	
	while (1) {
		Accelerometer_GetState(&state);
		//Magnetometer_GetState(&mstate);
		if(state.x > -600 || state.x < -1400) {
			//debug_printf("%5d %5d %5d\r\n", state.x, state.y, state.z);
			if (state.x > -600) {
				debug_printf("correct\r\n");
				words_correct++;
			}
			else {
				debug_printf("incorrect\r\n");
				words_incorrect++;
			}
			for(int i = 0; i < 10000000; i++) {}
		}
	}
}