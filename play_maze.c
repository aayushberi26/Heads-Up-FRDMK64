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

struct Tile{
	struct Tile* up;
	struct Tile* down;
	struct Tile* left;
	struct Tile* right;
};
struct Tile* maze[36];

void create_maze(void) {
	struct Tile* end = malloc(sizeof(struct Tile));
	struct Tile* Tile00 = malloc(sizeof(struct Tile));
	struct Tile* Tile01 = malloc(sizeof(struct Tile));
	struct Tile* Tile02 = malloc(sizeof(struct Tile));
	struct Tile* Tile03 = malloc(sizeof(struct Tile));
	struct Tile* Tile04 = malloc(sizeof(struct Tile));
	struct Tile* Tile10 = malloc(sizeof(struct Tile));
	struct Tile* Tile11 = malloc(sizeof(struct Tile));
	struct Tile* Tile12 = malloc(sizeof(struct Tile));
	struct Tile* Tile13 = malloc(sizeof(struct Tile));
	struct Tile* Tile14 = malloc(sizeof(struct Tile));
	struct Tile* Tile20 = malloc(sizeof(struct Tile));
	struct Tile* Tile21 = malloc(sizeof(struct Tile));
	struct Tile* Tile22 = malloc(sizeof(struct Tile));
	struct Tile* Tile23 = malloc(sizeof(struct Tile));
	struct Tile* Tile24 = malloc(sizeof(struct Tile));
	struct Tile* Tile30 = malloc(sizeof(struct Tile));
	struct Tile* Tile31 = malloc(sizeof(struct Tile));
	struct Tile* Tile32 = malloc(sizeof(struct Tile));
	struct Tile* Tile33 = malloc(sizeof(struct Tile));
	struct Tile* Tile34 = malloc(sizeof(struct Tile));
	struct Tile* Tile40 = malloc(sizeof(struct Tile));
	struct Tile* Tile41 = malloc(sizeof(struct Tile));
	struct Tile* Tile42 = malloc(sizeof(struct Tile));
	struct Tile* Tile43 = malloc(sizeof(struct Tile));
	struct Tile* Tile44 = malloc(sizeof(struct Tile));
	struct Tile* Tile50 = malloc(sizeof(struct Tile));
	struct Tile* Tile51 = malloc(sizeof(struct Tile));
	struct Tile* Tile52 = malloc(sizeof(struct Tile));
	struct Tile* Tile53 = malloc(sizeof(struct Tile));
	struct Tile* Tile54 = malloc(sizeof(struct Tile));
	struct Tile* Tile60 = malloc(sizeof(struct Tile));
	struct Tile* Tile61 = malloc(sizeof(struct Tile));
	struct Tile* Tile62 = malloc(sizeof(struct Tile));
	struct Tile* Tile63 = malloc(sizeof(struct Tile));
	struct Tile* Tile64 = malloc(sizeof(struct Tile));
	Tile00->up=Tile01;
	Tile00->down=NULL;
	Tile00->left=NULL;
	Tile00->right=Tile10;
	Tile10->up=NULL;
	Tile10->down=NULL;
	Tile10->left=Tile00;
	Tile10->right=Tile20;
	Tile20->up=NULL;
	Tile20->down=NULL;
	Tile20->left=Tile20;
	Tile20->right=Tile30;
	Tile30->up=Tile31;
	Tile30->down=NULL;
	Tile30->left=Tile20;
	Tile30->right=Tile40;
	Tile40->up=NULL;
	Tile40->down=NULL;
	Tile40->left=Tile30;
	Tile40->right=NULL;
	Tile50->up=NULL;
	Tile50->down=NULL;
	Tile50->left=NULL;
	Tile50->right=Tile60;
	Tile60->up=Tile61;
	Tile60->down=NULL;
	Tile60->left=Tile50;
	Tile60->right=NULL;
	Tile01->up=Tile02;
	Tile01->down=Tile00;
	Tile01->left=NULL;
	Tile01->right=Tile11;
	Tile11->up=Tile12;
	Tile11->down=NULL;
	Tile11->left=Tile01;
	Tile11->right=Tile21;
	Tile21->up=NULL;
	Tile21->down=NULL;
	Tile21->left=Tile21;
	Tile21->right=Tile31;
	Tile31->up=NULL;
	Tile31->down=Tile30;
	Tile31->left=Tile21;
	Tile31->right=NULL;
	Tile41->up=Tile42;
	Tile41->down=NULL;
	Tile41->left=NULL;
	Tile41->right=Tile51;
	Tile51->up=NULL;
	Tile51->down=NULL;
	Tile51->left=Tile41;
	Tile51->right=Tile61;
	Tile61->up=Tile62;
	Tile61->down=Tile60;
	Tile61->left=Tile51;
	Tile61->right=NULL;
	Tile02->up=Tile03;
	Tile02->down=Tile01;
	Tile02->left=NULL;
	Tile02->right=NULL;
	Tile12->up=NULL;
	Tile12->down=Tile11;
	Tile12->left=NULL;
	Tile12->right=NULL;
	Tile22->up=Tile23;
	Tile22->down=NULL;
	Tile22->left=NULL;
	Tile22->right=Tile32;
	Tile32->up=Tile33;
	Tile32->down=NULL;
	Tile32->left=Tile22;
	Tile32->right=NULL;
	Tile42->up=Tile43;
	Tile42->down=Tile41;
	Tile42->left=NULL;
	Tile42->right=NULL;
	Tile52->up=Tile53;
	Tile52->down=NULL;
	Tile52->left=NULL;
	Tile52->right=NULL;
	Tile62->up=Tile63;
	Tile62->down=Tile61;
	Tile62->left=NULL;
	Tile62->right=NULL;
	Tile03->up=Tile04;
	Tile03->down=Tile02;
	Tile03->left=NULL;
	Tile03->right=Tile13;
	Tile13->up=NULL;
	Tile13->down=NULL;
	Tile13->left=Tile03;
	Tile13->right=Tile23;
	Tile23->up=NULL;
	Tile23->down=Tile22;
	Tile23->left=Tile13;
	Tile23->right=NULL;
	Tile33->up=NULL;
	Tile33->down=Tile32;
	Tile33->left=NULL;
	Tile33->right=Tile43;
	Tile43->up=NULL;
	Tile43->down=Tile42;
	Tile43->left=Tile33;
	Tile43->right=NULL;
	Tile53->up=Tile54;
	Tile53->down=Tile52;
	Tile53->left=NULL;
	Tile53->right=NULL;
	Tile63->up=Tile64;
	Tile63->down=Tile62;
	Tile63->left=NULL;
	Tile63->right=NULL;
	Tile04->up=NULL;
	Tile04->down=Tile03;
	Tile04->left=NULL;
	Tile04->right=Tile14;
	Tile14->up=NULL;
	Tile14->down=NULL;
	Tile14->left=Tile04;
	Tile14->right=Tile24;
	Tile24->up=NULL;
	Tile24->down=NULL;
	Tile24->left=Tile14;
	Tile24->right=Tile34;
	Tile34->up=NULL;
	Tile34->down=NULL;
	Tile34->left=Tile24;
	Tile34->right=Tile44;
	Tile44->up=NULL;
	Tile44->down=NULL;
	Tile44->left=Tile34;
	Tile44->right=Tile54;
	Tile54->up=NULL;
	Tile54->down=Tile53;
	Tile54->left=Tile44;
	Tile54->right=NULL;
	Tile64->up=end;
	Tile64->down=Tile63;
	Tile64->left=NULL;
	Tile64->right=NULL;
	maze[0]=Tile00;
	maze[1]=Tile01;
	maze[2]=Tile02;
	maze[3]=Tile03;
	maze[4]=Tile04;
	maze[5]=Tile10;
	maze[6]=Tile11;
	maze[7]=Tile12;
	maze[8]=Tile13;
	maze[9]=Tile14;
	maze[10]=Tile20;
	maze[11]=Tile21;
	maze[12]=Tile22;
	maze[13]=Tile23;
	maze[14]=Tile24;
	maze[15]=Tile30;
	maze[16]=Tile31;
	maze[17]=Tile32;
	maze[18]=Tile33;
	maze[19]=Tile34;
	maze[20]=Tile40;
	maze[21]=Tile41;
	maze[22]=Tile42;
	maze[23]=Tile43;
	maze[24]=Tile44;
	maze[25]=Tile50;
	maze[26]=Tile51;
	maze[27]=Tile52;
	maze[28]=Tile53;
	maze[29]=Tile54;
	maze[30]=Tile60;
	maze[31]=Tile61;
	maze[32]=Tile62;
	maze[33]=Tile63;
	maze[34]=Tile64;
	maze[35]=end;
}

