// Include
//
#include "Global.h"
#include "Controller.h"
#include "Interrupts.h"
#include "SysConfig.h"
#include "BoardConfig.h"


// Forward functions
//
void SysClk_Config();
void IO_Config();
void CAN_Config();
void UART_Config();
void Timer2_Config();
void WatchDog_Config();


// Functions
//
int main()
{
	// Set request flag if firmware update is required
	if (*ProgramAddressStart == 0xFFFFFFFF || BOOT_LOADER_VARIABLE == BOOT_LOADER_REQUEST)
		WaitForFWUpload = TRUE;

	// Init peripherals
	SysClk_Config();
	IO_Config();
	CAN_Config();
	UART_Config();
	Timer2_Config();
	WatchDog_Config();

	// Init controller
	CONTROL_Init();

	// Infinite cycle
	while (true)
		CONTROL_Idle();

	return 0;
}
//--------------------------------------------

void SysClk_Config()
{
	RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//--------------------------------------------

void IO_Config()
{
	// ��������� ������������ ������
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);

	// ������
	GPIO_Config (GPIOA, Pin_8, Output, PushPull, HighSpeed, NoPull);	// PA8 - SYNC ����� ������� �������������
	GPIO_Bit_Rst(GPIOA, Pin_8);
	GPIO_Config (GPIOA, Pin_6, Output, PushPull, HighSpeed, NoPull);	// PA6 - PS_STOP ����� �������������� ��������� �������� ���������
	GPIO_Bit_Rst(GPIOA, Pin_6);
	GPIO_Config (GPIOB, Pin_0, Output, PushPull, HighSpeed, NoPull);	// PB0 - ACH1_RST ����� ������� ����������� ������ 1
	GPIO_Bit_Set(GPIOB, Pin_0);
	GPIO_Config (GPIOB, Pin_1, Output, PushPull, HighSpeed, NoPull);	// PB1 - ACH2_RST ����� ������� ����������� ������ 2
	GPIO_Bit_Set(GPIOB, Pin_1);
	GPIO_Config (GPIOB, Pin_2, Output, PushPull, HighSpeed, NoPull);	// PB2 - PS_ENABLE ��������� �������� ���������
	GPIO_Bit_Rst(GPIOB, Pin_2);
	GPIO_Config (GPIOB, Pin_4, Output, PushPull, HighSpeed, NoPull);	// PB4 - DSCHRG_SWITCH ��������� ��������� ����
	GPIO_Bit_Rst(GPIOB, Pin_4);
	GPIO_Config (GPIOB, Pin_10, Output, OpenDrain, HighSpeed, Pull_Up);	// PB10 - AMP_LOCK ������������ ������� ������� ���������� ��
	GPIO_Bit_Set(GPIOB, Pin_10);
	GPIO_Config (GPIOB, Pin_12, Output, PushPull, HighSpeed, NoPull);	// PB12 - LED ��������� �� ��
	GPIO_Bit_Rst(GPIOB, Pin_12);
	GPIO_Config (GPIOB, Pin_13, Output, PushPull, HighSpeed, NoPull);	// PB13 - IND ������� ���������
	GPIO_Bit_Rst(GPIOB, Pin_13);
	GPIO_Config (GPIOB, Pin_14, Output, PushPull, HighSpeed, NoPull);	// PB14 - DMGN_SWITCH ��������� ������� ���������������
	GPIO_Bit_Rst(GPIOB, Pin_14);
	GPIO_Config (GPIOB, Pin_15, Output, PushPull, HighSpeed, Pull_Up);	// PB15 - BC_CONTROL ���������� �����������
	GPIO_Bit_Set(GPIOB, Pin_15);

	// �������������� ������� ������
	GPIO_Config(GPIOA, Pin_9, AltFn, PushPull, HighSpeed, NoPull);		// PA9(USART1 TX)
	GPIO_AltFn(GPIOA, Pin_9, AltFn_7);

	GPIO_Config(GPIOA, Pin_10, AltFn, PushPull, HighSpeed, NoPull);		// PA10(USART1 RX)
	GPIO_AltFn(GPIOA, Pin_10, AltFn_7);

	GPIO_Config(GPIOA, Pin_11, AltFn, PushPull, HighSpeed, NoPull);		// PA11(CAN RX)
	GPIO_AltFn(GPIOA, Pin_11, AltFn_9);

	GPIO_Config(GPIOA, Pin_12, AltFn, PushPull, HighSpeed, NoPull);		// PA12(CAN TX)
	GPIO_AltFn(GPIOA, Pin_12, AltFn_9);
}
//--------------------------------------------

void CAN_Config()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, 0, 0);		// ������ 0 ���������� ��� ���������
}
//--------------------------------------------

void UART_Config()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//--------------------------------------------

void Timer2_Config()
{
	TIM_Clock_En(TIM_2);
	TIM_Config(TIM2, SYSCLK, TIMER2_uS);
	TIM_Interupt(TIM2, 0, true);
	TIM_Start(TIM2);
}
//--------------------------------------------

void WatchDog_Config()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//--------------------------------------------
