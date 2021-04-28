// -----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"


//Definitions
//
#define K_I_TO_DAC					53		// reg 1
//
#define K_ADC_TO_VBAT				90		// reg 3, 5
//
#define VBAT_THR_MAX				300		// reg 6
#define VBAT_THR_DEF				170		// reg 6
//
#define K_ADC_TO_VDUT				3264	// reg 8
//
#define K_ADC_TO_IDUT				14387	// reg 13
//
#define BASE_DAC_OFFS_MAX			200		// reg 17
//
#define OP_AMP_STAB_TIME_MIN		10		// reg 18
#define OP_AMP_STAB_TIME_MAX		500		// reg 18
#define OP_AMP_STAB_TIME_DEF		100		// reg 18
//
#define OP_AMP_PRE_CURR_GAIN_MAX	100		// reg 19
//
#define DAC_PULSE_WIDTH_MIN			100		// reg 20
#define DAC_PULSE_WIDTH_MAX			200		// reg 20
#define DAC_PULSE_WIDTH_DEF			100		// reg 20
//
#define SYNC_SHIFT_MAX				200		// reg 21
//
#define PP_KI_MIN					0		// reg 22
#define PP_KI_MAX					1000	// reg 22
#define PP_KI_DEF					100		// reg 22
//
#define PRE_PULSE_CURR_MIN			50		// reg 64
#define PRE_PULSE_CURR_MAX			300
#define PRE_PULSE_CURR_DEF			100
//
#define PULSE_POW_MIN				200		// reg 65
#define PULSE_POW_MAX				8000
#define PULSE_POW_DEF				1000
//
#define PULSE_CURRENT_MIN			250		// reg 66
#define PULSE_CURRENT_MAX			22500
#define PULSE_CURRENT_DEF			500
//
#define PULSE_TIME_MIN				100		// reg 67
#define PULSE_TIME_MAX				200
#define PULSE_TIME_DEF				100
//
#define DIAG_DAC_MAX_PULSE			1000	// reg 70


// Types
//
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;


// Variables
//
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];


#endif // __CONSTRAINTS_H
