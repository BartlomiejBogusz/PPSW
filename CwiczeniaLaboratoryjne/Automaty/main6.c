#include "led.h"
#include "keyboard.h"

enum LedState{LED_LEFT, LED_RIGHT, LED_STOP};
enum LedState eLedState = LED_STOP;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	LedInit();
	KeyboardInit();
	
	while(1){
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
		Delay(500);
	}
}

