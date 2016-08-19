#pragma once
#include "fsm.h"
#include <WS2tcpip.h>

typedef struct ClientConnection {
	SOCKET socket;
	Client client;
	ClientState state;
} ClientConnection;

ClientConnection *initClientConnection(SOCKET incomingSocket);
void releaseClientConnection(ClientConnection *clientConnection);
