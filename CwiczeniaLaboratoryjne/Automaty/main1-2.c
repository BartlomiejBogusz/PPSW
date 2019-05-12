#include "led.h"

enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	while(1){
		switch(eLedState){
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepLeft();
				break;
			case LED_RIGHT:
				eLedState = LED_LEFT;
				LedStepRight();
				break;
		}
		Delay(500);
	}
}

