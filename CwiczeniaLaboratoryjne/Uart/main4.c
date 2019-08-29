#include "led.h"
#include "uart.h"
#include "serwo.h"

#define NULL 0

int main(){
	extern char cOdebranyZnak;
	int iservoCounter=0;
	UART_InitWithInt(9600);                 //czas wyslania 1 bitu 1/9600 = 0.00010416666s = 104.166666us
	ServoInit(150);                         //czas wyslania 10 znakow: 104.166666us*120 = 12499.99992us = 0.0125s     (10 znaków - 120 bitów) 

	while(1){
		switch(cOdebranyZnak){
			case '1':
				iservoCounter++;
				ServoGoTo(12*(iservoCounter%4));
				cOdebranyZnak = NULL;
				break;
			case '2':
				ServoGoTo(24);
				break;
			case '3':
				ServoGoTo(36);
				break;
			case 'c':
				ServoCallib();
				break;
			default:
				break;
		}
	}
}
