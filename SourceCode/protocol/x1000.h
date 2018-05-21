/*
-------------------------------------

*/

#ifndef _X1000_H
#define _X1000_H

#include "../typedef.h"

#define MSG_PACKET_MAX_LEN              (128)    /* i2c packet length */
#define MSG_PACKET_SOP                  (0x00)   /* start of packet marker */
#define MSG_PACKET_EOP                  (0xff)   /* end of packet marker */
#define MSG_TYPE_MASTER_G_PACKET        (0xfe)   /* master gets message packet from slave */
#define MSG_TYPE_MASTER_S_SUSPEND       (0xfd)   /* master orders slave into suspend */
#define MSG_TYPE_MASTER_S_RESUME        (0xfc)   /* master resumes slave from suspend */
#define MSG_TYPE_SLAVE_S_KEYCODE        (0xfb)   /* slave sends keycode to master */
#define MSG_TYPE_SLAVE_S_PM_STATE       (0xfa)   /* slave sends pm state to master */
#define MSG_TYPE_MASTER_G_PM_STATE      (0xf9)   /* master gets slave pm state */
#define MSG_TYPE_SLAVE_S_CARD_UID       (0xf8)   /* slave sends card uid to master */
#define MSG_TYPE_MASTER_G_CARD_UID      (0xf7)   /* master gets card uid from slave */
#define MSG_TYPE_SLAVE_S_SECTOR_DATA    (0xf6)   /* slave sends card sector data to master */
#define MSG_TYPE_MASTER_G_SECTOR_DATA   (0xf5)   /* master gets card sector data from slave */
#define MSG_TYPE_MASTER_S_ACK           (0xf4)   /* master sends ACK to slave */
#define MSG_TYPE_SLAVE_S_ACK            (0xf3)   /* slave sends ACK to master */


#define MSG_TYPE_MASTER_S_MOTOR			(0xF2)	/*notify mcu control motor 0 stop , 1 right, -1 left*/
#define MSG_TYPE_MASTER_S_POWER         (0xF1)  /*switch usb power */
#define MSG_TYPE_SLAVE_S_VOLTAGE		(0xF0)  /*the voltage from mcu*/
#define MSG_TYPE_MASTER_S_EXTERN		(0xEF)  /*send data to extern device by mcu*/
#define MSG_TYPE_SLAVE_S_EXTERN			(0xEE)  /*recive data from extern device by mcu*/
#define MSG_TYPE_MASTER_G_VERSION       (0xED)
#define MSG_TYPE_SLAVE_S_VERSION        (0xEC)
#define MSG_TYPE_SLAVE_S_MOTOR			(0xEB)	/*notify to x1000, motor state*/

#define MSG_TYPE_MASTER_G_MOTOR			(0xEA)	/*request motor state*/
#define MSG_TYPE_MASTER_S_MOTOR_PARAMS	(0xE9)	/*set motor params*/

#define MSG_TYPE_MASTER_S_AUDIO         (0xE8)  /*sound play*/

#define MSG_TYPE_MIN        MSG_TYPE_MASTER_S_AUDIO
#define MSG_TYPE_MAX        MSG_TYPE_MASTER_G_PACKET

#define EXTERN_BUFFER_SIZE              (64)

enum card_type {    
    CARD_TYPE_A = 0,    
    CARD_TYPE_B = 1,    
    CARD_MIFARE1 = 2,
    };



struct motor_t{	
    unsigned char type;	
    unsigned char direct;
    unsigned char time; //100 ms	
    unsigned char lock; //lock/unlock
    unsigned char eof;
    };

struct power_t{	
    unsigned char type;	
    unsigned char mode;
    unsigned char eof;
    };

struct audio_t{
    unsigned char type;
    unsigned char index;
    unsigned char mode;
    unsigned char eof;
    };

struct voltage_t{	
    unsigned char type;	
    unsigned char voltage;
    unsigned char eof;
    };

struct extern_t{	
    unsigned char type;	
    unsigned char len;	
    unsigned char buf[EXTERN_BUFFER_SIZE];
    unsigned char eof;
    };

struct version_t{
    unsigned char type;
    unsigned char buf[VERSION_BUFFER_SIZE];
    unsigned char eof;
    };

struct pm_t {    
    unsigned char type;    
    unsigned char state;    
    unsigned char eof;
    };

struct ack_t {    
    unsigned char type;    
    unsigned char eof;
    };

struct key_t {    
    unsigned char type;    
    unsigned char code;    
    unsigned char value;    
    unsigned char eof;
    };

struct card_t {    
    unsigned char type;    
    unsigned char cardtype;    
    unsigned char uid[10];    
    unsigned char sector;    
    unsigned char keytype;    
    unsigned char m1keyA[6];    
    unsigned char m1keyB[6];    
    unsigned char data[64];    
    unsigned char eof;
    };

union mcu_i2c_msg {    
    unsigned char buf[MSG_PACKET_MAX_LEN];    
    struct pm_t pm;    
    struct ack_t ack;    
    struct key_t key;    
    struct card_t card;	
    struct motor_t motor;	
    struct voltage_t voltage;	
    struct extern_t externd;
    struct power_t power;
    struct version_t version;
    struct audio_t audio;
    };

#ifdef HAVE_X1000
void init_x1000_protocol();

void notify_x1000_read_data();
#endif
#endif	
