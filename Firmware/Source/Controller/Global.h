// -----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
#include "stdinc.h"
#include "SysConfig.h"
#include "Logic.h"

// Definitions
// 
// Global miscellaneous parameters
#define	SCCI_TIMEOUT_TICKS				1000						// (в мс)
// Password to unlock non-volatile area for write
#define ENABLE_LOCKING					FALSE
// -----------------------------------------------
#define EP_WRITE_COUNT					0							// Количество массивов для записи
#define EP_COUNT						8							// Количество массивов для чтения
#define VALUES_x_SIZE					PULSE_ARR_MAX_LENGTH		// Размер выходных массивов
#define ENABLE_LOCKING					FALSE
// -----------------------------------------------

// Временные параметры
#define TIME_LED_BLINK					500							// Период моргания светодиода на плате (в мс)
#define	TIME_DEMGNTZ					1000						// Время размагничивания сердечника и включения контактора (в мс)
#define TIME_SW_RELEASE_TIME			50							// Время на отключение реле размагничивания (в мс)
#define TIMEOUT_P2P_VOLTAGE				5000						// Таймаут выхода на напряжение между пульсами (суммируется с TIME_DEMGNTZ) (в мс)
// -----------------------------------------------

// Параметры формирования выходного импульса
#define PI_VALUE						3.1416f						// Значение числа пи
#define DAC_MAIN_PULSE_STOP				20.0f						// Время после основного импульса для удержания 0 по уставке (в мкс)
#define DAC_TIME_STEP					TIMER6_uS					// Дискрета времени ЦАП (в мкс)
#define MEASURE_AVG						10							// Количество сэмплов для усреднения результатов
#define LOAD_R_STDEV					3							// Среднеквадратичное отклонение сопротивления для резистора
#define ANALOG_OPTO_UNLOCK				500							// Задержка отключения оптопары, блокирующей ОС ОУ (в мкс)
//
#define PULSES_MAX						10							// Максимальное количество импульсов на измерение
#define PULSES_START_I					1000.0f						// Стартовый ток при выходе на мощность (в мА)
#define PULSES_POWER_REGULATOR_ERR		0.02f						// Допустимая ошибка регулятора по мощности (в %)
#define PULSES_POWER_MAX_ERR			0.07f						// Допустимая ошибка по мощности (в %)
#define PULSES_POWER_ERR_STOP			0.5f						// Ошибка по мощности, приводящая к остановке процесса (в %)
// -----------------------------------------------

// Параметры заряда батареи
#define	BAT_CHARGE_TIMEOUT				30000						// Время ожидания заряда после подачи питания (в мс)
#define	BAT_CHARGE_SHORT_TIMEOUT		5000						// Время ожидания заряда между импульсами (в мс)
#define BAT1_ADC1_CH					3							// Номер канала АЦП батареи 1
#define BAT2_ADC1_CH					4							// Номер канала АЦП батареи 2
#define BAT_VOLTAGE_DELTA				5.0f						// Гистерезис поддержания напряжения (в В)
// -----------------------------------------------

// Параметры оцифровки
#define ADC_REF_VOLTAGE					3300.0f						// Опорное напряжение (в В)
#define ADC_RESOLUTION					4095						// Разрешение АЦП
// -----------------------------------------------

// Параметры ЦАП
#define DAC_RESOLUTION					4095						// Разрешение ЦАП
// -----------------------------------------------

// Условия прерывания измерения
// ХХ
#define MEAS_BREAK_IDLE_V				9500.0f						// Максимальное рабочее напряжение (в В)

// КЗ
#define MEAS_BREAK_SHORT_V				100.0f						// Минимальное рабочее напряжение (в В)
// -----------------------------------------------

#endif //  __GLOBAL_H
