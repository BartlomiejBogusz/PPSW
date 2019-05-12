#include <LPC21xx.H>
enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT;

int main(){
	
	while(1){
		switch(eLedState){
			case LED_LEFT:
				eLedState = LED_RIGHT;
				break;
			case LED_RIGHT:
				eLedState = LED_LEFT;
				break;
		}
	}
}

