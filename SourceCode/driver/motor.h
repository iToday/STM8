/*
I2C 地址占用列表
-------------------------------------------

 Si4754：0xC2（可用地址四个：0xC0, 0xC2, 0xC4, 0xC6）
 ZL3560: 0x80
*/

#ifndef _MOTOR_H
#define _MOTOR_H

#include "../typedef.h"

#ifdef HAVE_MOTOR

enum MOTOR_DIRECTION{
	MOTOR_NONE,
	MOTOR_UNLOCK,
	MOTOR_LOCK,
};


#define MOTOR_PORT      GPIOB
#define MOTOR_A_PIN     GPIO_Pin_5
#define MOTOR_B_PIN     GPIO_Pin_6



void motor_init();

void set_motor(uint8_t state);

void set_motor_params(uint8_t direct, uint8_t time);


void motor_suspend();

void motor_wakeup();
#endif

#endif	//_I2C_H
