/*
 * display_controller.c
 *
 *  Created on: Jul 24, 2026
 *      Author: Dora_
 */
#include "display_controller.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <string.h>

typedef enum
{
    DISPLAY_MODE_STATIC,
    DISPLAY_MODE_SCROLL,
	DISPLAY_MODE_BLINK
} DisplayMode;

/* Macro -------------------------------------------------------------*/
#define MAX_TEXT_LENGTH       15U
#define BLINK_INTERVAL_MS     500U


/* Private variables ---------------------------------------------------------*/
static DisplayMode currentMode = DISPLAY_MODE_STATIC;

static char currentText[MAX_TEXT_LENGTH + 1U];
static uint8_t isTextVisible = 0U;
static uint32_t lastBlinkTime = 0U;



/* Private function prototypes -----------------------------------------------*/
static void RenderText(uint8_t isVisible);
static void CopyText(const char *text);

void DisplayController_Init(void)
{
	ssd1306_Init();

	currentMode = DISPLAY_MODE_STATIC;
	currentText[0] = '\0';
	isTextVisible = 0U;
	lastBlinkTime = 0U;

	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
}

void DisplayController_ShowText(const char *text)
{
	if(text == NULL)
	{
		return;
	}
	ssd1306_StopScroll();
	currentMode = DISPLAY_MODE_STATIC;

	CopyText(text);

	isTextVisible = 1U;
	RenderText(isTextVisible);

}

void DisplayController_Clear(void)
{
	ssd1306_StopScroll();
	currentMode = DISPLAY_MODE_STATIC;
	currentText[0] = '\0';
	isTextVisible = 0U;

	RenderText(isTextVisible);
}
void DisplayController_StartScrollLeft(void)
{
	DisplayController_StopEffect();
	ssd1306_StartScrollLeft();
	currentMode = DISPLAY_MODE_SCROLL;
}

void DisplayController_StartScrollRight(void)
{
	DisplayController_StopEffect();
	ssd1306_StartScrollRight();
	currentMode = DISPLAY_MODE_SCROLL;
}

void DisplayController_StopEffect(void)
{
	ssd1306_StopScroll();
	currentMode = DISPLAY_MODE_STATIC;
	isTextVisible = 1U;
	RenderText(isTextVisible);

}

void DisplayController_StartBlink(void)
{
    DisplayController_StopEffect();

    if (currentText[0] == '\0')
    {
        return;
    }

    currentMode = DISPLAY_MODE_BLINK;
    isTextVisible = 1U;
    lastBlinkTime = HAL_GetTick();
}

void DisplayController_Process(void)
{
	if (currentMode != DISPLAY_MODE_BLINK)
	{
	     return;
	}

	uint32_t currentTime = HAL_GetTick();

	if ((currentTime - lastBlinkTime) < BLINK_INTERVAL_MS)
	{
	    return;
	}

	lastBlinkTime = currentTime;
	isTextVisible = !isTextVisible;

	RenderText(isTextVisible);

}

static void RenderText(uint8_t isVisible)
{

    ssd1306_Fill(Black);


    if ((isVisible != 0U) && (currentText[0] != '\0'))
    {
        ssd1306_SetCursor(0U, 0U);
        ssd1306_WriteString((char *)currentText, Font_7x10, White);
    }

    ssd1306_UpdateScreen();
}

static void CopyText(const char *text)
{
    strncpy(currentText,text,MAX_TEXT_LENGTH);

    currentText[MAX_TEXT_LENGTH] = '\0';
}

