#include <stdlib.h>
#include <stdio.h>
#include "msgprocessor.h"
#include "stringhelper.h"
#include "strings.h"

int msgpProcessClient(Client *client)
{
	if (client == NULL)
	{
		return INVALID_CLIENT;
	}

	switch (client->state)
	{
		case CLIENT_INIT:
		{
			processInitClient(client);
			break;
		}
		case CLIENT_AWAITING_NAME:
		{
			processAwaitingName(client);
			break;
		}
		case CLIENT_COMMAND_MODE:
		{
			processCommand(client);
			break;
		}
		case CLIENT_READABLE:
		{
			processMessage(client);
			break;
		}
	}

	return MESSAGE_PROCESSED_SUCCESSFULLY;
}

void processInitClient(Client *client)
{
	strcpy_s(client->sendBuffer, sizeof(motd), motd);
	client->sendBufferLength = sizeof(motd);
	client->state = CLIENT_AWAITING_NAME;

	client->clientEvents.onClientEventsSocketRecv.eventFunc = triggerConvertEolToString;
}

void processAwaitingName(Client *client)
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
		msgWriterWriteMsg(client, welcomeNameBefore);
		msgWriterWriteMsg(client, client->recvBuffer);
		msgWriterWriteMsg(client, welcomeNameAfter);
		msgWriterWriteMsg(client, instructions);
		client->state = CLIENT_COMMAND_MODE;
	}
}

void processCommand(Client *client)
{
	char *upperedCommand = malloc(client->recvBufferLength + 1);
	upperString(upperedCommand, client->recvBuffer, client->recvBufferLength);
	Command *commands = cmdsGetCommands();
	int elems = sizeof(*commands) / sizeof(commands[0]);
	for (int i = 0; i < elems; i++)
	{
		if (strcmp(commands->cmdName, upperedCommand) == 0)
		{
			printf("Command Found!");
			commands->cmdFunc("param!");
		}
	}

	free(upperedCommand);
}

void processMessage(Client *client)
{

}

void setBuffer(char *buffer, short *bufferLength, const char *src, int len)
{
	strcpy_s(buffer, len, src);
	*bufferLength = len;
}

void triggerConvertEolToString(ClientConnection *clientConnection)
{
	convertEolToString(&clientConnection->client.recvBuffer, &clientConnection->client.recvBufferLength);
}

void appendPromptSig(Client *client)
{
	int nameLen = strlen(client->name);
	if (nameLen)
	{
		char *promptSig = malloc(nameLen + CLIENTCONNECTION_WRITE_ADDITIONAL_PADDING);
		memcpy(promptSig, client->name, nameLen);
		strcat_s(promptSig, 1, ">");

		strcat_s(client->sendBuffer, client->sendBufferLength, promptSig);
		client->sendBufferLength += nameLen + CLIENTCONNECTION_WRITE_ADDITIONAL_PADDING;

		free(promptSig);
	}
}
