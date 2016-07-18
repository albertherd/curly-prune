#pragma once
#include "server.h"

void clientEventsAfterAccept(ClientConnection *connection);

void clientEventsBeforeRead(ClientConnection *connection);

void clientEventsAfterRead(ClientConnection *connection);

void clientEventsBeforeSend(ClientConnection *connection);

void clientEventsAfterSend(ClientConnection *connection);