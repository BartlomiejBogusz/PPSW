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

void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
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

void ServoInit(unsigned int uiServoFrequency){
	ServoCallib();
	LedInit();
	Timer1Interrupts_Init((1000000/uiServoFrequency), &Automat);
}

int main (){
	KeyboardInit();
	DetectorInit();
	ServoInit(50);
	while(1){
	 	switch(eKeyboardRead()){
			case BUTTON_0:
				ServoCallib();
				break;
			case BUTTON_1:
				ServoGoTo(12);
				break;
			case BUTTON_2:
				ServoGoTo(24);
				break;
			case BUTTON_3:
				ServoGoTo(36);
				break;
			default:
				break;
		}
	}
}
