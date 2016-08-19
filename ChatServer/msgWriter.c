#include "msgWriter.h"

void msgWriterWriteMsg(Client *client, char *msg)
{
	if (client->sendBufferLength)
	{
		strcat_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE - client->sendBufferLength, msg);
	}
	else
	{
		strcpy_s(client->sendBuffer, CLIENTCONNECTION_BUFFER_SIZE, msg);
	}

	client->sendBufferLength = strlen(client->sendBuffer) + 1;
}
