/******************************************************************************/
/*               (C) 斯凯瑞利（北京）科技有限公司(SKYRELAY)                   */
/*                                                                            */
/* 此代码是斯凯瑞利（北京）科技有限公司为支持客户编写的示例程序的一部分       */
/* 所有使用斯凯瑞利相关芯片的用户可以无偿使用该代码，但需保留本声明部分       */
/* 本代码仅为演示使用，不保证符合所有的应用要求，当有特定规范或需求时，       */
/* 使用者需自行确认代码是否符合要求，不合要求时自行做出相应的修改。           */
/* (V1.10)                                                                    */
/******************************************************************************/
/**
 ******************************************************************************
 ** 文 件 名： stm8l_adc.c
 **
 ** 文件简述： 操作sky1311s的所有函数，常量和变量
 **
 ** 版本历史:
 ** 2015-10-05 V1.00  EH   第一个正式版本
 ** 2017-03-25 V1.10       根据STM8L MCU移植修改的版本
 **
 ******************************************************************************/
#include "mcu.h"
/*
 * 初始化ADC模块和端口
 * AD接口是ADC_IN17(PB1)
 * 参考电压
*/
void ADC1_Init(void)
{
    CLK->PCKENR2 |= CLK_Peripheral_ADC1;        //开启ADC1时钟
    ADC1->CR1 = 0x40;                //8位精度，中断关闭，单次模式
    ADC1->CR2 = 0x81;                //CK/2，软件触发，9 ADC时钟
    //ADC1->CR3 = 0x11;
    ADC1->CR1 |= ADC_CR1_ADON;
    ADC1->SQR[2] = 0x02;             //channel 17 enable
}

/**
  * @brief  Configure ADC peripheral
  * @param  None
  * @retval None
  */
void ADC_Config(void)
{
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    /* Initialise and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_8Bit, ADC_Prescaler_1);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_4Cycles);
    ADC_DMACmd(ADC1, DISABLE);
    /* Enable ADC1 */
    //ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 Channel 3 */
    ADC_ChannelCmd(ADC1, ADC_Channel_17, ENABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_17, DISABLE);

    /* Enable End of conversion ADC1 Interrupt */
    //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

    /* Start ADC1 Conversion using Software trigger*/
    //ADC_SoftwareStartConv(ADC1);
}


void ADC_Start(void)
{
    //ADC1->CR1 |= 0x02;
    ADC1->CR1 |= ADC_CR1_START;
    //ADC_SoftwareStartConv(ADC1);
}

uint8_t readADC(void)
{
    while(0==ADC1->SR & ADC_SR_EOC);
    ADC1->SR = 0;
    return ADC1->DRL;
    //return = ADC_GetConversionValue(ADC1);
}