struct Tile* current;
int moved;
ACCELEROMETER_STATE state;

void maze_end(void) {
	debug_printf("You won!");
	__disable_irq();
	while(1);
}

void reader_setup(void) {
	NVIC_EnableIRQ(PIT2_IRQn);
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT->MCR = (0 << 1);
	PIT->CHANNEL[2].LDVAL = 500000;
	PIT->CHANNEL[2].TCTRL = (3 << 0); // Enable timer and also enable interrupt
}

void PIT2_IRQHandler(void){
	
	Accelerometer_GetState(&state);
	/*
	if (state.x > -500) {
		current=current->down;	
	}
	else if (state.x < -1900) {
		current=current->up;
	}
	else if (state.y > 650 && state.x > -1800 && state.x < -600) {
		current=current->left;
	}
	else if (state.y < -650 && state.x > -1800 && state.x < -600) {
		current=current->right;
	}
	if (current==maze[35]) maze_end();
	debug_printf("You can move: ");
	if (current->up!=NULL) debug_printf("up ");
	if (current->down!=NULL) debug_printf("down ");
	if (current->left!=NULL) debug_printf("left ");
	if (current->right!=NULL) debug_printf("right ");
	for(int i = 0; i < 10000000; i++) {};
	*/
	debug_printf("\r\n");
	PIT->CHANNEL[2].LDVAL = 500000;
	PIT->CHANNEL[2].TCTRL = (3 << 0);
	PIT->CHANNEL[2].TFLG =1;
}

