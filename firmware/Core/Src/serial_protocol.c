/*
 * serial_protocol.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Dora_
 */
#include "serial_protocol.h"


/* Macro -------------------------------------------------------------*/




/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef *protocolUartHandler = NULL;
static uint8_t okResponse[] = "OK\r\n";


/* Private function prototypes -----------------------------------------------*/



void SerialProtocol_Init(UART_HandleTypeDef *huart)
{
	protocolUartHandler = huart;

}
void SerialProtocol_SendOK(void)
{
	if(protocolUartHandler == NULL)
		return;

	HAL_UART_Transmit(protocolUartHandler, okResponse, sizeof(okResponse)-1U, HAL_MAX_DELAY);
}
