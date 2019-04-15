#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}


void LedOn(unsigned char ucLedIndeks){
	
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	
	switch (ucLedIndeks){
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}

void LedInit(void){
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	LedOn(0);
}



int main()
{
	while(1){
		LedInit();
		Delay(250);
		LedOn(1);
		Delay(250);
		LedOn(2);
		Delay(250);
		LedOn(3);
		Delay(250);
		LedOn(5);
	}
}
