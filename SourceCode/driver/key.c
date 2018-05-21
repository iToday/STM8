/***********************************************************
Project  : T20
Compiler : T20
Version  : V1.0
Created  : 2010-01-06
Author   : Jason
Description
         Main function-
Modified
		 -
************************************************************/
#include "../typedef.h"

#include "key.h"

#ifdef HAVE_KEY

static on_key key_cbk = NULL;

static enum KEY_STATE last_state = KEY_UP;
static uint8_t last_code = INVALID_KEY;

void set_key_listener(on_key keyfunc){
    key_cbk = keyfunc;
}

static void update_key_state(uint8_t key, enum KEY_STATE state){

    if (state == KEY_DOWN){
        
        if (last_code != key){
            
           if (last_state == KEY_DOWN){
               
               last_state = KEY_UP; // reset last key
               
               if (key_cbk != NULL)
                   key_cbk(last_code, last_state);          
            } 

           last_state = KEY_DOWN; // update new key
           last_code = key;

           if (key_cbk != NULL)
              key_cbk(last_code, last_state);
        }
        
    } else {// KEY UP

        if (last_state == KEY_DOWN) {

            last_state = KEY_UP;
            
            if (key_cbk != NULL)
                key_cbk(last_code, last_state);
            
            last_code = INVALID_KEY;
            
        }
    }

}

void key_scan(){

    uint8_t now_code = 0xFF - GPIO_ReadInputData(KEY_CODE_PORT);

    if (now_code & KEY_CODE_LOCK_PIN){

       update_key_state(KEY_CODE_LOCK, KEY_DOWN);

    } else if (now_code & KEY_CODE_UNLOCK_PIN) {
    
       update_key_state(KEY_CODE_UNLOCK, KEY_DOWN);
       
    }/* else if (now_code & KEY_CODE_RESET_PIN) {
    
       update_key_state(KEY_CODE_RESET_PIN, KEY_DOWN);
       
    }*/ else {

        update_key_state(INVALID_KEY, KEY_UP);
    }    
    
}

void key_init(){

    GPIO_Init(KEY_CODE_PORT, KEY_CODE_LOCK_PIN | KEY_CODE_UNLOCK_PIN , GPIO_Mode_In_PU_No_IT);
 
}

void key_suspend(){
    
    disableInterrupts();
    
    GPIO_Init(KEY_CODE_PORT, KEY_CODE_LOCK_PIN | KEY_CODE_UNLOCK_PIN, GPIO_Mode_In_PU_IT);
    EXTI_ClearITPendingBit(EXTI_IT_Pin3);
    EXTI_ClearITPendingBit(EXTI_IT_Pin4);
    EXTI_SelectPort(EXTI_Port_B);
    EXTI_SetPinSensitivity(EXTI_Pin_3, EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_4, EXTI_Trigger_Falling);
}

void key_wakeup(){
     GPIO_Init(KEY_CODE_PORT, KEY_CODE_LOCK_PIN | KEY_CODE_UNLOCK_PIN , GPIO_Mode_In_PU_No_IT);
     EXTI_SelectPort(EXTI_Port_B);
     EXTI_ClearITPendingBit(EXTI_IT_Pin3);
     EXTI_ClearITPendingBit(EXTI_IT_Pin4);
     EXTI_DeInit();
}

#endif

