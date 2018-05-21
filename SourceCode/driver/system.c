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

#include "system.h"
#include "sky1311_drv.h"
#include "i2c.h"
#include "uart.h"
#include "timer.h"
#include "voltage.h"
#include "motor.h"
#include "key.h"
#include "protocol/x1000.h"

uint8_t system_state = NORMAL;


void set_system_state(RUN_STATE state){
    system_state = state;
}

/* 系统初始化 */
void system_Init(void)
{
    /* Select HSI as system clock source */
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

#ifdef HAVE_I2C
    I2C_Interface_Init();
#endif

#ifdef HAVE_TIMER
    TimingDelay_Init();   
#endif

#ifdef HAVE_UART
    Uart_Inerface_Init();
#endif
    
#ifdef HAVE_KEY
    key_init();
#endif

#ifdef HAVE_VOLTAGE
    init_adc_voltage();
#endif

#ifdef HAVE_MOTOR
    motor_init();
#endif

#ifdef HAVE_X1000
    init_x1000_protocol();
#endif    
   
    enableInterrupts(); 
}

/* 进入低功耗 active halt 状态 */
void system_ActiveHalt(void)
{
#ifdef HAVE_I2C    
    i2c_suspend();
#endif

#ifdef HAVE_TIMER
    timer_suspend();
#endif

#ifdef HAVE_UART
    uart_suspend();
#endif

#ifdef HAVE_VOLTAGE
    voltage_suspend();
#endif

#ifdef HAVE_KEY
    key_suspend();
#endif

    enableInterrupts();

    CLK_DeInit();
    
    CLK_HaltConfig(CLK_Halt_FastWakeup,ENABLE);
    PWR_FastWakeUpCmd(ENABLE);  
    PWR_UltraLowPowerCmd(ENABLE);
    halt();    

    PWR_UltraLowPowerCmd(DISABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    
#ifdef HAVE_I2C    
    i2c_wakeup();
#endif

#ifdef HAVE_TIMER
    timer_wakeup();
#endif

 #ifdef HAVE_UART
    uart_wakeup();
 #endif

#ifdef HAVE_VOLTAGE
    voltage_wakeup();
#endif

#ifdef HAVE_KEY
    key_wakeup();
#endif

    system_state = NORMAL;
  
}

void system_do(void){
    
    switch(system_state){
    
    case NORMAL:
#ifdef HAVE_CARD
      scan_card();
#endif

#ifdef HAVE_KEY
        key_scan(); 
        DelayMS(100);
#endif
        break;
    case SUSPEND:
        system_ActiveHalt();        
        break;
    case RESTART:
        break;
    }

}



