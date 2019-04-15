#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}


int main()
{
	KeyboardInit();
	LedInit();
	while(1){
		switch(eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
		}
		Delay(200);
	}
}
