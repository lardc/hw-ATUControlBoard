// Header
#include "StorageDescription.h"
#include "Global.h"

// Variables
RecordDescription StorageDescription[] =
{
	{"DUT Voltage",			DT_Int16U,	VALUES_x_SIZE},
	{"DUT Current",			DT_Int16U, 	VALUES_x_SIZE},
	{"DUT Counter",			DT_Int16U, 	1},

	{"Setpoint",			DT_Int16U, 	VALUES_x_SIZE},
	{"Setpoint Counter",	DT_Int16U, 	1},

	{"Pulse Vbr",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Vrsm",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Irsm",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Prsm",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Rstd",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Iset",			DT_Int16U, 	PULSES_MAX},
	{"Pulse Counter",		DT_Int16U, 	1}
};
Int32U TablePointers[sizeof(StorageDescription) / sizeof(StorageDescription[0])] = {0};
const Int16U StorageSize = sizeof(StorageDescription) / sizeof(StorageDescription[0]);
