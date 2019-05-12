#include "led.h"
#include "keyboard.h"

enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_RIGHT;

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
			case LED_LEFT:
				ucMovesCounter++;
				if(ucMovesCounter > 3){
					ucMovesCounter = 0;
					eLedState = LED_RIGHT;
				}
				else{
					LedStepRight();
				}
				break;
			case LED_RIGHT:
				if(eKeyboardRead() == BUTTON_0){
					eLedState = LED_LEFT;
				}
				break;
		}
		Delay(500);
	}
}

