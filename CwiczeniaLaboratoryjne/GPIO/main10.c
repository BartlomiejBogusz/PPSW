#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED3_bm 1<<19

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main()
{
	IO1DIR = LED3_bm;
	while(1){
		IO1SET = LED3_bm;
		Delay(100);
		IO1CLR = LED3_bm;
		Delay(100);
	}
}
