/*
 * serial_protocol.h
 *
 *  Created on: Jul 28, 2026
 *      Author: Dora_
 */

#ifndef INC_SERIAL_PROTOCOL_H_
#define INC_SERIAL_PROTOCOL_H_

#include "stm32f4xx_hal.h"

typedef enum
{
	SERIAL_PROTOCOL_REQUEST_TEXT,
	SERIAL_PROTOCOL_REQUEST_INVALID = 0,
	SERIAL_PROTOCOL_REQUEST_COMMAND
}SerialProtocolRequestType;


typedef struct
{
	SerialProtocolRequestType type;
	const char *payload;
}SerialProtocolRequest;


void SerialProtocol_Init(UART_HandleTypeDef *huart);
void SerialProtocol_SendOK(void);

SerialProtocolRequest SerialProtocol_ParseRequest(const char *message);
void SerialProtocol_SendInvalidRequest(void);

void SerialProtocol_SendUnknownCommand(void);


#endif /* INC_SERIAL_PROTOCOL_H_ */
