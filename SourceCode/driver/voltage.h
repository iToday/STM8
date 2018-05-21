/*
I2C 地址占用列表
-------------------------------------------

 Si4754：0xC2（可用地址四个：0xC0, 0xC2, 0xC4, 0xC6）
 ZL3560: 0x80
*/

#ifndef _VOLTAGE_H
#define _VOLTAGE_H

#include "../typedef.h"

#ifdef HAVE_VOLTAGE

#define ADC_PORT GPIOA
#define ADC_PIN  GPIO_Pin_3

#define USB_POWER_PORT GPIOA
#define USB_POWER_PIN GPIO_Pin_2

void empty_adcs();

void init_adc_voltage();

void update_voltage();

void set_usb_power_mode(uint8_t enable);

void set_voltage_listener(on_voltage voltage_cbk);

void voltage_suspend();

void voltage_wakeup();

#endif

#endif	//_I2C_H
