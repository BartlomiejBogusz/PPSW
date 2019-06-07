#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "serwo.h"

#define DETECTOR_bm (1<<10)

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
	while(sServo.eState != IDLE){}
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
	while(sServo.eState != IDLE){}
}

void Automat(void){
	
		switch(sServo.eState){
			case CALLIB:
				if(eReadDetector() == INACTIVE){
					LedStepRight();
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
	Timer1Interrupts_Init((1000000/uiServoFrequency), &Automat);
	LedInit();
	ServoCallib();
}
