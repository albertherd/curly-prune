#include "msgWriter.h"

void msgWriterWriteMsg(Client *client, char *msg)
{
	if (client->sendBufferLength)
	{
		strcat_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, msg);
	}
	else
	{
		strcpy_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, msg);
	}

	client->sendBufferLength = strlen(client->sendBuffer) + 1;
}

/*
strcpy_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, welcomeNameBefore);
strcat_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, client->recvBuffer);
strcat_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, welcomeNameAfter);
strcat_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, instructions);
client->sendBufferLength = strlen(client->sendBuffer) + 1;
client->state = CLIENT_COMMAND_MODE;*/