/*
 * uart_input.c
 *
 *  Created on: Jul 24, 2026
 *      Author: Dora_
 *
 * */
#include "uart_input.h"
#include <stdint.h>


/* Macro -------------------------------------------------------------*/
#define UART_INPUT_MAX_TEXT_LENGTH 15U

/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef *uartHandle = NULL; //jer svaka  HAL funkcija ocekuje pokazivac bas a ne kopiju
static char inputBuffer[UART_INPUT_MAX_TEXT_LENGTH + 1U];
static uint8_t inputIndex = 0U;

//static uint8_t newLine[] = "\r\n";
//static uint8_t backspaceSequence[] = "\b \b";

/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef UART_InputReceiveCharacter(uint8_t *receivedCharacter);
static uint8_t UART_InputProcessCharcter(uint8_t receivedCharacter);

void UART_InputInit(UART_HandleTypeDef *huart)
{
	uartHandle = huart;
	UART_InputClear();
}

void UART_InputClear(void)
{
	inputIndex = 0U;
	inputBuffer[0] = '\0';
}

uint8_t UART_InputProcess(void)
{
	uint8_t receivedCharacter;

	HAL_StatusTypeDef receiveStatus = UART_InputReceiveCharacter(&receivedCharacter);

	if(receiveStatus != HAL_OK)
	{
		return 0U;
	}

	return UART_InputProcessCharcter(receivedCharacter);
}
static HAL_StatusTypeDef UART_InputReceiveCharacter(uint8_t *receivedCharacter)
{
	if((uartHandle == NULL) || (receivedCharacter == NULL))
	{
		return HAL_ERROR;
	}

	return HAL_UART_Receive(uartHandle, receivedCharacter, 1U,1U);
}

static uint8_t UART_InputProcessCharcter(uint8_t receivedCharacter)
{
	//AKO JE ENTER - ZAVRSI TEKST I VRATI 1
	if(receivedCharacter == '\r' || receivedCharacter == '\n')
	{
		if (inputIndex == 0U)
		{
		   return 0U;
		}

		inputBuffer[inputIndex] = '\0';

		//HAL_UART_Transmit(uartHandle, newLine, sizeof(newLine)-1U, HAL_MAX_DELAY);

		return 1U;
	}
	//AKO JE BACKSPACE - IZBRISI POSLJEDNJUI ZNAK I VRATI 0
	if(receivedCharacter == 8U || receivedCharacter == 127U)
	{
		if(inputIndex > 0U)
		{
			inputIndex--;
			inputBuffer[inputIndex] = '\0';
			//HAL_UART_Transmit(uartHandle, backspaceSequence, sizeof(backspaceSequence)-1U, HAL_MAX_DELAY);
		}

		return 0U;
	}
	// AKO JE OBICAN VIDLJIV  ZNAK - UPISI GA U BUFFER I PRIKAZI U PUTTIJU
	if((receivedCharacter >= 32U) && (receivedCharacter <= 126U) && (inputIndex < UART_INPUT_MAX_TEXT_LENGTH ))
	{
		inputBuffer[inputIndex] = (char)receivedCharacter;
		inputIndex++;
		inputBuffer[inputIndex] = '\0';

		//HAL_UART_Transmit(uartHandle, &receivedCharacter, 1U, HAL_MAX_DELAY);
	}
	// 0 - NASTAVAK UPISIVANJE, 1 - KORISNIK PRITISNUO ENTER


	return 0U;

}

const char * UART_InputGetText(void)
{
	return inputBuffer;
}
