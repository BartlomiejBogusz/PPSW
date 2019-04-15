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


void KeyboardInit(){
	IO0DIR = IO0DIR&(~(S0|S1|S2|S3));
}


enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead(){
	if(S0 == (~IO0PIN & S0)){
		return BUTTON_0;
	}
	else if(S1 == (~IO0PIN & S1)){
		return BUTTON_2;
	}
	else if(S2 == (~IO0PIN & S2)){
		return BUTTON_1;
	}
	else if(S3 == (~IO0PIN & S3)){
		return BUTTON_3;
	}
	return RELASED;
}



unsigned char ucWhichDiode = 0; 
enum Direction {LEFT, RIGHT};

void LedStep(enum Direction eWhere){
	if(eWhere == LEFT){
		++ucWhichDiode;
		LedOn(ucWhichDiode % 4);
	}
	else if(eWhere == RIGHT){
		--ucWhichDiode;
		LedOn(ucWhichDiode % 4);
	}
}

int main()
{
	LedInit();
	while(1){
		unsigned char ucCounter;
		for(ucCounter = 0; ucCounter < 9; ucCounter++){
			LedStep(LEFT);
			Delay(150);
		}
		for(ucCounter = 0; ucCounter < 9; ucCounter++){
			LedStep(RIGHT);
			Delay(150);
		}
	}
}
