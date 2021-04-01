#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "Board.h"

//Functions
//
void SysClk_Config();
void IO_Config();
void CAN_Config();
void UART_Config();
void ADC_Config();
void ADC_SwitchToBase();
void ADC_SwitchToHighSpeed();
void Timer2_Config();
void Timer3_Config();
void Timer6_Config();
void DAC_Config();
void DAC_SwitchToHighSpeed();
void DAC_SwitchToBase();
void DMA_Config();
void WatchDog_Config();
void InitializeController(Boolean GoodClock);

#endif //__INITCONFIG_H
