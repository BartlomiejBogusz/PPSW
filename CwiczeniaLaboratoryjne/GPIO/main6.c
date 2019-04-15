#include <LPC21xx.H>

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

int main()
{
	Delay(17);
}
