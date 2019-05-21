#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum DetectorState{ACTIVE, INACTIVE};


struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};
struct Servo sServo;


void DetectorInit(void){
	IO0DIR = IO0DIR &(~DETECTOR_bm);
}

enum DetectorState eReadDetector(void){
	
	if((IO0PIN & DETECTOR_bm) == 0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

void Automat(void){
	
		switch(sServo.eState){
			case CALLIB:
				if(eReadDetector() == INACTIVE){
					LedStepLeft();
				}
				else{
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				}
				break;
			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
				}
				break;
			case IN_PROGRESS:
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					LedStepRight();
					sServo.uiCurrentPosition++;
					sServo.eState = IN_PROGRESS;
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					LedStepLeft();
					sServo.uiCurrentPosition--;
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
				}
		}
}

int main (){
	LedInit();
	KeyboardInit();
	DetectorInit();
	Timer1Interrupts_Init(5, &Automat);
	while(1){
	 	switch(eKeyboardRead()){
			case BUTTON_0:
				sServo.eState = CALLIB;
				break;
			case BUTTON_1:
				sServo.eState = IN_PROGRESS;
				sServo.uiDesiredPosition = 12;
				break;
			case BUTTON_2:
				sServo.eState = IN_PROGRESS;
				sServo.uiDesiredPosition = 24;
				break;
			case BUTTON_3:
				sServo.eState = IN_PROGRESS;
				sServo.uiDesiredPosition = 36;
				break;
			case RELASED:
				break;
			default:
				break;
		}
	}
}
