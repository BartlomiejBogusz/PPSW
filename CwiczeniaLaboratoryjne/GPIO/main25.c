#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

#define S0_bm 1<<4
#define S1_bm 1<<5
#define S2_bm 1<<6
#define S3_bm 1<<7

void Delay(unsigned int uiOpoznienie){
	int iLicznik;
	for(iLicznik=0; iLicznik<5450*uiOpoznienie; iLicznik++);
}


void LedInit(void){
	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
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
	IO0DIR = IO0DIR&(~(S0_bm|S1_bm|S2_bm|S3_bm));
}


enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead(){
	if(0 == (IO0PIN & S0_bm)){ //1x s0
		return BUTTON_0;
	}
	else if(0 == (IO0PIN & S1_bm)){ //dla wcisnietego: 0x00, dla niewcisnietego: 0x10
		return BUTTON_2;
	}
	else if(0 == (IO0PIN & S2_bm)){ // dla wcisnietego: 0x00, dla niewcisnietego: 0x20
		return BUTTON_1;
	}
	else if(0 == (IO0PIN & S3_bm)){
		return BUTTON_3;
	}
	return RELASED;
}

//git test

enum Direction {LEFT, RIGHT};

void LedStep(enum Direction eWhere){
	static unsigned char ucWhichDiode = 0; 
	if(eWhere == LEFT){
		ucWhichDiode++;  // konwencje
	}
	else if(eWhere == RIGHT){
		ucWhichDiode--;  // konwencje
	}
	LedOn(ucWhichDiode % 4);
}

void LedStepLeft(void){
	LedStep(LEFT);
}

void LedStepRight(void){
	LedStep(RIGHT);
}

int main()
{
	KeyboardInit();
	LedInit();
	while(1){
		switch(eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
		}
		Delay(200);
	}
}
