// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "Constraints.h"

// Definitions
#define NO		0
#define YES		1

// Constants
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] =
{
	{0, INT16U_MAX, 0},								// 0
	{1, INT16U_MAX, K_I_TO_DAC},					// 1
	{0, INT16U_MAX, 0},								// 2
	{1, INT16U_MAX, K_ADC_TO_VBAT},					// 3
	{0, INT16U_MAX, 0},								// 4
	{1, INT16U_MAX, K_ADC_TO_VBAT},					// 5
	{0, VBAT_THR_MAX, VBAT_THR_DEF},				// 6
	{0, INT16U_MAX, 0},								// 7
	{1, INT16U_MAX, K_ADC_TO_VDUT},					// 8
	{0, INT16U_MAX, 0},								// 9
	{1, INT16U_MAX, 1000},							// 10
	{0, INT16U_MAX, 0},								// 11
	{0, INT16U_MAX, 0},								// 12
	{1, INT16U_MAX, K_ADC_TO_IDUT},					// 13
	{0, INT16U_MAX, 0},								// 14
	{1, INT16U_MAX, 1000},							// 15
	{0, INT16U_MAX, 0},								// 16
	{0, BASE_DAC_OFFS_MAX, 0},						// 17
	{OP_AMP_STAB_TIME_MIN, OP_AMP_STAB_TIME_MAX, OP_AMP_STAB_TIME_DEF}, // 18
	{0, OP_AMP_PRE_CURR_GAIN_MAX, 0},					// 19
	{DAC_PULSE_WIDTH_MIN, DAC_PULSE_WIDTH_MAX, DAC_PULSE_WIDTH_DEF}, // 20
	{0, SYNC_SHIFT_MAX, 0},							// 21
	{PP_KI_MIN, PP_KI_MAX, PP_KI_DEF},				// 22
	{0, INT16U_MAX, 1000},							// 23
	{0, 0, 0},										// 24
	{PRE_PULSE_CURR_MIN, PRE_PULSE_CURR_MAX, PRE_PULSE_CURR_DEF}, // 25
	{PULSE_TIME_MIN, PULSE_TIME_MAX, PULSE_TIME_DEF},	// 26
	{0, 10000, 0},									// 27
	{0, 0, 0},										// 28
	{0, 0, 0},										// 29
	{NO, YES, NO},									// 30
	{NO, YES, NO},									// 31
	{0, 100, 0},									// 32
	{0, 10000, 0},									// 33
	{0, PULSE_POW_MAX, 0},							// 34
	{0, 0, 0},										// 35
	{0, 0, 0},										// 36
	{0, 0, 0},										// 37
	{0, 0, 0},										// 38
	{0, 0, 0},										// 39
	{0, 0, 0},										// 40
	{0, 0, 0},										// 41
	{0, 0, 0},										// 42
	{0, 0, 0},										// 43
	{0, 0, 0},										// 44
	{0, 0, 0},										// 45
	{0, 0, 0},										// 46
	{0, 0, 0},										// 47
	{0, 0, 0},										// 48
	{0, 0, 0},										// 49
	{0, 0, 0},										// 50
	{0, 0, 0},										// 51
	{0, 0, 0},										// 52
	{0, 0, 0},										// 53
	{0, 0, 0},										// 54
	{0, 0, 0},										// 55
	{0, 0, 0},										// 56
	{0, 0, 0},										// 57
	{0, 0, 0},										// 58
	{0, 0, 0},										// 59
	{0, 0, 0},										// 60
	{0, 0, 0},										// 61
	{0, 0, 0},										// 62
	{0, 0, 0}										// 63
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] =
{
	{0, INT16U_MAX, 0},								// 64
	{PULSE_POW_MIN, PULSE_POW_MAX, PULSE_POW_DEF},	// 65
	{PULSE_CURRENT_MIN, PULSE_CURRENT_MAX, PULSE_CURRENT_DEF},		// 66
	{0, INT16U_MAX, 0},								// 67
	{0, 0, 0},										// 68
	{0, 0, 0},										// 69
	{0, DIAG_DAC_MAX_PULSE, 0},						// 70
	{0, 0, 0},										// 71
	{0, 0, 0},										// 72
	{0, 0, 0},										// 73
	{0, 0, 0},										// 74
	{0, 0, 0},										// 75
	{0, 0, 0},										// 76
	{0, 0, 0},										// 77
	{0, 0, 0},										// 78
	{0, 0, 0},										// 79
	{0, 0, 0},										// 80
	{0, 0, 0},										// 81
	{0, 0, 0},										// 82
	{0, 0, 0},										// 83
	{0, 0, 0},										// 84
	{0, 0, 0},										// 85
	{0, 0, 0},										// 86
	{0, 0, 0},								 		// 87
	{0, 0, 0},										// 88
	{0, 0, 0},										// 89
	{0, 0, 0},										// 90
	{0, 0, 0},										// 91
	{0, 0, 0},										// 92
	{0, 0, 0},										// 93
	{0, 0, 0},										// 94
	{0, 0, 0}										// 95
};
