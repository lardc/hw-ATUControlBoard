// Header
#include "LowLevel.h"

// Functions
//
// LED on board
void LL_ToggleBoardLED()
{
	GPIO_Bit_Toggle(GPIOB, Pin_12);
}
//------------------------------------------------------------------------------

// External LED
void LL_ExternalLED(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_13) : GPIO_Bit_Rst(GPIOB, Pin_13);
}
//------------------------------------------------------------------------------

// Unit cooler
void LL_PowerSupplyStop(bool State)
{
	State ? GPIO_Bit_Set(GPIOA, Pin_6) : GPIO_Bit_Rst(GPIOA, Pin_6);
}
//------------------------------------------------------------------------------

// External SYNC
void LL_Sync(bool State)
{
	State ? GPIO_Bit_Set(GPIOA, Pin_8) : GPIO_Bit_Rst(GPIOA, Pin_8);
}
//------------------------------------------------------------------------------

// Contactor control
void LL_Contactor(bool State)
{
	State ? GPIO_Bit_Rst(GPIOB, Pin_15) : GPIO_Bit_Set(GPIOB, Pin_15);
}
//------------------------------------------------------------------------------

// Amplifier lock control
void LL_AmpLock(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_10) : GPIO_Bit_Rst(GPIOB, Pin_10);
}
//------------------------------------------------------------------------------

// Demagnitization coil control
void LL_Demagnitization(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_14) : GPIO_Bit_Rst(GPIOB, Pin_14);
}
//------------------------------------------------------------------------------

// Channel 1 control
void LL_MuteChannel1(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_0) : GPIO_Bit_Rst(GPIOB, Pin_0);
}
//------------------------------------------------------------------------------

// Channel 2 control
void LL_MuteChannel2(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_1) : GPIO_Bit_Rst(GPIOB, Pin_1);
}
//------------------------------------------------------------------------------

// Power Supply control
void LL_PowerOn(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_2) : GPIO_Bit_Rst(GPIOB, Pin_2);
}
//------------------------------------------------------------------------------

// Discharge control
void LL_Discharge(bool State)
{
	State ? GPIO_Bit_Rst(GPIOB, Pin_4) : GPIO_Bit_Set(GPIOB, Pin_4);
}
//------------------------------------------------------------------------------
