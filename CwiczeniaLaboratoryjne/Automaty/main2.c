#include "led.h"

enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedState eLedState = STATE0;

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main(void){
	
	while(1){
		switch(eLedState){
			case STATE0:
				eLedState = STATE1;
				LedStepLeft();
				break;
			case STATE1:
				eLedState = STATE2;
				LedStepLeft();
				break;
			case STATE2:
				eLedState = STATE3;
				LedStepLeft();
				break;
			case STATE3:
				eLedState = STATE4;
				LedStepRight();
				break;
			case STATE4:
				eLedState = STATE5;
				LedStepRight();
				break;
			case STATE5:
				eLedState = STATE0;
				LedStepRight();
				break;
		}
		Delay(500);
	}
}

