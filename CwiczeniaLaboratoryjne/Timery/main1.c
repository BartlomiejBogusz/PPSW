#include "timer.h"
#include "led.h"

int main()
{
	InitTimer0();
	LedInit();
	WaitOnTimer0(100000);
	while(1){
		LedStepLeft();
		WaitOnTimer0(100000);
	}
}
