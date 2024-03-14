// Header
#include "LowLevel.h"

// Include
#include "Board.h"

// Functions
void LL_ToggleBoardLED()
{
	GPIO_Bit_Toggle(GPIOB, Pin_12);
}
//-----------------------------------

void LL_ExternalLED(bool State)
{
	GPIO_SetState(GPIO_LAMP_EXT, State);
}
//-----------------------------------

void LL_PowerSupplyStop(bool State)
{
	GPIO_SetState(GPIO_PS_MUTE, State);
}
//-----------------------------------

void LL_ExternalSync(bool State)
{
	GPIO_SetState(GPIO_SYNC_EXT, State);
}
//-----------------------------------

void LL_Contactor(bool State)
{
	GPIO_SetState(GPIO_CONTACTOR, State);
}
//-----------------------------------

void LL_AmpLock(bool State)
{
	GPIO_SetState(GPIO_AMP_LOCK, State);
}
//-----------------------------------

void LL_Demagnitization(bool State)
{
	GPIO_SetState(GPIO_DEMAGNET_SW, State);
}
//-----------------------------------

void LL_MuteChannel1(bool State)
{
	GPIO_SetState(GPIO_ACH1_MUTE, State);
}
//-----------------------------------

void LL_MuteChannel2(bool State)
{
	GPIO_SetState(GPIO_ACH2_MUTE, State);
}
//-----------------------------------

void LL_PowerOn(bool State)
{
	GPIO_SetState(GPIO_PS_230V_CTRL, State);
}
//-----------------------------------

void LL_Discharge(bool State)
{
	GPIO_SetState(GPIO_DISCHARGE, !State);
}
//-----------------------------------
