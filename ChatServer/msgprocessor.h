#pragma once
#define INVALID_CLIENT -1
#define INVALID_MESSAGE -2
#define MESSAGE_PROCESSED_SUCCESSFULLY 0

#include "commands.h"
#include "server.h"
#include "msgWriter.h"

int msgpProcessClient(Client *client);
void processCommand(Client *client);
void processMessage(Client *client);
void processAwaitingName(Client *client);
void processInitClient(Client *client);
void appendPromptSig(Client *client);
void setBuffer(char *buffer, int *bufferLength, const char *src, int len);
void triggerConvertEolToString(ClientConnection *clientConnection);