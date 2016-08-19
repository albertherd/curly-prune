#include "Client.h"
#include "clientConnection.h"

ClientConnection *initClientConnection(SOCKET incomingSocket)
{
	ClientConnection *clientConnection = malloc(sizeof(ClientConnection));
	memset(clientConnection, 0, sizeof(ClientConnection));
	clientConnection->socket = incomingSocket;
	clientConnection->state = STATE_INIT;
	return clientConnection;
}

void releaseClientConnection(ClientConnection *clientConnection)
{
	free(clientConnection);
}