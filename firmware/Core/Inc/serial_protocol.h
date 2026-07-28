/*
 * serial_protocol.h
 *
 *  Created on: Jul 28, 2026
 *      Author: Dora_
 */

#ifndef INC_SERIAL_PROTOCOL_H_
#define INC_SERIAL_PROTOCOL_H_

void SerialProtocol_Init(UART_HandleTypeDef *huart);
void SerialProtocol_SendOK(void);


#endif /* INC_SERIAL_PROTOCOL_H_ */
