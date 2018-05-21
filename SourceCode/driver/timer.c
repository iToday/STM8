/***********************************************************
Project  : T20
Compiler : T20
Version  : V1.0
Created  : 2010-01-06
Author   : Jason
Description
         Main function-
Modified
		 -
************************************************************/
#include "../typedef.h"

#include "timer.h"

#ifdef HAVE_TIMER
void delay(volatile uint8_t i){
    while(i--);
    {
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
    }
}

#define TIM2_PERIOD  (uint8_t) 124
/**
  * @addtogroup TIMING_DELAY_Functions
  * @{
  */
/**
  * @brief  timing delay init:to generate 1 ms time base using TIM2 update interrupt
  * @note   The external low speed clock (LSE) is used to ensure timing accuracy.
  *         This function should be updated in case of use of other clock source.
  * @param  None
  * @retval None
  */
void TimingDelay_Init(void)
{
  /* Enable TIM2 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  /* Time Base configuration */
  TIM2_TimeBaseInit(TIM2_Prescaler_128,TIM2_CounterMode_Up,TIM2_PERIOD);//定时器2,将主时钟16分频.自动装载FA=124
  TIM2_SetCounter(TIM2_PERIOD);                                //设定计数值FA=124
  TIM2_UpdateRequestConfig(TIM2_UpdateSource_Global);
  /* Clear TIM2 update flag */
  TIM2_ClearFlag(TIM2_FLAG_Update);
  /* Enable update interrupt */
  //TIM2_ITConfig(TIM2_IT_Update, ENABLE);
  //TIM2_Cmd(ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void DelayMS(volatile uint16_t nTime)
{
    TIM2_SetCounter(TIM2_PERIOD);
    TIM2_Cmd(ENABLE);
    while(nTime>0)
    {
        if(1==(TIM2->SR1 & 0x01))
        {
            TIM2_ClearITPendingBit(TIM2_IT_Update);
            if(nTime!=0)  nTime--;
        }
    }
    TIM2_Cmd(DISABLE);
}

void timer_suspend(){
    TIM2_DeInit();
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, DISABLE);
}

void timer_wakeup(){
    TimingDelay_Init();
}

#endif
