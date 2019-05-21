#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

	enum LedState{LED_LEFT, LED_RIGHT, LED_STOP, CALLIB};
	enum LedState eLedState = CALLIB;
	enum DetectorState{ACTIVE, INACTIVE};
	
void DetectorInit(){
	IO0DIR = IO0DIR &(~DETECTOR_bm);
}

enum DetectorState eReadDetector(){
	
	if((IO0PIN & DETECTOR_bm) == 0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

void Automat(){
	
		switch(eLedState){
			case LED_STOP:
				if(eKeyboardRead() == BUTTON_0){
					eLedState = LED_LEFT;
				}
				else if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_RIGHT;
				}
				break;
			case LED_RIGHT:
					if(eKeyboardRead() == BUTTON_1){
						eLedState = LED_STOP;
					}
					else{
						LedStepRight();
					}
				break;
			case LED_LEFT:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_STOP;
				}
				else{
					LedStepLeft();
				}
				break;
			case CALLIB:
				if(eReadDetector() == INACTIVE){
					LedStepLeft();
				}
				else{
					eLedState = LED_STOP;
				}
				break;
		}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	DetectorInit();
	Timer1Interrupts_Init(5, &Automat);
	while(1){
	 	iMainLoopCtr++;
	}
}
