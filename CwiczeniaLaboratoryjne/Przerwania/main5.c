#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

	enum LedState{LED_LEFT, LED_RIGHT, LED_STOP};
	enum LedState eLedState = LED_STOP;

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
		}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(20000, &Automat);
	while(1){
	 	iMainLoopCtr++;
	}
}
