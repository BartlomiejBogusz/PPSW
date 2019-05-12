#include "led.h"
#include "keyboard.h"

enum LedState{LED_LEFT, LED_RIGHT, LED_STOP};
enum LedState eLedState = LED_STOP;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	unsigned char ucMovesCounter = 0;
	LedInit();
	KeyboardInit();
	
	while(1){
		switch(eLedState){
			case LED_STOP:
				if(eKeyboardRead() == BUTTON_3){
					eLedState = LED_LEFT;
				}
				break;
			case LED_RIGHT:
				ucMovesCounter++;
				if(ucMovesCounter > 5){
					ucMovesCounter = 0;
					eLedState = LED_STOP;
				}
				else{
					LedStepRight();
				}
				break;
			case LED_LEFT:
				ucMovesCounter++;
				if(ucMovesCounter > 5){
					ucMovesCounter = 0;
					eLedState = LED_RIGHT;
				}
				else{
					LedStepLeft();
				}
				break;
		}
		Delay(100);
	}
}
