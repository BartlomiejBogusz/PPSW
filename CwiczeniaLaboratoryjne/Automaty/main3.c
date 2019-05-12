#include "led.h"

enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	unsigned char ucMovesCounter = 0;
	LedInit();
	
	while(1){
		switch(eLedState){
			case LED_LEFT:
				ucMovesCounter++;
				if(ucMovesCounter > 3){
					ucMovesCounter = 0;
					eLedState = LED_RIGHT;
				}
				else{
					LedStepLeft();
				}
				break;
			case LED_RIGHT:
				ucMovesCounter++;
				if(ucMovesCounter > 3){
					ucMovesCounter = 0;
					eLedState = LED_LEFT;
				}
				else{
					LedStepRight();
				}
				break;
		}
		Delay(500);
	}
}