int main(void){
	hardware_init();
	Accelerometer_Initialize();
	create_maze();
	current=maze[3];
	debug_printf("You can move: ");
	if (current->up!=NULL) debug_printf("up ");
	if (current->down!=NULL) debug_printf("down ");
	if (current->left!=NULL) debug_printf("left ");
	if (current->right!=NULL) debug_printf("right ");
	debug_printf("\r\n");
	//reader_setup();
	moved = 1;
	while(1) {
		Accelerometer_GetState(&state);
	if (state.x > -500) {
			if(current->down != NULL) {
				moved = 1;
				current=current->down;
			}				
	}
	else if (state.x < -1900) {
		if(current->up != NULL) {
			current=current->up;
			moved = 1;
		}
	}
	else if (state.y > 650 && state.x > -1800 && state.x < -600) {
		if(current->left != NULL) {
			current=current->left;
			moved = 1;
		}
	}
	else if (state.y < -650 && state.x > -1800 && state.x < -600) {
		if(current->right != NULL) {
			current=current->right;
			moved = 1;
		}
	}
	if(moved) {
		if (current==maze[35]) maze_end();
		if (current->up!=NULL) debug_printf("up ");
		if (current->down!=NULL) debug_printf("down ");
		if (current->left!=NULL) debug_printf("left ");
		if (current->right!=NULL) debug_printf("right ");
		for(int i = 0; i < 10000000; i++) {};
		debug_printf("\r\n");
		moved = 0;
		}
	};
	return 1;
}