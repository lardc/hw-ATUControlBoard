//-----------------------------------------------
// Основная логика
//-----------------------------------------------

// Header
#include "Controller.h"
//
// Includes
#include "SysConfig.h"
#include "DataTable.h"
#include "SCCISlave.h"
#include "DeviceProfile.h"
#include "BCCITypes.h"
#include "Board.h"
#include "Global.h"
#include "LowLevel.h"
#include "Logic.h"
#include "Measurement.h"
#include "math.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = FALSE;
SubState SUB_State = SS_None;
volatile Int16U CONTROL_Values_Setpoint[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_DUTVoltage[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_DUTCurrent[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_SetCounter = 0;
volatile Int16U CONTROL_Values_ADCCounter = 0;
//
volatile Int16U CONTROL_Values_DiagVbr[PULSES_MAX];
volatile Int16U CONTROL_Values_DiagVrsm[PULSES_MAX];
volatile Int16U CONTROL_Values_DiagIrsm[PULSES_MAX];
volatile Int16U CONTROL_Values_DiagPrsm[PULSES_MAX];
volatile Int16U CONTROL_Values_DiagRstd[PULSES_MAX];
volatile Int16U CONTROL_Values_DiagEPCounter = 0;
//
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int64U CONTROL_TimeCounterDelay = 0;
//
// Параметры выхода на мощность
static Int16U CONTROL_PulsesRemain = 0;
static Boolean CONTROL_PowerRegulator = FALSE;
static float PowerTarget = 0, PowerRegulatorErrKi = 0;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_ResetToDefaults(bool StopPowerSupply);
void CONTROL_Idle();
void CONTROL_WatchDogUpdate();
void CONTROL_RegistersReset();
void CONTROL_SaveResultToEndpoints(ProcessResult Result);
void CONTROL_SaveResultToRegisters(ProcessResult Result);
uint16_t CONTROL_HandleWarningCondition(ProcessResult Result);

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = { EP_DUT_V,  EP_DUT_I, EP_SETPOINT,
								   EP_DIAG_DUT_VBR, EP_DIAG_DUT_VRSM, EP_DIAG_DUT_IRSM, EP_DIAG_DUT_PRSM, EP_DIAG_DUT_R_STD };
	Int16U EPSized[EP_COUNT] = { VALUES_x_SIZE, VALUES_x_SIZE, VALUES_x_SIZE,
								 PULSES_MAX, PULSES_MAX, PULSES_MAX, PULSES_MAX, PULSES_MAX };
	pInt16U EPCounters[EP_COUNT] = { (pInt16U)&CONTROL_Values_ADCCounter, (pInt16U)&CONTROL_Values_ADCCounter, (pInt16U)&CONTROL_Values_SetCounter,
									 (pInt16U)&CONTROL_Values_DiagEPCounter, (pInt16U)&CONTROL_Values_DiagEPCounter,
									 (pInt16U)&CONTROL_Values_DiagEPCounter, (pInt16U)&CONTROL_Values_DiagEPCounter, (pInt16U)&CONTROL_Values_DiagEPCounter };
	pInt16U EPDatas[EP_COUNT] = { (pInt16U)CONTROL_Values_DUTVoltage, (pInt16U)CONTROL_Values_DUTCurrent, (pInt16U)CONTROL_Values_Setpoint,
								  (pInt16U)CONTROL_Values_DiagVbr, (pInt16U)CONTROL_Values_DiagVrsm,
								  (pInt16U)CONTROL_Values_DiagIrsm, (pInt16U)CONTROL_Values_DiagPrsm, (pInt16U)CONTROL_Values_DiagRstd };

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = { (FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT };
	// Инициализация data table
	DT_Init(EPROMService, FALSE);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaults(TRUE);
}
//------------------------------------------------------------------------------

void CONTROL_ResetToDefaults(bool StopPowerSupply)
{
	LOGIC_ResetHWToDefaults(StopPowerSupply);

	SUB_State = SS_None;
	CONTROL_SetDeviceState(DS_None);

	DataTable[REG_FAULT_REASON] = 0;
	CONTROL_RegistersReset();
}
//------------------------------------------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;

	switch (ActionID)
	{
		case ACT_CLR_FAULT:
			{
				if (CONTROL_State == DS_Fault)
					CONTROL_ResetToDefaults(TRUE);
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = 0;
			break;

		case ACT_ENABLE_POWER:
			{
				if (CONTROL_State == DS_None)
				{
					LOGIC_StartBatteryCharge();
					CONTROL_TimeCounterDelay = CONTROL_TimeCounter + BAT_CHARGE_TIMEOUT;
					CONTROL_SetDeviceState(DS_BatteryCharge);
					SUB_State = SS_Charge;
				}
				else if (CONTROL_State != DS_Ready)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;

		case ACT_DISABLE_POWER:
			{
				if (CONTROL_State != DS_Disabled)
					CONTROL_ResetToDefaults(TRUE);
			}
			break;

		case ACT_SINGLE_PULSE:
			{
				if (CONTROL_State == DS_Ready)
				{
					CONTROL_RegistersReset();
					//
					CONTROL_PowerRegulator = FALSE;
					CONTROL_PulsesRemain = 1;
					//
					LOGIC_PrepareForPulse((float)DataTable[REG_SET_PRE_PULSE_CURRENT],
										  (float)DataTable[REG_SET_PULSE_CURRENT] * 2);
					CONTROL_TimeCounterDelay = CONTROL_TimeCounter + TIME_DEMGNTZ;
					CONTROL_SetDeviceState(DS_InProcess);
					SUB_State = SS_PulsePrepStep1;
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_START_TEST:
			{
				if (CONTROL_State == DS_Ready)
				{
					CONTROL_RegistersReset();
					//
					CONTROL_PowerRegulator = TRUE;
					CONTROL_PulsesRemain = PULSES_MAX;
					PowerTarget = (float)DataTable[REG_SET_PULSE_POWER] * 10;
					PowerRegulatorErrKi = 0;
					//
					LOGIC_PrepareForPulse((float)DataTable[REG_SET_PRE_PULSE_CURRENT],
										  PULSES_START_I);
					CONTROL_TimeCounterDelay = CONTROL_TimeCounter + TIME_DEMGNTZ;
					CONTROL_SetDeviceState(DS_InProcess);
					SUB_State = SS_PulsePrepStep1;
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_STOP_TEST:
			{
				if (CONTROL_State == DS_InProcess)
				{
					CONTROL_ResetToDefaults(FALSE);
					CONTROL_SetDeviceState(DS_Ready);
				}
			}
			break;

		case ACT_DBG_PULSE_DEMAGNET_SW:
			if (CONTROL_State == DS_None)
			{
				LL_Demagnitization(TRUE);
				Delay_mS(1000);
				LL_Demagnitization(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_SYNC:
			if (CONTROL_State == DS_None)
			{
				LL_Sync(TRUE);
				Delay_mS(1000);
				LL_Sync(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_DSCHRG_SW:
			if (CONTROL_State == DS_None)
			{
				LL_Discharge(TRUE);
				Delay_mS(1000);
				LL_Discharge(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_PS_SW:
			if (CONTROL_State == DS_None)
			{
				LL_PowerOn(TRUE);
				Delay_mS(1000);
				LL_PowerOn(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_CONTACTOR:
			if (CONTROL_State == DS_None)
			{
				LL_Contactor(TRUE);
				Delay_mS(1000);
				LL_Contactor(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_PS_STOP:
			if (CONTROL_State == DS_None)
			{
				LL_PowerSupplyStop(TRUE);
				Delay_mS(1000);
				LL_PowerSupplyStop(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_PULSE_EXT_LED:
			if (CONTROL_State == DS_None)
			{
				LL_ExternalLED(TRUE);
				Delay_mS(1000);
				LL_ExternalLED(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_GENERATE_DAC_SETPOINT:
			if (CONTROL_State == DS_None)
			{
				DEVPROFILE_ResetScopes(0);
				DEVPROFILE_ResetEPReadState();
				LOGIC_GeneratePulseForm((float)DataTable[REG_SET_PRE_PULSE_CURRENT],
										(float)DataTable[REG_SET_PULSE_CURRENT] * 2);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_DAC_PULSE:
			if (CONTROL_State == DS_Ready)
				LOGIC_DiagPulseDAC();
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		// Обратная совместимость
		case 72:
			break;

		default:
			return FALSE;
	}

	return TRUE;
}
//-----------------------------------------------

void CONTROL_HandleBatteryCharge()
{
	// Мониторинг уровня заряда батареи
	if (SUB_State == SS_Charge || SUB_State == SS_None || SUB_State == SS_PulsePrepCheckV)
	{
		float BatteryVoltage1 = MEASURE_BatteryVoltage1();
		float BatteryVoltage2 = MEASURE_BatteryVoltage2();
		float VoltageThreshold = (float)DataTable[REG_VBAT_THRESHOLD];

		DataTable[REG_BAT1_VOLTAGE] = (uint16_t)(BatteryVoltage1 * 10);
		DataTable[REG_BAT2_VOLTAGE] = (uint16_t)(BatteryVoltage2 * 10);

		// Переключение состояния в случае заряда
		if (SUB_State == SS_Charge)
		{
			if (BatteryVoltage1 >= VoltageThreshold && BatteryVoltage2 >= VoltageThreshold)
			{
				SUB_State = SS_None;
				CONTROL_SetDeviceState(DS_Ready);
			}
			else if (CONTROL_TimeCounterDelay < CONTROL_TimeCounter)
				CONTROL_SwitchToFault(DF_BATTERY);
		}

		// Поддержание уровня заряда
		if ((CONTROL_State == DS_Ready) ||
			(CONTROL_State == DS_InProcess && SUB_State == SS_PulsePrepCheckV))
		{
			if (BatteryVoltage1 >= (VoltageThreshold + BAT_VOLTAGE_DELTA) &&
				BatteryVoltage2 >= (VoltageThreshold + BAT_VOLTAGE_DELTA))
				LL_PowerSupplyStop(TRUE);

			if (BatteryVoltage1 < VoltageThreshold ||
				BatteryVoltage2 < VoltageThreshold)
				LL_PowerSupplyStop(FALSE);
		}
	}
}
//-----------------------------------------------

void CONTROL_SaveResultToEndpoints(ProcessResult Result)
{
	CONTROL_Values_DiagVbr[CONTROL_Values_DiagEPCounter]  = (uint16_t)Result.Vbr;
	CONTROL_Values_DiagVrsm[CONTROL_Values_DiagEPCounter] = (uint16_t)Result.Vrsm;
	CONTROL_Values_DiagIrsm[CONTROL_Values_DiagEPCounter] = (uint16_t)Result.Irsm;
	CONTROL_Values_DiagPrsm[CONTROL_Values_DiagEPCounter] = (uint16_t)(Result.Prsm / 10);
	CONTROL_Values_DiagRstd[CONTROL_Values_DiagEPCounter] = (uint16_t)(Result.Rstd * 100);
	CONTROL_Values_DiagEPCounter++;
}
//-----------------------------------------------

void CONTROL_SaveResultToRegisters(ProcessResult Result)
{
	DataTable[REG_PRE_VOLTAG]	= (uint16_t)Result.Vbr;
	DataTable[REG_VOLTAGE]		= (uint16_t)Result.Vrsm;
	DataTable[REG_CURRENT]		= (uint16_t)Result.Irsm;
	DataTable[REG_POWER]		= (uint16_t)(Result.Prsm / 10);
}
//-----------------------------------------------

void CONTROL_RegistersReset()
{
	DataTable[REG_PRE_VOLTAG] = 0;
	DataTable[REG_VOLTAGE] = 0;
	DataTable[REG_CURRENT] = 0;
	DataTable[REG_POWER] = 0;

	DataTable[REG_WARNING] = 0;
	DataTable[REG_PROBLEM] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//-----------------------------------------------

void CONTROL_HandlePulse()
{
	switch (SUB_State)
	{
		case SS_None:
		case SS_Charge:
			break;

		case SS_PulsePrepStep1:
			if (CONTROL_TimeCounterDelay < CONTROL_TimeCounter)
			{
				// Окончание размагничивания
				LL_Demagnitization(FALSE);
				CONTROL_TimeCounterDelay = CONTROL_TimeCounter + TIMEOUT_P2P_VOLTAGE;
				SUB_State = SS_PulsePrepCheckV;
			}
			break;

		case SS_PulsePrepCheckV:
			{
				// Проверка уровня напряжения на батареях
				float BatteryVoltage1 = MEASURE_BatteryVoltage1();
				float BatteryVoltage2 = MEASURE_BatteryVoltage2();
				float VoltageThreshold = (float)DataTable[REG_VBAT_THRESHOLD];

				if (BatteryVoltage1 >= VoltageThreshold && BatteryVoltage2 >= VoltageThreshold)
				{
					SUB_State = SS_PulsePrepStep2;
					CONTROL_TimeCounterDelay = CONTROL_TimeCounter + TIME_SW_RELEASE_TIME;
				}
				else if (CONTROL_TimeCounterDelay < CONTROL_TimeCounter)
					CONTROL_SwitchToFault(DF_BATTERY_P2P);
			}
			break;

		case SS_PulsePrepStep2:
			if (CONTROL_TimeCounterDelay < CONTROL_TimeCounter)
			{
				LOGIC_StartPulse();
				SUB_State = SS_PulseFinishWait;
			}
			break;

		case SS_PulseFinishWait:
			if (LOGIC_IsPulseFinished())
			{
				ProcessResult Result;

				// Уменьшение счётчика
				if (CONTROL_PulsesRemain)
					CONTROL_PulsesRemain--;
				DataTable[REG_COUNTER_MEASURE] = PULSES_MAX - CONTROL_PulsesRemain;

				// Обработка результатов
				LOGIC_PulseFinished();
				Result = LOGIC_ProcessOutputData();
				CONTROL_SaveResultToEndpoints(Result);

				// Проверка условий остановки
				uint16_t Warning = CONTROL_HandleWarningCondition(Result);

				// Ошибка по мощности
				float Perror = PowerTarget - Result.Prsm;

				// В случае критического роста ошибки (неустойчивость регулирования) - остановка
				if ((fabs(Perror) > (PowerTarget * PULSES_POWER_ERR_STOP)) &&
					(CONTROL_PulsesRemain < (PULSES_MAX - 1)) && CONTROL_PowerRegulator)
				{
					CONTROL_SwitchToFault(DF_FOLLOWING_ERROR);
				}
				else
				{
					// Проверка условий перехода к следующему шагу
					if ((fabs(Perror) > (PowerTarget * PULSES_POWER_REGULATOR_ERR)) &&
						(CONTROL_PulsesRemain > 0) && CONTROL_PowerRegulator && (Warning == WARNING_NONE))
					{
						float Isetpoint, Ki;

						// Следующий шаг
						CONTROL_TimeCounterDelay = CONTROL_TimeCounter + TIME_DEMGNTZ;
						SUB_State = SS_PulsePrepStep1;

						// Интегральная составляющая ошибки
						Ki = (float)DataTable[REG_PP_KI] / 1000;

						// Для первого импульса ошибка не учитывается
						if (CONTROL_PulsesRemain < (PULSES_MAX - 1))
							PowerRegulatorErrKi += Perror * Ki;

						// Расчёт корректировки
						if (Result.LoadR)
							Isetpoint = Result.Irsm * sqrt(PowerTarget / Result.Prsm) + PowerRegulatorErrKi;
						else
							Isetpoint = Result.Irsm * PowerTarget / Result.Prsm + PowerRegulatorErrKi;

						LOGIC_PrepareForPulse((float)DataTable[REG_SET_PRE_PULSE_CURRENT], Isetpoint);
					}
					else
					{
						// Регулятор не вышел на мощность
						if ((CONTROL_PulsesRemain == 0) && CONTROL_PowerRegulator && (Warning == WARNING_NONE) &&
							(fabs(Perror) > (PowerTarget * PULSES_POWER_MAX_ERR)))
							Warning = WARNING_ACCURACY;

						// Завершение работы
						SUB_State = SS_None;
						CONTROL_SetDeviceState(DS_Ready);
						CONTROL_SaveResultToRegisters(Result);
						DataTable[REG_WARNING] = Warning;

						LL_ExternalLED(FALSE);
						LL_Contactor(FALSE);
					}
				}
			}
			break;
	}

}
//-----------------------------------------------

uint16_t CONTROL_HandleWarningCondition(ProcessResult Result)
{
	if (Result.Vmax > MEAS_BREAK_IDLE_V && Result.Vbr > MEAS_BREAK_IDLE_V)
		return WARNING_IDLE;
	else if (Result.Vmax < MEAS_BREAK_SHORT_V && Result.Vbr < MEAS_BREAK_SHORT_V)
		return WARNING_SHORT;

	return WARNING_NONE;
}
//-----------------------------------------------

void CONTROL_Idle()
{
	// Process battery charge
	CONTROL_HandleBatteryCharge();

	// Handle pulse logic
	CONTROL_HandlePulse();

	// Process WD and interface
	CONTROL_WatchDogUpdate();
	DEVPROFILE_ProcessRequests();
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	LOGIC_ResetHWToDefaults(TRUE);
	//
	CONTROL_SetDeviceState(DS_Fault);
	SUB_State = SS_None;
	DataTable[REG_FAULT_REASON] = Reason;
}
//-----------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//-----------------------------------------------

void Delay_mS(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while (Counter != CONTROL_TimeCounter)
		CONTROL_WatchDogUpdate();
}
//-----------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if (BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//-----------------------------------------------
