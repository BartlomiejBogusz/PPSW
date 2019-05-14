#include "timer.h"
#include "led.h"

int main()
{
	LedInit();
	InitTimer0Match0(100000);
	while(1){
		WaitOnTimer0Match0();
		LedStepLeft();
	}
}
