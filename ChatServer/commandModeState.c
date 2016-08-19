#include "fsm.h"
#include "commandModeState.h"
#include "stringhelper.h"
#include "rawCommandProcessor.h"
#include <string.h>

StateResult commandModeOnBeforeRead(Client *client, ClientState *clientState)
{
	convertEolToString(&client->recvBuffer, &client->recvBufferLength);
}


StateResult commandModeMainEvent(Client *client, ClientState *clientState)
{
	char **rawCommand = splitString(client->recvBuffer, " ");
	if (!rawCommand){
		return STATERESULT_OK;
	}
	
	CommandFunc *func = getCmdFuncByName(rawCommand[0]);
	if (func != NULL)
	{
		func(rawCommand);
	}

	return STATERESULT_OK;
}
