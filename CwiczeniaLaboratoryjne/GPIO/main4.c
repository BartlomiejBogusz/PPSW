#include <LPC21xx.H>

void Delay(){
	int iLicznik;
	for(iLicznik=0; iLicznik<1000; iLicznik++);
}

int main()
{
	IO1DIR=0x010000;
	
	while(1){
		IO1SET=0x010000;
		Delay();
		IO1CLR=0x010000;
	}
}
