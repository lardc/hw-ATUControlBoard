#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_ExternalLED(bool State);
//
void LL_PowerSupplyStop(bool State);
void LL_Sync(bool State);
void LL_Contactor(bool State);
void LL_AmpLock(bool State);
void LL_Demagnitization(bool State);
void LL_MuteChannel1(bool State);
void LL_MuteChannel2(bool State);
void LL_PowerOn(bool State);
void LL_Discharge(bool State);

#endif //__LOWLEVEL_H
