#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define S0 1<<4
#define S1 1<<6
#define S2 1<<5
#define S3 1<<7

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}

void LedInit(void){
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	
	//IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	
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

enum ButtonState {RELEASED, PRESSED};

int ReadButton1(){
	unsigned int uiReturnNumber;
	uiReturnNumber = ((IO0PIN & S0) == S0) ? RELEASED : PRESSED; 
	return uiReturnNumber;
}

int main()
{
	LedInit();
	while(1){
		if(ReadButton1()==PRESSED){
			IO1CLR = LED0_bm;
		}
		else if(ReadButton1()==RELEASED){
			IO1CLR = LED1_bm;
		}
		switch(ReadButton1()){
			case RELEASED:
				LedOn(0);
				break;
			case PRESSED:
				LedOn(1);
				break;
		}
	}
}
