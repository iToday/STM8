

#ifndef _TIMER_H
#define _TIMER_H

#include "../typedef.h"

#ifdef HAVE_TIMER

void DelayMS(__IO uint16_t nTime);
void TimingDelay_Init(void);

void delay(uint8_t i);

void timer_suspend();

void timer_wakeup();

#endif

#endif	//_I2C_H
