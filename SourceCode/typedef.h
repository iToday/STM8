/******************************************************************************/
/*               (C) ˹���������������Ƽ����޹�˾(SKYRELAY)                   */
/*                                                                            */
/* �˴�����˹���������������Ƽ����޹�˾Ϊ֧�ֿͻ���д��ʾ�������һ����       */
/* ����ʹ��˹���������оƬ���û������޳�ʹ�øô��룬���豣������������       */
/* �������Ϊ��ʾʹ�ã�����֤�������е�Ӧ��Ҫ�󣬵����ض��淶������ʱ��       */
/* ʹ����������ȷ�ϴ����Ƿ����Ҫ�󣬲���Ҫ��ʱ����������Ӧ���޸ġ�           */
/* (V1.00)                                                                    */
/******************************************************************************/
/**
 ******************************************************************************
 ** �� �� ���� typedef.h
 **
 ** �ļ������� �����б����Ļ������͡��ṹ����������Ͷ���
 **
 ** �汾��ʷ:
 ** 2015-10-05 V1.00  Mark   ��ʽ�汾
 **
 ******************************************************************************/

#ifndef  __TYPEDEF_H_
#define  __TYPEDEF_H_

#include <stddef.h>
//#include "stdint.h"
#include "mcu.h"
#include "ring_buffer.h"

#define NOCHANGE    0
#define LARGEN      1
#define LESSEN      2
#define MINIMUM     3
#define MAXIMUM     4
/**
 ******************************************************************************
 ** \�������������Ͷ���
 **
 ******************************************************************************/
#ifndef TRUE
	/** Value is true (boolean_t type) */
    #define TRUE        ((boolean) 1)
    #define true        ((boolean) 1)
#endif

#ifndef FALSE
	/** Value is false (boolean_t type) */
    #define FALSE       ((boolean) 0)
	#define false       ((boolean) 0)
#endif

typedef uint8_t         boolean;

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;

/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCCI character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void         (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void         (*func_ptr_arg1_t)(uint8_t);

/* function pointer type for i2c/uart data buffer*/
typedef uint8_t        (*received_cbk)(PRING_BUFFER buf);

/*function pointer type for key report */
typedef uint8_t        (*on_key)(uint8_t code, uint8_t value);

/*function pointer type for voltage report */
typedef uint8_t        (*on_voltage)(uint8_t value);


typedef enum sta_result
{
    Ok                      = 0,  ///< �޴������ɹ�
    Error                   = 1,  ///< ���ض�����
    Timeout                 = 3,  ///< ��ʱ����
    RxParity			    = 4,  ///< ������żУ���
    RxCheckCRC			    = 5,  ///< ����CRCУ���
    FifoFull                = 6,  ///< FIFO��
    FifoEmpty               = 7,  ///< FIFO��
    Collision               = 8,  ///< ����ͻ����
    Framing                 = 9,  ///< ����֡����
    UIDFormat               = 10, ///< UID��ʽ����
    M1Error                 = 11, ///< ����M1������

    ErrorRequest            = 12,  ///< ִ��REQA/WUPA ����ʱ����
    ErrorAnticollision      = 13,  ///< ִ�з���ͻ����ANTICOLLISIONʱ����
    ErrorSelect             = 14,  ///< ִ��SELECT ����ʱ����
    ErrorAts                = 15,  ///< ִ��ATS�������
    ErrorInvalidMode            = 16,  ///< Operation not allowed in current mode
    ErrorUninitialized          = 17,  ///< Module (or part of it) was not initialized properly
    ErrorBufferFull             = 18,  ///< Circular buffer can not be written because the buffer is full
    ErrorTimeout                = 19,  ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ErrorNotReady               = 20, ///< A requested final state is not reached
    OperationInProgress         = 21,  ///< Indicator for operation in progress

	UnknowError				= 0x7F,
    NoResponse              = 0xFF
}sta_result_t,en_result_t;


typedef enum sta_field
{
    NoObjectIn              = 0,    ///< �����������޿�������
    PiccIn                  = 1,    ///< �п��ڳ���
    OtherObjectIn           = 2
}sta_field_t;


/** Returns the minimum value out of two values */
#define MIN( X, Y )  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define MAX( X, Y )  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define DIM( X )  (sizeof(X) / sizeof(X[0]))

#define _MEMCPY_(dst, src, len) \
{                               \
    uint8_t index = 0;          \
    do {                        \
        (dst)[index] = (src)[index];\
        index ++;               \
    }while (index < (len));     \
}

#define VERSION_BUFFER_SIZE             (8)

#define VERSION "1.00.00"   //the string length must less than VERSION_BUFFER_SIZE

#define HAVE_I2C
#define HAVE_UART
#define HAVE_TIMER
#define HAVE_KEY

#define HAVE_VOLTAGE
#define HAVE_X1000



#endif