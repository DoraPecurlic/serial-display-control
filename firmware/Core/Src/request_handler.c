/*
 * request_handler.c
 *
 *  Created on: Jul 30, 2026
 *      Author: Dora_
 */

#include "serial_protocol.h"
#include "display_controller.h"

/* Macro -------------------------------------------------------------*/




/* Private variables ---------------------------------------------------------*/




/* Private function prototypes -----------------------------------------------*/


void RequestHandler_Process(const char *message)
{
	SerialProtocolRequest request = SerialProtocol_ParseRequest(message);

	if(request.type == SERIAL_PROTOCOL_REQUEST_TEXT)
	{
		DisplayController_ShowText(request.payload);
		SerialProtocol_SendOK();

		return;
	}

	SerialProtocol_SendInvalidRequest();
}
