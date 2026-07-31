/*
 * display_controller.c
 *
 *  Created on: Jul 24, 2026
 *      Author: Dora_
 */
#include "display_controller.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"


void DisplayController_Init(void)
{
	ssd1306_Init();
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

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0U, 0U);
	ssd1306_WriteString((char *)text, Font_7x10, White);
	ssd1306_UpdateScreen();

}

void DisplayController_Clear(void)
{
	ssd1306_StopScroll();
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
}
void DisplayController_StartScrollLeft(void)
{
	ssd1306_StartScrollLeft();
}

void DisplayController_StartScrollRight(void)
{
	ssd1306_StartScrollRight();
}
