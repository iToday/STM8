

#ifndef _I2C_H
#define _I2C_H

#include "../typedef.h"

#define I2C_BUFFER_SIZE 128

#define INVALID_POS (0xFF)

/* GPIO for I2C*/
#define I2C_GPIO_PORT           GPIOC
#define I2C_SDA_PIN             GPIO_Pin_0
#define I2C_SDA_PORT            GPIOC
#define I2C_SCL_PIN             GPIO_Pin_1
#define I2C_SCL_PORT            GPIOC

#ifdef HAVE_CARD
#define I2C_IRQ_PIN             GPIO_Pin_4
#define I2C_IRQ_PORT            GPIOC
#else
#define I2C_IRQ_PIN             GPIO_Pin_2
#define I2C_IRQ_PORT            GPIOB
#endif

uint8_t i2c_send(uint8_t* buffer, uint8_t len);

PRING_BUFFER get_i2c_tx_buffer();
PRING_BUFFER get_i2c_rx_buffer();


uint8_t i2c_received(uint8_t byte);

uint8_t i2c_receive_end();


void set_i2c_received_callback(received_cbk cbk);

void notify_i2c_read_data();

void I2C_Interface_Init(void);

void i2c_suspend();

void i2c_wakeup();


#endif	//_I2C_H
