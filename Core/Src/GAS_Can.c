/*
 * CAN.c
 *
 *  Created on: 2020. 10. 27.
 *      Author: Suprhimp
 */

#include <GAS_Can.h>
#include <stdio.h>

CAN_FilterTypeDef sFilterConfig;
CAN_FilterTypeDef sFilterConfig2;
CAN_RxHeaderTypeDef canRxHeader;
CAN_TxHeaderTypeDef canTxHeader;
CAN_TxHeaderTypeDef canTxHeader2;
uint8_t canRx0Data[8];
uint32_t TxMailBox;
stm32_msg_t stm32_1;
stm32_msg_t stm32_2;
<<<<<<< Updated upstream
stm32_msg_t TC237;
uint32_t STM32_ID = 0x32F103A;
uint32_t STM32_ID2 = 0x32F103B;
=======



uint32_t STM32_TempMonitorID = 0x405DC;
uint32_t BatteryInsideID = 0x405DB;


>>>>>>> Stashed changes
uint32_t TC237_ID = 0x237;

/*-------------------------Function Prototypes--------------------------------*/
void GAS_Can_txSetting(void);
void GAS_Can_rxSetting(void);
void GAS_Can_init(void);
<<<<<<< Updated upstream
void GAS_Can_sendMessage(uint8_t sendData[8]);
=======
void GAS_Can_sendMessage(CAN_HandleTypeDef hcan,CAN_TxHeaderTypeDef canHeader, uint8_t Data[]);
>>>>>>> Stashed changes
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef* hcan);
//void GAS_Can_recieveMessage(CAN_HandleTypeDef *hcan);

void GAS_Can_txSetting(void)
{
<<<<<<< Updated upstream
	/*
	 * CAN tx set function
	 * set ID, IDE, DLC
	 */
	canTxHeader.ExtId = STM32_ID2;
	canTxHeader.IDE	= CAN_ID_EXT;
	canTxHeader.RTR	= CAN_RTR_DATA;
	canTxHeader.DLC	=	8;
=======
>>>>>>> Stashed changes

//	  canTxHeader.StdId = (0x283>>18)&0x7ff;
	  canTxHeader.ExtId = STM32_TempMonitorID;
	  canTxHeader.IDE	= CAN_ID_EXT;
	  canTxHeader.RTR	= CAN_RTR_DATA;
	  canTxHeader.DLC	=	8;

	  canTxHeader2.ExtId = BatteryInsideID;
	  canTxHeader2.IDE	= CAN_ID_EXT;
	  canTxHeader2.RTR	= CAN_RTR_DATA;
	  canTxHeader2.DLC	=	8;

<<<<<<< Updated upstream
void GAS_Can_rxSetting(void)
{
	/*
	 * CAN rx set function
	 * IdHigh, IdLow for each 16bit in 29bit ID
	 * Set different FIFO and FilterBank
	 *
	 */
	sFilterConfig.FilterIdHigh = (STM32_ID<<3)>>16;				/*first 2byte in 29bit (shift need to IED,RTR,0)*/
	sFilterConfig.FilterIdLow = (0xffff & (STM32_ID << 3)) | (1<<2);	/*second 2byte in 29bit + IDE (shift need to IED,RTR,0/)*/
	sFilterConfig.FilterMaskIdHigh = (0x0fffffff<<3)>>16;
	sFilterConfig.FilterMaskIdLow =(0xffff & (0x0FFFFFFF << 3)) | (1<<2);
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	 if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK)
	  {
	    /* Filter configuration Error */
	    Error_Handler();
	  }

	 sFilterConfig2.FilterIdHigh = 0x0000;
	 sFilterConfig2.FilterIdLow = (0xffff & (0x0237 << 3)) | (1<<2);
	 sFilterConfig2.FilterMaskIdHigh = 0x0000;
 	 sFilterConfig2.FilterMaskIdLow = (0xffff & (0x0237 << 3)) | (1<<2);
	 sFilterConfig2.FilterFIFOAssignment = CAN_RX_FIFO1;
	 sFilterConfig2.FilterBank = 1;
	 sFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
	 sFilterConfig2.FilterScale = CAN_FILTERSCALE_32BIT;
	 sFilterConfig2.FilterActivation = ENABLE;
	 sFilterConfig2.SlaveStartFilterBank = 15;

	 if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig2) != HAL_OK)
	 {
	     /* Filter configuration Error */
	     Error_Handler();
	 }
