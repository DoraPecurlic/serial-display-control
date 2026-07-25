/*
 * uart_input.h
 *
 *  Created on: Jul 24, 2026
 *      Author: Dora_
 */

#ifndef INC_UART_INPUT_H_
#define INC_UART_INPUT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

void UART_InputInit(UART_HandleTypeDef *huart);
void UART_InputClear(void);
uint8_t UART_InputProcess(void);

const char * UART_InputGetText(void);

#endif /* INC_UART_INPUT_H_ */
