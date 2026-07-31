/*
 * request_handler.c
 *
 *  Created on: Jul 30, 2026
 *      Author: Dora_
 */

#include "serial_protocol.h"
#include "display_controller.h"
#include <string.h>

/* Macro -------------------------------------------------------------*/
#define REQUEST_HANDLER_CLEAR_COMMAND "CLEAR"



/* Private variables ---------------------------------------------------------*/




/* Private function prototypes -----------------------------------------------*/
static void ProcessCommand(const char* command);


void RequestHandler_Process(const char *message)
{
	SerialProtocolRequest request = SerialProtocol_ParseRequest(message);

	if(request.type == SERIAL_PROTOCOL_REQUEST_TEXT)
	{
		DisplayController_ShowText(request.payload);
		SerialProtocol_SendOK();

		return;
	}

	if(request.type == SERIAL_PROTOCOL_REQUEST_COMMAND)
	{
		ProcessCommand(request.payload);

		return;
	}

	SerialProtocol_SendInvalidRequest();
}

static void ProcessCommand(const char* command)
{
	if(command == NULL)
	{
	    SerialProtocol_SendInvalidRequest();
	    return;
	}

	if(strcmp(command, REQUEST_HANDLER_CLEAR_COMMAND) == 0)
	{
		DisplayController_Clear();
		SerialProtocol_SendOK();

		return;
	}

	SerialProtocol_SendUnknownCommand();
}
