#ifndef __LOGIC_H
#define __LOGIC_H

#include "stdinc.h"

// Definitions
//
#define PULSE_ARR_MAX_LENGTH	1300
//
typedef enum __HighSpeedState
{
	HSS_None					 = 0,
	HSS_AnalogUnlockOpto		 = 1,
	HSS_AnalogUnlockMosfets		 = 2,
	HSS_Plate					 = 3,
	HSS_PulseTop				 = 4,
	HSS_PulseEnd				 = 5,
	HSS_WaitFinish				 = 6
} HighSpeedState;
//
typedef struct __ProcessResult
{
	float Vbr;
	float Vrsm;
	float Irsm;
	float Prsm;
	float Max_dVdt;
	float Vmax;
	float Rstd;
	bool LoadR;
} ProcessResult, *pProcessResult;

// Variables
//
extern volatile uint16_t LOGIC_OutputPulse[];
extern volatile uint16_t LOGIC_DUTCurrentRaw[];
extern volatile uint16_t LOGIC_DUTVoltageRaw[];
extern volatile uint16_t LOGIC_DataCounter;
extern volatile HighSpeedState HS_State;
extern uint16_t TimeOpAmpStabilize, TimePreCurrentPlate, TimeSyncShift;
extern float TimePulseWidth;

//Functions
//
void LOGIC_ResetHWToDefaults(bool StopPowerSupply);
void LOGIC_StartBatteryCharge();
void LOGIC_PrepareForPulse(float PrePulseCurrent, float PulseCurrent);
void LOGIC_StartPulse();
bool LOGIC_IsPulseFinished();
void LOGIC_PulseFinished();
void LOGIC_GeneratePulseForm(float PrePulseCurrent, float PulseCurrent);
ProcessResult LOGIC_ProcessOutputData();
void LOGIC_DiagPulseDAC();

#endif //__LOGIC_H
