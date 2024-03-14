#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// Включить питание блока
#define ACT_DISABLE_POWER						2		// Выключить питание блока
#define ACT_CLR_FAULT							3		// Очистка ошибки
#define ACT_CLR_WARNING							4		// Очистка предупреждения
//
#define ACT_DBG_PULSE_DEMAGNET_SW				10		// Запуск размагничивающего тока на 1сек.
#define ACT_DBG_PULSE_SYNC						11		// Синхросигнал на 1сек.
#define ACT_DBG_PULSE_DSCHRG_SW					12		// Включение реле разряда на 1сек.
#define ACT_DBG_PULSE_PS_SW						13		// Подача питания на зарядные устройства на 1сек.
#define ACT_DBG_PULSE_PS_STOP					14		// Включение остановки зарядных устройств на 1сек.
#define ACT_DBG_PULSE_CONTACTOR					15		// Включение контактора на 1сек.
#define ACT_DBG_PULSE_EXT_LED					16		// Включение внешней индикации на 1сек.
#define ACT_DBG_OPENING_SENSOR					17		//считывание состояния датчика размыкания
//
#define ACT_DBG_GENERATE_DAC_SETPOINT			20		// Формирование массива уставки для ЦАП
#define ACT_DBG_DAC_PULSE						21		// Формирование импульса на ЦАП
//
#define ACT_SINGLE_PULSE						76		// Запуск формирования одиночного импульса
//
#define ACT_START_TEST							100		// Запуск процесса измерения
#define ACT_STOP_TEST							101		// Останов процесса измерения
//
#define ACT_SAVE_TO_ROM							200		// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201		// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202		// Сброс DataTable в состояние по умолчанию
//
#define ACT_BOOT_LOADER_REQUEST					320		// Перезапуск процессора с целью перепрограммирования


// REGISTERS
//
#define REG_I_TO_DAC_OFFSET						0		// Пересчёт уставки по току в значения ЦАП смещение (в тиках)
#define REG_I_TO_DAC_K							1		// Пересчёт уставки по току в значения ЦАП пропорциональный коэффициент х1000
//
#define REG_V_BAT1_OFFSET						2		// Смещение оцифрованного напряжения батареи 1 (в тиках)
#define REG_V_BAT1_K							3		// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение батареи 1 (в В) х1000
#define REG_V_BAT2_OFFSET						4		// Смещение оцифрованного напряжения батареи 2 (в тиках)
#define REG_V_BAT2_K							5		// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение батареи 1 (в В) х1000
#define REG_VBAT_THRESHOLD						6		// Порог заряда конденсаторной батареи (в В)
//
#define REG_V_DUT_OFFSET						7		// Смещение оцифрованного напряжения DUT (в тиках)
#define REG_V_DUT_K								8		// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение DUT (в В) х1000
#define REG_V_DUT_P0							9		// Полином точной корректировки напряжения DUT P0 (в вольтах)
#define REG_V_DUT_P1							10		// Полином точной корректировки напряжения DUT P1 x1000
#define REG_V_DUT_P2							11		// Полином точной корректировки напряжения DUT P2 x1e6
//
#define REG_I_DUT_OFFSET						12		// Смещение оцифрованного тока DUT (в тиках)
#define REG_I_DUT_K								13		// Коэффициент пересчёта напряжения АЦП (в мВ) в ток DUT (мА) х1000
#define REG_I_DUT_P0							14		// Полином точной корректировки тока DUT P0 (в вольтах)
#define REG_I_DUT_P1							15		// Полином точной корректировки тока DUT P1 x1000
#define REG_I_DUT_P2							16		// Полином точной корректировки тока DUT P2 x1e6
//
#define REG_DAC_BASE_OFFSET						17		// Смещение ЦАП, предшествующее работе формирователя (в тиках)
#define REG_OP_AMP_STAB_TIME					18		// Время выхода ОУ в рабочий режим (при заданном смещении) (в мкс)
#define REG_DAC_PRE_CURR_GAIN					19		// Коэффициент усиления начала импульса предварительного тока x10
#define REG_DAC_PULSE_WIDTH						20		// Подстройка фактической ширины импульса по уровню 50% (в мкс)
#define REG_SYNC_SHIFT							21		// Сдвиг сигнала синхронизации и точки измерения Vbr (в мкс)
//
#define REG_PP_KI								22		// Интегральный коэффициент импульсного регулятора х1000
#define REG_W_DUT_K								23		// Пропорциональный коэффциент пересчета мощности х1000
// -----------------------------------------------

