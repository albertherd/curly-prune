#include "fsm.h"
#include "constants.h"
#include "awaitingNameState.h"
#include "msgWriter.h"
#include "stringhelper.h"

StateResult awaitingNameOnBeforeRead(Client *client, ClientState *clientState)
{
	convertEolToString(&client->recvBuffer, &client->recvBufferLength);
}

StateResult awaitingNameMainEvent(Client *client, ClientState *clientState)
{
	if (client->recvBufferLength > CLIENT_NAME_SIZE)
	{
		msgWriterWriteMsg(client, errorNameTooLong);
	}
	else if (!strlen(client->recvBuffer))
	{
		msgWriterWriteMsg(client, errorNoName);
	}
	else
	{
		strcpy_s(client->name, CLIENT_NAME_SIZE, client->recvBuffer);
		msgWriterWriteMsg(client, welcomeNameBefore);
		msgWriterWriteMsg(client, client->recvBuffer);
		msgWriterWriteMsg(client, welcomeNameAfter);
		msgWriterWriteMsg(client, instructions);
		*clientState = STATE_COMMAND_MODE;
	}

	return STATERESULT_OK;
}