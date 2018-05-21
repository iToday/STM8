
#include "../typedef.h"

#include "motor.h"

#ifdef HAVE_MOTOR
enum MOTOR_PARAMS_DIRECTION{
    FORWARD, //?y?¨°
    REVERSE, //¡¤¡ä?¨°
};


static uint8_t motor_direct = FORWARD;
static uint8_t motor_time = 100; //100ms uint

void motor_init(){
    GPIO_Init(MOTOR_PORT, MOTOR_A_PIN | MOTOR_B_PIN , GPIO_Mode_Out_PP_High_Slow);
}

void set_motor(uint8_t state){

    switch(state){
    case MOTOR_UNLOCK:

        if (motor_direct == FORWARD)
            GPIO_ResetBits(MOTOR_PORT, MOTOR_A_PIN);
        else
            GPIO_ResetBits(MOTOR_PORT, MOTOR_B_PIN);
        break;
    case MOTOR_LOCK:
        if (motor_direct == FORWARD)
            GPIO_ResetBits(MOTOR_PORT, MOTOR_B_PIN);
        else
            GPIO_ResetBits(MOTOR_PORT, MOTOR_A_PIN);
        break;
    default:
        GPIO_SetBits(MOTOR_PORT, MOTOR_A_PIN);
        GPIO_SetBits(MOTOR_PORT, MOTOR_B_PIN);
        break;

    }
}

void set_motor_params(uint8_t direct, uint8_t time){

    motor_direct = direct;
    motor_time = time;
}

void motor_suspend(){

}

void motor_wakeup(){

}
#endif

