#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"

// Определения для аналоговых входов
GPIO_PortPinSettingMacro GPIO_ANLG_DUT_V =			{GPIOA, Pin_0};
GPIO_PortPinSettingMacro GPIO_ANLG_DUT_I_DUMMY =	{GPIOA, Pin_1};
GPIO_PortPinSettingMacro GPIO_ANLG_BUT2_V =			{GPIOA, Pin_2};
GPIO_PortPinSettingMacro GPIO_ANLG_BUT1_V =			{GPIOA, Pin_3};
GPIO_PortPinSettingMacro GPIO_ANLG_DAC_PULSE =		{GPIOA, Pin_4};
GPIO_PortPinSettingMacro GPIO_ANLG_DAC_OFFSET =		{GPIOA, Pin_5};
GPIO_PortPinSettingMacro GPIO_ANLG_DUT_I =			{GPIOA, Pin_7};

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_SYNC_EXT =			{GPIOA, Pin_8};
GPIO_PortPinSettingMacro GPIO_PS_MUTE =				{GPIOA, Pin_6};
GPIO_PortPinSettingMacro GPIO_ACH1_MUTE =			{GPIOB, Pin_0};
GPIO_PortPinSettingMacro GPIO_ACH2_MUTE =			{GPIOB, Pin_1};
GPIO_PortPinSettingMacro GPIO_PS_230V_CTRL =		{GPIOB, Pin_2};
GPIO_PortPinSettingMacro GPIO_DISCHARGE =			{GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_AMP_LOCK =			{GPIOB, Pin_10};
GPIO_PortPinSettingMacro GPIO_LED =					{GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_LAMP_EXT =			{GPIOB, Pin_13};
GPIO_PortPinSettingMacro GPIO_DEMAGNET_SW =			{GPIOB, Pin_14};
GPIO_PortPinSettingMacro GPIO_CONTACTOR =			{GPIOB, Pin_15};

// Определения для входных портов
GPIO_PortPinSettingMacro GPIO_OPENING_SEN =			{GPIOB, Pin_5};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX =			{GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX =			{GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART_RX =			{GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_UART_TX =			{GPIOA, Pin_9};

#endif // __BOARD_H
