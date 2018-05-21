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

#include "voltage.h"

#ifdef HAVE_VOLTAGE


static on_voltage voltage_cbk = NULL;

#define MAX_ADCS 20

static uint16_t adcs_value[MAX_ADCS] = {0};
static uint8_t last_pos = 0;

void push_adc_value(uint16_t value){
    adcs_value[last_pos ++] = value;    
}

uint8_t is_adcs_enough(){
    return last_pos >= MAX_ADCS;
}

void empty_adcs(){
    last_pos = 0;
}

uint16_t get_average_adcs(){

    uint16_t min = 0;
    uint16_t max = 0;
    uint8_t index = 0;

    uint16_t totle = 0;

    for (index = 0; index < MAX_ADCS; index ++){

        if (adcs_value[index] > max)
            max = adcs_value[index];
        else if (adcs_value[index] < min)
            min = adcs_value[index];

        totle += adcs_value[index];
    }

    totle -= (min + max);

    return totle / (MAX_ADCS - 2);

}



void init_adc_voltage(){

    GPIO_Init(USB_POWER_PORT, USB_POWER_PIN , GPIO_Mode_Out_PP_Low_Slow);
    
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    /* Initialise and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_1);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_4Cycles);
    ADC_DMACmd(ADC1, DISABLE);
    ADC_VrefintCmd(ENABLE);
    /* Enable ADC1 */
   

    /* Enable ADC1 Channel 3 */
    ADC_ChannelCmd(ADC1, ADC_Channel_17, ENABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_17, DISABLE);
    ADC_Cmd(ADC1, ENABLE);

    last_pos = 0;
}

void set_voltage_listener(on_voltage cbk){
    voltage_cbk = cbk;
}

void set_usb_power_mode(uint8_t enable){

    if (enable)
        GPIO_SetBits(USB_POWER_PORT, USB_POWER_PIN);
    else
        GPIO_ResetBits(USB_POWER_PORT, USB_POWER_PIN);
}

void update_voltage(){

    uint16_t adc1_value;

    float32_t value;
    
    ADC_SoftwareStartConv(ADC1);

    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
     
    ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//清除对应标志
     
    adc1_value = ADC_GetConversionValue(ADC1); //获取转换值
     
	push_adc_value(adc1_value);
	
	if (is_adcs_enough()){
		
		value = 10*1.225*4096/get_average_adcs(); //获得VDD电压，单位V   
		empty_adcs();
		if (voltage_cbk != NULL)
			voltage_cbk((uint8_t)value);
	}
}

void voltage_suspend(){
    ADC_Cmd(ADC1, DISABLE);
    ADC_DeInit(ADC1);
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
}

void voltage_wakeup(){
    init_adc_voltage();
}

#endif

