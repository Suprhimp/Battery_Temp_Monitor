/*
 * CAN.h
 *
 *  Created on: 2020. 10. 27.
 *      Author: Suprhimp
 */

#ifndef SRC_GETANDSEND_H_
#define SRC_GETANDSEND_H_

#include "stm32f4xx_hal_can.h"
#include "can.h"


typedef union{
	uint8_t TxData[8];
	uint8_t RxData[8];
	struct{
		unsigned int sensor0 : 12;
		unsigned int sensor1 : 12;
		unsigned int sensor2 : 12;
		unsigned int sensor3 : 12;
		unsigned int sensor4 : 12;
		unsigned int reserved: 4;

	}__attribute__((aligned(1),packed)) B;

}stm32_msg_t;

typedef union
{
	uint8_t TxData[8];
	    struct{
			unsigned int AMK_bReserve : 8;
			unsigned int AMK_bSystemReady : 1;
			unsigned int AMK_bSError : 1;
			unsigned int AMK_bWarn : 1;
			unsigned int AMK_bQuitDcOn : 1;
			unsigned int AMK_bDcOn : 1;
			unsigned int AMK_bQuitInverterOn : 1;
			unsigned int AMK_bInverterOn : 1;
			unsigned int AMK_bDerating : 1;
	        int AMK_ActualVelocity : 16;
	        int AMK_TorqueCurrent : 16;
	        int AMK_MagnetizingCurrent : 16;
	    }S;
}amkActualValues1;

typedef union
{
	uint8_t RxData[8];
	    struct{
			unsigned int AMK_bReserve1 : 8;
			unsigned int AMK_bInverterOn : 1;
			unsigned int AMK_bDcOn : 1;
			unsigned int AMK_bEnable : 1;
			unsigned int AMK_bErrorReset : 1;
			unsigned int AMK_bReserve2 : 4;
	        int AMK_TargetVelocity : 16;
	        int AMK_TorqueLimitPositv : 16;
	        int AMK_TorqueLimitNegativ : 16;
	    }S;
}amkSetpoint1;

extern amkActualValues1 AMK_Actual_Values1;
extern amkSetpoint1 AMK_Setpoint1;
extern stm32_msg_t stm32_1;

extern void GAS_Can_init(void);

extern void GAS_Can_sendMessage(CAN_HandleTypeDef hcan,CAN_TxHeaderTypeDef canHeader, uint8_t Data[]);

extern void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan);
//extern void GAS_Can_recieveMessage(CAN_HandleTypeDef *hcan);
#endif /* SRC_GETANDSEND_H_ */
