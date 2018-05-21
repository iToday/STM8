/***********************************************************/

#include "../typedef.h"
#include "i2c.h"
#include "key.h"
#include "motor.h"
#include "x1000.h"
#include "voltage.h"
#include "stm8l15x.h"
#include "system.h"
#include "uart.h"
#include <stdio.h>

#ifdef HAVE_X1000
static uint8_t is_frame_head(uint8_t b){
    return b >= MSG_TYPE_MIN && b <= MSG_TYPE_MAX;
}

static void send_version(){
    union mcu_i2c_msg msg;

    msg.version.type = MSG_TYPE_SLAVE_S_VERSION;
    msg.version.eof = MSG_PACKET_EOP;

    _MEMCPY_(msg.version.buf, VERSION, VERSION_BUFFER_SIZE);

    i2c_send(msg.buf, sizeof (struct version_t));

    notify_i2c_read_data();
}

static uint8_t  recv_cbk(PRING_BUFFER ring){

    union mcu_i2c_msg* msg;
    uint8_t buf[RING_BUFFER_SIZE] = {0};

    PRING_BUFFER_CALL(ring, clone, buf);
    PRING_BUFFER_CALL_VOID(ring, clear);
   
    if (is_frame_head(buf[0])){
        
        msg = (union mcu_i2c_msg*)buf;

        if (msg->motor.type == MSG_TYPE_MASTER_S_MOTOR
            && msg->motor.eof == MSG_PACKET_EOP){
            // motor data
            set_motor(msg->motor.direct);
            
        } else if (msg->power.type == MSG_TYPE_MASTER_S_POWER
            && msg->power.eof == MSG_PACKET_EOP){
            // set usb power
            set_usb_power_mode(msg->power.mode);
            
        } else  if (msg->pm.type == MSG_TYPE_MASTER_S_SUSPEND
            && msg->pm.eof == MSG_PACKET_EOP){
            // pm data
            set_system_state(SUSPEND);        
           
        } else  if (msg->externd.type == MSG_TYPE_MASTER_S_EXTERN
            && msg->externd.eof == MSG_PACKET_EOP){
            //uart data
            
        } else if (msg->version.type == MSG_TYPE_MASTER_G_VERSION
            && msg->version.eof == MSG_PACKET_EOP){

            send_version();
           
        } else if (msg->motor.type == MSG_TYPE_MASTER_S_MOTOR_PARAMS
            && msg->motor.eof == MSG_PACKET_EOP){
            set_motor_params(msg->motor.direct, msg->motor.time);

        } else if (msg->audio.type == MSG_TYPE_MASTER_S_AUDIO
            && msg->audio.eof == MSG_PACKET_EOP){
            // play audio
        }

    }

    return 0;
   
}

static uint8_t key_cbk(uint8_t code, uint8_t value){

    union mcu_i2c_msg msg;
    msg.key.type = MSG_TYPE_SLAVE_S_KEYCODE;
    msg.key.code = code;
    msg.key.value = value;
    msg.key.eof = MSG_PACKET_EOP;

    i2c_send(msg.buf, sizeof (struct key_t));

    notify_i2c_read_data();
    
    return 0;
}

static uint8_t voltage_cbk(uint8_t value){

    union mcu_i2c_msg msg;
    msg.voltage.type = MSG_TYPE_SLAVE_S_VOLTAGE;
    msg.voltage.voltage = value;
    msg.voltage.eof = MSG_PACKET_EOP;

    i2c_send(msg.buf, sizeof (struct key_t));

    notify_i2c_read_data();
    return 0;
}

void init_x1000_protocol(){

    set_i2c_received_callback(recv_cbk);
    set_key_listener(key_cbk);
    set_voltage_listener(voltage_cbk);
}

#endif
