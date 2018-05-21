/*
I2C 地址占用列表
-------------------------------------------

 Si4754：0xC2（可用地址四个：0xC0, 0xC2, 0xC4, 0xC6）
 ZL3560: 0x80
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "../typedef.h"

typedef enum {
    NORMAL,
    SUSPEND,
    RESTART,
} RUN_STATE;


void set_system_state(RUN_STATE state);

void system_Init(void);


void system_do(void);

#ifdef HAVE_CARD
void system_ActiveHalt(void);
#endif

#endif	//_I2C_H
