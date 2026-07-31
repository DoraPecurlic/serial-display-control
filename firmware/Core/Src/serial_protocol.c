/*
 * serial_protocol.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Dora_
 */
#include "serial_protocol.h"
#include <string.h>


/* Macro -------------------------------------------------------------*/
#define SERIAL_PROTOCOL_TEXT_PREFIX "TEXT:"
#define SERIAL_PROTOCOL_TEXT_PREFIX_LENGTH 5U

#define SERIAL_PROTOCOL_COMMAND_PREFIX "CMD:"
#define SERIAL_PROTOCOL_COMMAND_PREFIX_LENGTH 4U


/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef *protocolUartHandler = NULL;
static uint8_t okResponse[] = "OK\r\n";

static uint8_t invalidRequestResponse[] = "ERROR: INVALID REQUEST\r\n";
static uint8_t unknownCommandResponse[] = "ERROR:UNKNOWN_COMMAND\r\n";



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

SerialProtocolRequest SerialProtocol_ParseRequest(const char *message)
{
	SerialProtocolRequest package;

	package.type = SERIAL_PROTOCOL_REQUEST_INVALID;
	package.payload = NULL;

	if(message == NULL)
	{
		return package;
	}

	if((strncmp(message, SERIAL_PROTOCOL_TEXT_PREFIX, SERIAL_PROTOCOL_TEXT_PREFIX_LENGTH) == 0) && (message[SERIAL_PROTOCOL_TEXT_PREFIX_LENGTH] != '\0'))
	{
		package.type = SERIAL_PROTOCOL_REQUEST_TEXT;
		package.payload = &message[SERIAL_PROTOCOL_TEXT_PREFIX_LENGTH];
	}

	if((strncmp(message, SERIAL_PROTOCOL_COMMAND_PREFIX, SERIAL_PROTOCOL_COMMAND_PREFIX_LENGTH) == 0 )&& (message[SERIAL_PROTOCOL_COMMAND_PREFIX_LENGTH] != '\0'))
	{
		package.type = SERIAL_PROTOCOL_REQUEST_COMMAND;
		package.payload = &message[SERIAL_PROTOCOL_COMMAND_PREFIX_LENGTH];
	}

	return package;
}

void SerialProtocol_SendInvalidRequest(void)
{
	if(protocolUartHandler == NULL)
			return;

	HAL_UART_Transmit(protocolUartHandler, invalidRequestResponse, sizeof(invalidRequestResponse)-1U, HAL_MAX_DELAY);
}

void SerialProtocol_SendUnknownCommand(void)
{
	if(protocolUartHandler == NULL)
				return;

		HAL_UART_Transmit(protocolUartHandler, unknownCommandResponse, sizeof(unknownCommandResponse)-1U, HAL_MAX_DELAY);
}
