#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <fsl_debug_console.h>
#include <fsl_device_registers.h>
#include <board.h>
#include "Driver_I2C.h"
//#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RT
#include <string.h>
#include <time.h>
#include <stdlib.h>

//#include "ledmatrix.h"
//#include "accelerometer.h"


/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. 
	 Code from http://stackoverflow.com/questions/6127503/shuffle-array-in-c
	 */
	 
void shuffle(char *array[30])
{
    {
        size_t i;
        for (i = 0; i < 29; i++) 
        {
          int j = rand() % 30;
          char *t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}



ACCELEROMETER_STATE state;
int seconds;
int words_correct;
int words_incorrect;
int list_ind;
char *sports[30];
char *nerd[30];
char *music[30];
char *movies[30];
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
	PIT->CHANNEL[1].LDVAL = 500000;
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
		//debug_printf("%5d %5d %5d\r\n", state.x, state.y, state.z);
		PIT->CHANNEL[0].LDVAL = 61500000;
		PIT->CHANNEL[0].TCTRL = (3 << 0);
		PIT->CHANNEL[0].TFLG =1;
	}
}

void print_next(char *array[30]) {
	if(list_ind < 30) {
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
		if(state.x > -200 || state.x < -1900) {
			//debug_printf("%5d %5d %5d\r\n", state.x, state.y, state.z);
			if (state.x > -500) {
				debug_printf("correct\r\n");
				words_correct++;
			}
			else if (state.x < -1900) {
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
		PIT->CHANNEL[1].LDVAL = 500000;
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
	//srand(time(NULL));
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
	srand(22);

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
	sports[12] = "Superbowl";
	sports[13] = "Tour de France";
	sports[14] = "Craig Sager";
	sports[15] = "Stuart Scott";
	sports[16] = "Bryce Harper";
	sports[17] = "New York Yankees";
	sports[18] = "Lionel Messi";
	sports[19] = "Champions League";
	sports[20] = "Ray Allen";
	sports[21] = "The Block";
	sports[22] = "PGA Tour";
	sports[23] = "Jerry Rice";
	sports[24] = "Wayne Gretzky";
	sports[25] = "Derek Jeter";
	sports[26] = "Ronda Rousey";
	sports[27] = "Roger Federer";
	sports[28] = "Christiano Ronaldo";
	sports[29] = "Arsenal";
	
	
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
	movies[15] = "Pitch Perfect";
	movies[16] = "The Proposal";
	movies[17] = "Captain America";
	movies[18] = "Deadpool";
	movies[19] = "Finding Nemo";
	movies[20] = "E.T.";
	movies[21] = "Forest Gump";
	movies[22] = "The Lion King";
	movies[23] = "The Little Mermaid";
	movies[24] = "Beauty and the Beast";
	movies[25] = "King Kong";
	movies[26] = "Kung Fu Panda";
	movies[27] = "Friends with Benefits";
	movies[28] = "The Great Gatsby";
	movies[29] = "Wolf of Wall Street";



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
	nerd[15] = "Newton's 2nd Law";
	nerd[16] = "The Catcher in the Rye";
	nerd[17] = "Harry Potter";
	nerd[18] = "E = mc^2";
	nerd[19] = "World War 2";
	nerd[20] = "Donald Trump";
	nerd[21] = "The New Deal";
	nerd[22] = "Ionization Energy";
	nerd[23] = "Periodic Table";
	nerd[24] = "Carnot Engine";
	nerd[25] = "Supply Curve";
	nerd[26] = "Marginal Cost";
	nerd[27] = "Vertical Integration";
	nerd[28] = "Condition Variable";
	nerd[29] = "Linked List";



	music[0] = "Shape of You";
	music[1] = "No Problem";
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
	music[15] = "Maroon 5";
	music[16] = "Take Care";
	music[17] = "Aerosmith";
	music[18] = "Back to Back";
	music[19] = "Airplanes";
	music[20] = "Star Spangled Banner";
	music[21] = "Waka Waka";
	music[22] = "Crazy in Love";
	music[23] = "Empire State of Mind";
	music[24] = "Hotel California";
	music[25] = "Jai Ho";
	music[26] = "Party Rock Anthem";
	music[27] = "Shakira";
	music[28] = "Pitbull";
	music[29] = "Kendrick Lamar";
	
	
	
	debug_printf("Welcome to Heads Up! Choose your category: \r\n swipe up for sports, down for nerdy stuff, left for music or right for movies. \r\n");
	
	int selected = 0;
	for(int i = 0; i < 5000000; i++) {};
	while (!selected) {
		//debug_printf("incorrect\r\n")
		Accelerometer_GetState(&state);
		//normal ranges: x:-1000,-800, y:-100,100, z:-400,-200
			if (state.x > -500) {
				debug_printf("Nerd\r\n");
				selected = 1;
				mode = 1;
			}
			else if (state.x < -1900) {
				debug_printf("Sports\r\n");
				selected = 1;
				mode = 2;
			}
			else if (state.y > 650 && state.x > -1800 && state.x < -600) {
				debug_printf("Music\r\n");
				selected = 1;
				mode = 3;
			}
			else if (state.y < -650 && state.x > -1800 && state.x < -600) {
				debug_printf("Movies\r\n");
				selected = 1;
				mode = 4;
			}
			
	}
	
	for(int i = 0; i < 30000000; i++) {};
	timer_setup();
	switch (mode) {
		case 1:
			shuffle(nerd);
			print_next(nerd);
			break;
		case 2:
			shuffle(sports);
			print_next(sports);
			break;
		case 3:
			shuffle(music);
			print_next(music);
			break;
		case 4:
			shuffle(movies);
			print_next(movies);
			break;
		}
		
	while(1) {};
}