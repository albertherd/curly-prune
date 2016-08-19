#include "fsm.h"
#include "onAfterRead.h"
#include "stringhelper.h"
#include "constants.h"
#include "msgWriter.h"
#include <string.h>

StateResult onAfterRead(Client *client, ClientState *clientState)
{
	convertEolToString(&client->recvBuffer, &client->recvBufferLength);
	appendPromptSig(client);
}

void appendPromptSig(Client *client)
{
	int nameLen = strlen(client->name);
	if (nameLen)
	{
		msgWriterWriteMsg(client, client->name);
		msgWriterWriteMsg(client, endPrompt);
	}
}