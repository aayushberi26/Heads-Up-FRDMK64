#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <fsl_debug_console.h>
#include <fsl_device_registers.h>
#include <board.h>
#include "Driver_I2C.h"
//#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RT
#include <string.h>

//#include "ledmatrix.h"
//#include "accelerometer.h"





ACCELEROMETER_STATE state;
int seconds;
int words_correct;
int words_incorrect;
int list_ind;
const char *sports[15];
const char *nerd[15];
const char *music[15];
const char *movies[15];
int mode;
//MAGNETOMETER_STATE mstate;

void timer_setup (void) {
	NVIC_EnableIRQ(PIT0_IRQn);
	NVIC_EnableIRQ(PIT1_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT->MCR = (0 << 1);
	PIT->CHANNEL[0].LDVAL = 61500000;
	PIT->CHANNEL[0].TCTRL = (3 << 0); // Enable timer and also enable interrupt
	PIT->CHANNEL[1].LDVAL = 200000;
	PIT->CHANNEL[1].TCTRL = (3 << 0); // Enable timer and also enable interrupt
	NVIC_SetPriority(PIT0_IRQn, 0);
	NVIC_SetPriority(PIT1_IRQn, 1);
	
	
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
	debug_printf("%d\r\n", 60-seconds);
	if (seconds==59) game_over();
	else {
		//Accelerometer_GetState(&state);
		debug_printf("%5d %5d %5d\r\n", state.x, state.y, state.z);
		PIT->CHANNEL[0].LDVAL = 61500000;
		PIT->CHANNEL[0].TCTRL = (3 << 0);
		PIT->CHANNEL[0].TFLG =1;
	}
}

void print_next(const char *array[15]) {
	if(list_ind < 15) {
	debug_printf("%s \r\n", array[list_ind]);
	list_ind ++;
	}
	else {
		__disable_irq();
		seconds = 59;
		game_over();
		__enable_irq();
	}
}

void PIT1_IRQHandler(void)
{
		if(seconds != 59) {
		Accelerometer_GetState(&state);
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
			for(int i = 0; i < 10000000; i++) {};
			switch (mode) {
				case 1:
					print_next(nerd);
					break;
				case 2:
					print_next(sports);
					break;
				case 3:
					print_next(music);
					break;
				case 4:
					print_next(movies);
					break;
			}
		}
		PIT->CHANNEL[1].LDVAL = 200000;
		PIT->CHANNEL[1].TCTRL = (3 << 0);
		PIT->CHANNEL[1].TFLG =1;
		}
	/*
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
			for(int i = 0; i < 10000000; i++) {};
			PIT->CHANNEL[1].LDVAL = 20000;
			PIT->CHANNEL[1].TCTRL = (3 << 0);
			PIT->CHANNEL[1].TFLG =1;
		}
	*/
	}

void PORTA_IRQHandler(void) { 
	debug_printf("debug");
	PORTA->PCR[4] = (1 << 24);
}


int main() {
	hardware_init();
	Accelerometer_Initialize();
	seconds=0;
	words_correct=0;
	words_incorrect=0;
	//timer_setup();
	//Magnetometer_Initialize();
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 	//Enable clock to port A
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; 	//Enable clock to port C
	PORTA->PCR[4] = (1 << 8); //Set pin A4 to GPIO
	PORTC->PCR[6] = (1 << 8); //Set pin C6 to GPIO
	PTA->PDDR = (0 << 4);	//Enable PTA4 as input
	PTC->PDDR = (0 << 6);	//Enable PTC6 as input
	PORTA->PCR[4] = (9 << 16); // configure interrupt on rising edge
	PORTC->PCR[6]= (9 << 16); // configure interrupt on rising edge
	NVIC_EnableIRQ(PORTA_IRQn);

	sports[0] = "Lebron James";
	sports[1] = "Mike Trout";
	sports[2] = "Sidney Crosby";
	sports[3] = "Tom Brady";
	sports[4] = "Flea Flicker";
	sports[5] = "Batting a cycle";
	sports[6] = "Triple Double";
	sports[7] = "Triple Crown";
	sports[8] = "Kentucky Derby";
	sports[9] = "Floyd Mayweather";
	sports[10] = "UFC";
	sports[11] = "Conor McGregor";
	sports[12] = "SuperBowl";
	sports[13] = "Fall Classic";
	sports[14] = "Craig Sager";
	
	
	movies[0] = "The Godfather";
	movies[1] = "Avatar";
	movies[2] = "Despicable Me";
	movies[3] = "Toy Story";
	movies[4] = "Fast and the Furious";
	movies[5] = "Slumdog Millionare";
	movies[6] = "Star Wars";
	movies[7] = "Mulan";
	movies[8] = "Olympus Has Fallen";
	movies[9] = "21 Jumpstreet";
	movies[10] = "White House Down";
	movies[11] = "Wall-E";
	movies[12] = "Concussion";
	movies[13] = "The Matrix";
	movies[14] = "Titanic";



	nerd[0] = "Round-Robin";
	nerd[1] = "Biot-Savart Law";
	nerd[2] = "Stokes Theorem";
	nerd[3] = "The Lord of the Flies";
	nerd[4] = "Semaphore";
	nerd[5] = "JavaScript";
	nerd[6] = "Normal Distribution";
	nerd[7] = "Gettysburg Address";
	nerd[8] = "Benedict Arnold";
	nerd[9] = "The Scarlett Letter";
	nerd[10] = "Mitochondria";
	nerd[11] = "Great Depression";
	nerd[12] = "Mesopotamia";
	nerd[13] = "The Adventures of Huckleberry Finn";
	nerd[14] = "Race Condition";



	music[0] = "Shape of You";
	music[1] = "Ode to Joy";
	music[2] = "Black and Yellow";
	music[3] = "Drake";
	music[4] = "Mozart";
	music[5] = "Brad Paisley";
	music[6] = "The Beatles";
	music[7] = "Starboy";
	music[8] = "Rihanna";
	music[9] = "Trumpet";
	music[10] = "Fleetwood Mac";
	music[11] = "Billy Joel";
	music[12] = "Calvin Harris";
	music[13] = "Call me Maybe";
	music[14] = "Friday";
	
	
	
	debug_printf("Welcome to Heads Up! Choose your category: \r\n swipe up for sports, down for nerdy stuff, left for music or right for movies. \r\n");
	
	int selected = 0;
	for(int i = 0; i < 30000000; i++) {};
	while (!selected) {
		//debug_printf("incorrect\r\n")
		Accelerometer_GetState(&state);
		//normal ranges: x:-1000,-800, y:-100,100, z:-400,-200
			if (state.x > -600 && state.y > -120 && state.y < 130) {
				debug_printf("Nerd\r\n");
				selected = 1;
				mode = 1;
			}
			else if (state.x < -1400 && state.y > -120 && state.y < 130) {
				debug_printf("Sports\r\n");
				selected = 1;
				mode = 2;
			}
			else if (state.y < -120 && state.x > -1400 && state.x < -600) {
				debug_printf("Music\r\n");
				selected = 1;
				mode = 3;
			}
			else if (state.y > 130 && state.x > -1400 && state.x < -600) {
				debug_printf("Movies\r\n");
				selected = 1;
				mode = 4;
			}
			
	}
	
	for(int i = 0; i < 30000000; i++) {};
	timer_setup();
	switch (mode) {
		case 1:
			print_next(nerd);
			break;
		case 2:
			print_next(sports);
			break;
		case 3:
			print_next(music);
			break;
		case 4:
			print_next(movies);
			break;
		}
		
	while(1) {};
}