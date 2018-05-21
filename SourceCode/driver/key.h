/*
I2C 地址占用列表
-------------------------------------------

 Si4754：0xC2（可用地址四个：0xC0, 0xC2, 0xC4, 0xC6）
 ZL3560: 0x80
*/

#ifndef _KEY_H
#define _KEY_H

#include "../typedef.h"

#ifdef HAVE_KEY

#define KEY_CODE_LOCK   60 //LINUX KEY_F2
#define KEY_CODE_UNLOCK 61 // LINUX KEY_F3
//#define KEY_CODE_RESET  59 // LINUX KEY_F1

#define KEY_CODE_PORT           GPIOB
#define KEY_CODE_LOCK_PIN       GPIO_Pin_3
#define KEY_CODE_UNLOCK_PIN     GPIO_Pin_4
//#define KEY_CODE_RESET_PIN      GPIO_Pin_2

#define INVALID_KEY  (0xFF)

enum KEY_STATE{
    KEY_UP,
    KEY_DOWN,
};

void set_key_listener(on_key keyfunc);

void key_scan();

void key_init();

void key_suspend();

void key_wakeup();

#endif

#endif	//_I2C_H
