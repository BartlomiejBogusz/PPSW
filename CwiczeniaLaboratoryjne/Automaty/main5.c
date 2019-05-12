#include "led.h"
#include "keyboard.h"

enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_RIGHT;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	LedInit();
	KeyboardInit();
	
	while(1){
		switch(eLedState){
			case LED_RIGHT:
				if(eKeyboardRead() != BUTTON_0){
					LedStepRight();
				}
				else{
					eLedState = LED_LEFT;
				}
				break;
			case LED_LEFT:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_RIGHT;
				}
				break;
		}
		Delay(500);
	}
}

