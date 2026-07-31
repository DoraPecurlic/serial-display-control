/*
 * display_controller.h
 *
 *  Created on: Jul 24, 2026
 *      Author: Dora_
 */

#ifndef INC_DISPLAY_CONTROLLER_H_
#define INC_DISPLAY_CONTROLLER_H_

void DisplayController_Init(void);
void DisplayController_ShowText(const char *text);

void DisplayController_Clear(void);
void DisplayController_StartScrollLeft(void);
void DisplayController_StartScrollRight(void);

void DisplayController_StopEffect(void);

#endif /* INC_DISPLAY_CONTROLLER_H_ */
