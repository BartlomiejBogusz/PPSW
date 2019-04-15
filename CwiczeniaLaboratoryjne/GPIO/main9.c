#include <LPC21xx.H>

#define LED0_bm 1<<16

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main()
{
	IO1DIR = LED0_bm;
	while(1){
		IO1SET = LED0_bm;
		Delay(100);
		IO1CLR = LED0_bm;
		Delay(100);
	}
}