#define REG_SET_PRE_PULSE_CURRENT				64		// Значение амплитуды предварительного импульса тока (в мА)
#define REG_SET_PULSE_POWER						65		// Значение требуемой мощности (в Вт /10)
#define REG_SET_PULSE_CURRENT					66		// Значение задания амплитуды основного импульса тока (в мА /2)
#define REG_SET_PRE_PULSE_TIME					67		// Длительность предварительного импульса (в мкс)
//
#define REG_DIAG_DAC_PULSE						70		// Уставка ЦАП для диагностического импульса
#define REG_OPENING_SEN							71		// Состояния датчика размыкания

// -----------------------------------------------

#define REG_DEV_STATE							96		// Статус работы блока
#define REG_FAULT_REASON						97		// Ошибка работы блока
#define REG_DISABLE_REASON						98		// Причина отключения блока
#define REG_WARNING								99		// Предупреждение
#define REG_PROBLEM								100		// Регистр Problem
//
#define REG_BAT1_VOLTAGE						103		// Напряжение на конденсаторной батарее 1 (в В х10)
#define REG_BAT2_VOLTAGE						104		// Напряжение на конденсаторной батарее 2 (в В х10)
#define REG_COUNTER_MEASURE						105		// Счетчик количества импульсов, потребовавшихся для получения требуемой мощности
//
#define REG_PRE_VOLTAG							109		// Измеренное значение напряжения лавинообразования (в В)
#define REG_VOLTAGE								110		// Измеренное значение напряжения в пике тока (в В)
#define REG_CURRENT								111		// Измеренное значение амплитуды тока (в мА)
#define REG_POWER								112		// Измеренное значение мощности (в Вт / 10)

#define REG_FWINFO_SLAVE_NID					256		// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257		// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN						260		// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261		// Begining of the information string record

// -----------------------------------------------

// ENDPOINTS
//
#define EP_DUT_V								1		// Оцифрованные данные напряжения DUT (в В)
#define EP_DUT_I								2		// Оцифрованные данные тока DUT (в мА)
#define EP_SETPOINT								3		// Данные уставки ЦАП (в тиках)
//
#define EP_DIAG_DUT_VBR							4		// Значения напряжения Vbr по пульсам (в В)
#define EP_DIAG_DUT_VRSM						5		// Значения напряжения Vrsm по пульсам (в В)
#define EP_DIAG_DUT_IRSM						6		// Значения тока Irsm по пульсам (в мА)
#define EP_DIAG_DUT_PRSM						7		// Значения мощности по пульсам (в Вт /10)
#define EP_DIAG_DUT_R_STD						8		// СКО сопротивления нагрузки х100


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// Ошибка заряда батареи
#define DF_BATTERY_P2P							2		// Ошибка заряда батареи между импульсами
#define DF_FOLLOWING_ERROR						3		// Ошибка регулирования мощности

// WARNINGS
//
#define WARNING_NONE							0
#define WARNING_IDLE							1		// ХХ на выходе
#define WARNING_SHORT							2		// КЗ на выходе
#define WARNING_ACCURACY						3		// Погрешность полученной мощности велика
#define WARNING_BREAK							4		// Пробой прибора
#define WARNING_FACET_BREAK						5		// Пробой по фаске

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2		// Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3		// Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4		// Неправильный ключ


#endif // __DEV_OBJ_DIC_H
