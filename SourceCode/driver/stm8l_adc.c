/******************************************************************************/
/*               (C) ˹���������������Ƽ����޹�˾(SKYRELAY)                   */
/*                                                                            */
/* �˴�����˹���������������Ƽ����޹�˾Ϊ֧�ֿͻ���д��ʾ�������һ����       */
/* ����ʹ��˹���������оƬ���û������޳�ʹ�øô��룬���豣������������       */
/* �������Ϊ��ʾʹ�ã�����֤�������е�Ӧ��Ҫ�󣬵����ض��淶������ʱ��       */
/* ʹ����������ȷ�ϴ����Ƿ����Ҫ�󣬲���Ҫ��ʱ����������Ӧ���޸ġ�           */
/* (V1.10)                                                                    */
/******************************************************************************/
/**
 ******************************************************************************
 ** �� �� ���� stm8l_adc.c
 **
 ** �ļ������� ����sky1311s�����к����������ͱ���
 **
 ** �汾��ʷ:
 ** 2015-10-05 V1.00  EH   ��һ����ʽ�汾
 ** 2017-03-25 V1.10       ����STM8L MCU��ֲ�޸ĵİ汾
 **
 ******************************************************************************/
#include "mcu.h"
/*
 * ��ʼ��ADCģ��Ͷ˿�
 * AD�ӿ���ADC_IN17(PB1)
 * �ο���ѹ
*/
void ADC1_Init(void)
{
    CLK->PCKENR2 |= CLK_Peripheral_ADC1;        //����ADC1ʱ��
    ADC1->CR1 = 0x40;                //8λ���ȣ��жϹرգ�����ģʽ
    ADC1->CR2 = 0x81;                //CK/2�����������9 ADCʱ��
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