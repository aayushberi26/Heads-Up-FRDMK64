#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <fsl_debug_console.h>
#include <board.h>

//#include "ledmatrix.h"
//#include "accelerometer.h"

ACCELEROMETER_STATE state;
MAGNETOMETER_STATE mstate;

int main() {
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize();
	
	while (1) {
		Accelerometer_GetState(&state);
		Magnetometer_GetState(&mstate);
		if(state.x > -800 || state.x < -1000) {
			debug_printf("%5d %5d %5d\r\n", state.x, state.y, state.z);
			//for(int i = 0; i < 10000000; i++) {}
		}
	}
}