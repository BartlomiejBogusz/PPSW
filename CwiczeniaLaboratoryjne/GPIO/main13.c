#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

void LedInit(void){
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

int main()
{
	while(1){
		LedInit();
		Delay(250);
		IO1CLR = LED0_bm;
		IO1SET = LED1_bm;
		Delay(250);
		IO1CLR = LED1_bm;
		IO1SET = LED2_bm;
		Delay(250);
		IO1CLR = LED2_bm;
		IO1SET = LED3_bm;
		Delay(250);
		IO1CLR = LED3_bm;
	}
}
