#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// �������� ������� �����
#define ACT_DISABLE_POWER						2		// ��������� ������� �����
#define ACT_CLR_FAULT							3		// ������� ������
#define ACT_CLR_WARNING							4		// ������� ��������������
//
#define ACT_DBG_PULSE_DEMAGNET_SW				10		// ������ ����������������� ���� �� 1���.
#define ACT_DBG_PULSE_SYNC						11		// ������������ �� 1���.
#define ACT_DBG_PULSE_DSCHRG_SW					12		// ��������� ���� ������� �� 1���.
#define ACT_DBG_PULSE_PS_SW						13		// ������ ������� �� �������� ���������� �� 1���.
#define ACT_DBG_PULSE_PS_STOP					14		// ��������� ��������� �������� ��������� �� 1���.
#define ACT_DBG_PULSE_CONTACTOR					15		// ��������� ���������� �� 1���.
#define ACT_DBG_PULSE_EXT_LED					16		// ��������� ������� ��������� �� 1���.
//
#define ACT_DBG_GENERATE_DAC_SETPOINT			20		// ������������ ������� ������� ��� ���
#define ACT_DBG_DAC_PULSE						21		// ������������ �������� �� ���
//
#define ACT_SINGLE_PULSE						76		// ������ ������������ ���������� ��������
//
#define ACT_START_TEST							100		// ������ �������� ���������
#define ACT_STOP_TEST							101		// ������� �������� ���������
//
#define ACT_SAVE_TO_ROM							200		// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM					201		// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT					202		// ����� DataTable � ��������� �� ���������
//
#define ACT_BOOT_LOADER_REQUEST					320		// ���������� ���������� � ����� ��������������������


// REGISTERS
//
#define REG_I_TO_DAC_OFFSET						0		// �������� ������� �� ���� � �������� ��� �������� (� �����)
#define REG_I_TO_DAC_K							1		// �������� ������� �� ���� � �������� ��� ���������������� ����������� �1000
//
#define REG_V_BAT1_OFFSET						2		// �������� ������������� ���������� ������� 1 (� �����)
#define REG_V_BAT1_K							3		// ����������� ��������� ���������� ��� (� ��) � ���������� ������� 1 (� �) �1000
#define REG_V_BAT2_OFFSET						4		// �������� ������������� ���������� ������� 2 (� �����)
#define REG_V_BAT2_K							5		// ����������� ��������� ���������� ��� (� ��) � ���������� ������� 1 (� �) �1000
#define REG_VBAT_THRESHOLD						6		// ����� ������ �������������� ������� (� �)
//
#define REG_V_DUT_OFFSET						7		// �������� ������������� ���������� DUT (� �����)
#define REG_V_DUT_K								8		// ����������� ��������� ���������� ��� (� ��) � ���������� DUT (� �) �1000
#define REG_V_DUT_P0							9		// ������� ������ ������������� ���������� DUT P0 (� �������)
#define REG_V_DUT_P1							10		// ������� ������ ������������� ���������� DUT P1 x1000
#define REG_V_DUT_P2							11		// ������� ������ ������������� ���������� DUT P2 x1e6
//
#define REG_I_DUT_OFFSET						12		// �������� ������������� ���� DUT (� �����)
#define REG_I_DUT_K								13		// ����������� ��������� ���������� ��� (� ��) � ��� DUT (��) �1000
#define REG_I_DUT_P0							14		// ������� ������ ������������� ���� DUT P0 (� �������)
#define REG_I_DUT_P1							15		// ������� ������ ������������� ���� DUT P1 x1000
#define REG_I_DUT_P2							16		// ������� ������ ������������� ���� DUT P2 x1e6
//
#define REG_DAC_BASE_OFFSET						17		// �������� ���, �������������� ������ ������������� (� �����)
#define REG_OP_AMP_STAB_TIME					18		// ����� ������ �� � ������� ����� (��� �������� ��������) (� ���)
#define REG_DAC_PRE_CURR_GAIN					19		// ����������� �������� ������ �������� ���������������� ���� x10
#define REG_DAC_PULSE_WIDTH						20		// ���������� ����������� ������ �������� �� ������ 50% (� ���)
#define REG_SYNC_SHIFT							21		// ����� ������� ������������� � ����� ��������� Vbr (� ���)
//
#define REG_PP_KI								22		// ������������ ����������� ����������� ���������� �1000

// -----------------------------------------------

#define REG_SET_PRE_PULSE_CURRENT				64		// �������� ��������� ���������������� �������� ���� (� ��)
#define REG_SET_PULSE_POWER						65		// �������� ��������� �������� (� �� /10)
#define REG_SET_PULSE_CURRENT					66		// �������� ������� ��������� ��������� �������� ���� (� �� /2)
#define REG_SET_PRE_PULSE_TIME					67		// ������������ ���������������� �������� (� ���)
//
#define REG_DIAG_DAC_PULSE						70		// ������� ��� ��� ���������������� ��������

// -----------------------------------------------

#define REG_DEV_STATE							96		// ������ ������ �����
#define REG_FAULT_REASON						97		// ������ ������ �����
#define REG_DISABLE_REASON						98		// ������� ���������� �����
#define REG_WARNING								99		// ��������������
#define REG_PROBLEM								100		// ������� Problem
//
#define REG_BAT1_VOLTAGE						103		// ���������� �� �������������� ������� 1 (� � �10)
#define REG_BAT2_VOLTAGE						104		// ���������� �� �������������� ������� 2 (� � �10)
#define REG_COUNTER_MEASURE						105		// ������� ���������� ���������, ��������������� ��� ��������� ��������� ��������
//
#define REG_PRE_VOLTAG							109		// ���������� �������� ���������� ����������������� (� �)
#define REG_VOLTAGE								110		// ���������� �������� ���������� � ���� ���� (� �)
#define REG_CURRENT								111		// ���������� �������� ��������� ���� (� ��)
#define REG_POWER								112		// ���������� �������� �������� (� �� / 10)


// ENDPOINTS
//
#define EP_DUT_V								1		// ������������ ������ ���������� DUT (� �)
#define EP_DUT_I								2		// ������������ ������ ���� DUT (� ��)
#define EP_SETPOINT								3		// ������ ������� ��� (� �����)
//
#define EP_DIAG_DUT_VBR							4		// �������� ���������� Vbr �� ������� (� �)
#define EP_DIAG_DUT_VRSM						5		// �������� ���������� Vrsm �� ������� (� �)
#define EP_DIAG_DUT_IRSM						6		// �������� ���� Irsm �� ������� (� ��)
#define EP_DIAG_DUT_PRSM						7		// �������� �������� �� ������� (� �� /10)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// ������ ������ �������
#define DF_BATTERY_P2P							2		// ������ ������ ������� ����� ����������
#define DF_FOLLOWING_ERROR						3		// ������ ������������� ��������

// WARNINGS
//
#define WARNING_NONE							0
#define WARNING_IDLE							1		// �� �� ������
#define WARNING_SHORT							2		// �� �� ������
#define WARNING_ACCURACY						3		// ����������� ���������� �������� ������
#define WARNING_BREAK							4		// ������ �������
#define WARNING_FACET_BREAK						5		// ������ �� �����

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED					2		// �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY					3		// ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD							4		// ������������ ����


#endif // __DEV_OBJ_DIC_H
