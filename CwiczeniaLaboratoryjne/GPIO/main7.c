#include <LPC21xx.H>

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main()
{
	IO1DIR = 0x010000;
	while(1){
		IO1SET=0x010000;
		Delay(1000);
		IO1CLR=0x010000;
		Delay(1000);
	}
}
