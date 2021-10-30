/*
 * GAS_Scheduler.c
 *
 *  Created on: Oct 30, 2020
 *      Author: Suprhimp
 *      		InitusNovus
 */


#include "GAS_Scheduler.h"
#include "stdio.h"
#include "tim.h"
//#include "GAS_Can.h"


extern uint8_t canRx0Data[8];
extern volatile uint16_t ValueOfADC[5];
uint8_t pin_state;

#define False 0
#define True 1

volatile int gTimerCnt;

Scheduler_task gTask;

void GAS_Scheduler_init(void);
static void GAS_Scheduler_taskCounter_1ms(void);
static void GAS_Scheduler_taskCounter_10ms(void);
static void GAS_Scheduler_taskCounter_100ms(void);
static void GAS_Scheduler_taskCounter_1000ms(void);
static void GAS_Scheduler_taskBackground(void);
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_SYSTICK_Callback(void);
void GAS_Schduler(void);

void GAS_Scheduler_init(void)
{
//	if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
//	  {
//		  Error_Handler();
//	  }
	SysTick_Config(SystemCoreClock/1000);

//********ADC initialization********=

//********CAN initialization********
	GAS_Can_init();

//********PWM initialization********
<<<<<<< Updated upstream
	GAS_PWM_inputInit();
	GAS_PWM_outputInit();
=======
>>>>>>> Stashed changes

}



static inline __attribute__((always_inline)) void GAS_Scheduler_taskCounter_1ms(void)
{
<<<<<<< Updated upstream
	GAS_Vadc_dmaIn();
//	GAS_Vadc_getValue();
//	GAS_Can_sendMessage();
	GAS_PWM_changeOutput_ch1(ValueOfADC[0]);
=======
//	GAS_Can_sendMessage();

>>>>>>> Stashed changes
}

static inline __attribute__((always_inline)) void GAS_Scheduler_taskCounter_10ms(void)
{
<<<<<<< Updated upstream
//	GAS_Can_sendMessage();
=======

>>>>>>> Stashed changes
}

uint8_t Count100ms = 0;
static inline __attribute__((always_inline)) void GAS_Scheduler_taskCounter_100ms(void)
{
	Count100ms += 1;
	if (Count100ms >5){
		GAS_BulkADC_run_100ms();
		Count100ms = 0;
	}

}
static inline __attribute__((always_inline)) void GAS_Scheduler_taskCounter_1000ms(void)
{
<<<<<<< Updated upstream
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_15);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
=======
	HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);

#ifdef INVCON_TEST
	InverterControl_test_1000ms();
#endif
>>>>>>> Stashed changes
}
static inline __attribute__((always_inline)) void GAS_Scheduler_taskBackground(void)
{

}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
void HAL_SYSTICK_Callback(void)
{
	gTimerCnt++;

	gTask.flag_1ms=True;

	if(gTimerCnt % 10 == 0)
	{
		gTask.flag_10ms=True;
	}

	if(gTimerCnt % 100 == 0)
	{
		gTask.flag_100ms=True;
	}

	if(gTimerCnt == 1000)
	{
		gTask.flag_1000ms=True;
		gTimerCnt = 0;
	}
}

void GAS_Scheduler(void)
{
	if(gTask.flag_1ms == True)
	{
		gTask.flag_1ms = False;
		GAS_Scheduler_taskCounter_1ms();
	}

	if(gTask.flag_10ms == True)
	{
		gTask.flag_10ms = False;
		GAS_Scheduler_taskCounter_10ms();
	}

	if(gTask.flag_100ms == True)
	{
		gTask.flag_100ms = False;
		GAS_Scheduler_taskCounter_100ms();
	}

	if(gTask.flag_1000ms == True)
	{
		gTask.flag_1000ms = False;
		GAS_Scheduler_taskCounter_1000ms();
	}

	GAS_Scheduler_taskBackground();

//	GAS_Can_recieveMessage(&hcan);
//	HAL_CAN_IRQHandler(&hcan);
//	  pin_state=HAL_GPIO_ReadPin(GPIO_PIN_8);
}
