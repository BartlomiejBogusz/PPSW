#include <LPC21xx.H>
#include "timer.h"

#define Counter_Enable (1<<0)
#define Counter_Reset (1<<1)
#define Interrupt_On_MR0 (1<<0)
#define Reset_On_MR0 (1<<1)

void InitTimer0(void){
	T0TCR = Counter_Enable;
}

void WaitOnTimer0(unsigned int uiTime){
	
	T0TCR = T0TCR | Counter_Reset;
	T0TCR = T0TCR & ~Counter_Reset;
	while ((uiTime*15) > T0TC){}                       //T0TC taktowanie 15mln/s
}

void InitTimer0Match0(unsigned int uiDelayTime){
	
	T0MR0 = uiDelayTime*15;
	T0MCR = T0MCR | Reset_On_MR0;
	T0MCR = T0MCR | Interrupt_On_MR0;
	T0TCR = T0TCR | Counter_Enable;
}

void WaitOnTimer0Match0(){
	
	while(T0IR == 0){}
	T0IR = Interrupt_On_MR0;
}
