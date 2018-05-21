
#include "I2C.h"
#include "timer.h"

static received_cbk i2c_cbk = NULL;

static RING_BUFFER i2c_tx_buffer;
static RING_BUFFER i2c_rx_buffer;

uint8_t i2c_send(uint8_t* buffer, uint8_t len){
    
    uint8_t index = 0;
    uint8_t res = true;
    
    for (index = 0; index < len; index ++){
        res = res && RING_BUFFER_CALL(i2c_tx_buffer, push, buffer[index]);
    }

    return res;
}


PRING_BUFFER get_i2c_tx_buffer(){
    return &i2c_tx_buffer;
}

PRING_BUFFER get_i2c_rx_buffer(){
    return &i2c_rx_buffer;
}


uint8_t i2c_receive_end(){
    
    if (i2c_cbk != NULL && !RING_BUFFER_CALL_VOID(i2c_rx_buffer, is_empty)){
        
        i2c_cbk(&i2c_rx_buffer);  
    }
    
    return 0;
}

uint8_t i2c_received(uint8_t byte){

    RING_BUFFER_CALL(i2c_rx_buffer, push, byte);
    return 0;
}

void set_i2c_received_callback(received_cbk cbk){

    i2c_cbk = cbk;
}


void notify_i2c_read_data(){
         
    GPIO_SetBits(I2C_IRQ_PORT, I2C_IRQ_PIN);
    delay(5);
    GPIO_ResetBits(I2C_IRQ_PORT, I2C_IRQ_PIN);
}

void I2C_Interface_Init(void)
{
    init_ring_buffer(&i2c_tx_buffer);
    init_ring_buffer(&i2c_rx_buffer);

    GPIO_Init(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_Mode_In_PU_No_IT);        // PC.00
    GPIO_Init(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_Mode_In_PU_No_IT);   // PC.01
    GPIO_Init(I2C_IRQ_PORT, I2C_IRQ_PIN, GPIO_Mode_Out_PP_Low_Fast);   // PB.02

    CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);
    
    I2C_DeInit(I2C1);
    
    I2C_ITConfig(I2C1, (I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);  

#ifdef HAVE_CARD 
    I2C_Init(I2C1, I2C_MAX_STANDARD_FREQ, 0x08 << 1,I2C_Mode_I2C, I2C_DutyCycle_2,
    I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);

#else
    I2C_Init(I2C1, I2C_MAX_STANDARD_FREQ, 0x09 << 1,I2C_Mode_I2C, I2C_DutyCycle_2,
    I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
#endif

    I2C_Cmd(I2C1, ENABLE);
}

void i2c_suspend(){
    
    disableInterrupts();
    GPIO_Init(I2C_GPIO_PORT, I2C_SDA_PIN|I2C_SCL_PIN, GPIO_Mode_Out_PP_High_Slow);
    I2C_Cmd(I2C1, DISABLE);
    I2C_DeInit(I2C1);
    CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, DISABLE);

    GPIO_Init(I2C_IRQ_PORT, I2C_IRQ_PIN, GPIO_Mode_Out_OD_Low_Slow);

}

void i2c_wakeup(){
     
    I2C_Interface_Init();    
}


