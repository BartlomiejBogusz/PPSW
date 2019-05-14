#include "timer_interrupts.h"
#include "led.h"


int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	Timer0Interrupts_Init(250000, &LedStepLeft);
	while(1){
	 	iMainLoopCtr++;
	}
}