=======
>>>>>>> Stashed changes
}

//void GAS_Can_rxSetting(void){
//
////	sFilterConfig.FilterIdHigh = (Setpoint<<3)>>16;				/*first 2byte in 29bit (shift need to IED,RTR,0)*/
////	sFilterConfig.FilterIdLow = (0xffff & (Setpoint << 3)) | (1<<2);	/*second 2byte in 29bit + IDE (shift need to IED,RTR,0/)*/
//	sFilterConfig.FilterIdHigh = 0;				/*first 2byte in 29bit (shift need to IED,RTR,0)*/
//	sFilterConfig.FilterIdLow = (0xffff & (0x275A << 3));	/*second 2byte in 29bit + IDE (shift need to IED,RTR,0/)*/
//	sFilterConfig.FilterMaskIdHigh = 0;
//	sFilterConfig.FilterMaskIdLow =0;
//	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
//	sFilterConfig.FilterBank = 0;
//	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
//	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
//	sFilterConfig.FilterActivation = ENABLE;
//	sFilterConfig.SlaveStartFilterBank = 14;
//
//	 if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
//	  {
//	    /* Filter configuration Error */
//	    Error_Handler();
//	  }
//
//	 sFilterConfig.FilterIdHigh = (0x275A<<3)>>16;				/*first 2byte in 29bit (shift need to IED,RTR,0)*/
//	 sFilterConfig.FilterIdLow = (0xffff & (0x275A << 3)) | (1<<2);	/*second 2byte in 29bit + IDE (shift need to IED,RTR,0/)*/
//	 sFilterConfig2.FilterMaskIdHigh = 0x0000;
// 	 sFilterConfig2.FilterMaskIdLow = 0;
//	 sFilterConfig2.FilterFIFOAssignment = CAN_RX_FIFO1;
//	 sFilterConfig2.FilterBank = 1;
//	 sFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
//	 sFilterConfig2.FilterScale = CAN_FILTERSCALE_32BIT;
//	 sFilterConfig2.FilterActivation = ENABLE;
//	 sFilterConfig2.SlaveStartFilterBank = 15;
//
//	 if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig2) != HAL_OK)
//	 {
//	     /* Filter configuration Error */
//	     Error_Handler();
//	 }
//}

void GAS_Can_init(void)
{

	GAS_Can_txSetting();
//	GAS_Can_rxSetting();
//
//
//	HAL_CAN_Start(&hcan1);
//
//	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
//	{
//	  Error_Handler();
//	}
//
//	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
//	{
//	  Error_Handler();
//	}


}

void GAS_Can_sendMessage(CAN_HandleTypeDef hcan,CAN_TxHeaderTypeDef canHeader, uint8_t Data[])
{

	TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
	HAL_CAN_AddTxMessage(&hcan, &canHeader, &Data[0], &TxMailBox);

}

<<<<<<< Updated upstream
void GAS_Can_sendMessage(uint8_t sendData[8])
{
	/*
	 * CAN send message function
	 * send Message data with sendData[8]
	 */
	memmove(sendData, stm32_1.TxData, sizeof(uint8_t) * 8);
	TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan2);
	HAL_CAN_AddTxMessage(&hcan2, &canTxHeader, &stm32_1.TxData[0], &TxMailBox);
}
=======


//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
//	if(hcan->Instance == CAN1)
//	{
//		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &canRxHeader, AMK_Setpoint1.RxData);
//
//	}
//}
//
//void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
//	if(hcan->Instance == CAN1)
//	{
//		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &canRxHeader, AMK_Setpoint2.RxData);
//
//	}
//}
>>>>>>> Stashed changes

//void GAS_Can_recieveMessage(CAN_HandleTypeDef *hcan)
//{
//		if(HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO1) != 0)
//	{
//		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &canRxHeader, stm32_2.RxData);
//	}
//
//}
