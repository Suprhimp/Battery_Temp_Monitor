/*
 * GAS_BulkADC.c
 *
 *  Created on: Oct 30, 2021
 *      Author: aswww
 */
#include "GAS_BulkADC.h"


uint16_t MCP3208[8];
uint16_t CellTemp[48];

BatteryTemp_t T_BatteryTemp;

void GAS_BulkADC_run_100ms(uint8_t CScount){
//	for(uint8_t CScount = 1;CScount<7;CScount++){
//
//	HAL_GPIO_WritePin(SPI_AD0_GPIO_Port,SPI_AD0_Pin,CScount&0b001);
//	HAL_GPIO_WritePin(SPI_AD1_GPIO_Port,SPI_AD1_Pin,CScount&0b010);
//	HAL_GPIO_WritePin(SPI_AD2_GPIO_Port,SPI_AD2_Pin,CScount&0b100);
//	HAL_GPIO_WritePin(SPI_AD0_GPIO_Port,SPI_AD0_Pin,1);
//	HAL_GPIO_WritePin(SPI_AD1_GPIO_Port,SPI_AD1_Pin,1);
//	HAL_GPIO_WritePin(SPI_AD2_GPIO_Port,SPI_AD2_Pin,0);
		GAS_Spi_getAll(MCP3208);

		for(uint8_t i =0;i<8;i++){
//			CellTemp[i] = MCP3208[i];
			CellTemp[i+(CScount-1)*8] = MCP3208[i];
		}

//		HAL_GPIO_WritePin(SPI_AD0_GPIO_Port,SPI_AD0_Pin,0);
//		HAL_GPIO_WritePin(SPI_AD1_GPIO_Port,SPI_AD1_Pin,0);
//		HAL_GPIO_WritePin(SPI_AD2_GPIO_Port,SPI_AD2_Pin,0);

}

void GAS_BulkADC_select(uint8_t CScount){
	HAL_GPIO_WritePin(SPI_AD0_GPIO_Port,SPI_AD0_Pin,CScount&0b001);
	HAL_GPIO_WritePin(SPI_AD1_GPIO_Port,SPI_AD1_Pin,CScount&0b010);
	HAL_GPIO_WritePin(SPI_AD2_GPIO_Port,SPI_AD2_Pin,CScount&0b100);

}

void GAS_BulkADC_Calc(){
	uint32_t Total = 0;
	uint16_t Max = 9;
	uint16_t Min = 0xffff;

	for(int i=0;i<48;i++){
		if (CellTemp[i]<100 || CellTemp[i]>4000){
			continue;
		}
		unsigned int parsedTemp = CellTemp[i] ;
		Total += parsedTemp;
		if (parsedTemp > Max){
			Max = parsedTemp;
		}
		if (parsedTemp < Min){
			Min = parsedTemp;
		}
	}

	T_BatteryTemp.B.HighestTemp = Max;
	T_BatteryTemp.B.LowestTemp = Min;
	T_BatteryTemp.B.MeanTemp = (int)(((float)Total)/4.8);
	GAS_Can_sendMessage_2(T_BatteryTemp.TxData);

}
