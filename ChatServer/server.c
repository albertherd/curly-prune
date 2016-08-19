#include <errno.h>
#include "server.h"
#include "list.h"
#include "Ws2tcpip.h"
#include "msgprocessor.h"
#include "Client.h"
#include "clientConnection.h"

SOCKET listenerSocket;
list *clients;
char clientAddress[INET_ADDRSTRLEN];

int initServer()
{
	if (startWinSock() == INVALID_SOCKET)
	{
		return 1;
	}

	if (setupListenerSocket() == INVALID_SOCKET)
	{
		return 1;
	}

	if (!cmdsInit())
	{
		return 1;
	}

	listenForConnections();
	cleanupSession();
	return 0;
}

int startWinSock()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("Error init winsock with code %d.\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	return 0;
}

int setupListenerSocket()
{
	SOCKADDR_IN socketAddr;
	setsocketAddr(&socketAddr);

	if ((listenerSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	if (bind(listenerSocket, (SOCKADDR *)&socketAddr, sizeof(socketAddr)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	puts("Server initialized..waiting for connection");
	listen(listenerSocket, MAX_CLIENTS);
	return 0;
}

void setsocketAddr(SOCKADDR_IN *server)
{
	memset(server, 0, sizeof(*server));
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons(LISTEN_PORT);
}

int listenForConnections()
{
	clients = listCreate();
	while (1)
	{
		FD_SET readSet;
		FD_SET writeSet;
		FD_SET exceptSet;

		if (setUpFDSets(&readSet, &writeSet, &exceptSet, listenerSocket) == INVALID_SOCKET)
		{
			return ;
		}

		if (select(0, &readSet, &writeSet, &exceptSet, 0) > 0)
		{
			if (FD_ISSET(listenerSocket, &readSet))
			{
				printf("Accepting Socket!\n");
				acceptConnection();
			}
			else if (FD_ISSET(listenerSocket, &exceptSet))
			{
				printf("Error in Socket!\n");
				handleSocketErr(listenerSocket);
			}
			else
			{
				processSockets(&readSet, &writeSet, &exceptSet);
			}

		}
	}
	return 0;
}

int setUpFDSets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet, SOCKET listenerSocket)
{
	if (listenerSocket == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}

	FD_ZERO(readSet);
	FD_ZERO(writeSet);
	FD_ZERO(exceptSet);

	FD_SET(listenerSocket, readSet);
	FD_SET(listenerSocket, writeSet);
	FD_SET(listenerSocket, exceptSet);

	listIter *iter = listGetIterator(clients, AL_START_HEAD);
	listNode *node;
	ClientConnection *clientConnection;
	while ((node = listNext(iter)) != NULL)
	{
		clientConnection = node->value;
		if (clientConnection->client.recvBufferLength < CLIENTCONNECTION_BUFFER_SIZE)
		{
			FD_SET(clientConnection->socket, readSet);
		}

		if (clientConnection->client.sendBufferLength > 0)
		{
			FD_SET(clientConnection->socket, writeSet);
		}

		FD_SET(clientConnection->socket, exceptSet);
	}
	listReleaseIterator(iter);

	return 0;
}

int acceptConnection()
{
	SOCKADDR_IN incomingSockAddr;
	int incomingSockAddrSize = sizeof(incomingSockAddr);

	SOCKET incomingSocket = accept(listenerSocket, (SOCKADDR *)&incomingSockAddr, &incomingSockAddrSize);
	if (incomingSocket != INVALID_SOCKET)
	{
		printf("New connection from %s:%d \n", inet_ntop(AF_INET, &incomingSockAddr.sin_addr, clientAddress, INET_ADDRSTRLEN), ntohs(incomingSockAddr.sin_port));

		u_long nonBlockFlag = 1;
		ioctlsocket(incomingSocket, FIONBIO, &nonBlockFlag);
		ClientConnection *clientConnection = initClientConnection(incomingSocket);
		listAddNodeHead(clients, clientConnection);
	}
	else
	{
		return WSAGetLastError();
	}
}


int processSockets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet)
{
	listIter *iter = listGetIterator(clients, AL_START_HEAD);
	listNode *node;

	while ((node = listNext(iter)) != NULL)
	{
		int result = 0;
		ClientConnection *clientConnection = node->value;
		SOCKET clientSocket = clientConnection->socket;
		if (FD_ISSET(clientSocket, exceptSet))
		{
			printf("Error in socket");
			FD_CLR(clientSocket, exceptSet);
			result = SERVER_CONNECTION_ERR;
		}
		else if (FD_ISSET(clientSocket, readSet))
		{
			printf("Reading From Socket!\n");
			result = readFromClient(clientConnection);
			FD_CLR(clientSocket, readSet);
		}
		else if (FD_ISSET(clientSocket, writeSet))
		{
			printf("Writing To Socket!\n");
			result = writeToClient(clientConnection);
			FD_CLR(clientSocket, writeSet);
		}

		if (result == SERVER_CONNECTION_CLOSED)
		{
			cleanupSocket(node);
		}
		else if (result == SERVER_CONNECTION_ERR)
		{
			handleSocketErr(clientSocket);
			cleanupSocket(node);
		}
	}

	listReleaseIterator(iter);
}

int readFromClient(ClientConnection *clientConnection)
{
	int receivedBytes = recv(clientConnection->socket, clientConnection->client.recvBuffer + clientConnection->client.recvBufferLength, CLIENTCONNECTION_BUFFER_SIZE - clientConnection->client.recvBufferLength, 0);
	clientConnection->client.recvBufferLength += receivedBytes;

	if (receivedBytes == 0)
	{
		return SERVER_CONNECTION_CLOSED;
	}
	else if (receivedBytes == SOCKET_ERROR)
	{
		return handleSocketErr(clientConnection->socket) == WSAEWOULDBLOCK ? SERVER_CONNECTION_OK : SERVER_CONNECTION_ERR;
	}

	fsmProcessBeforeReadEvent(&clientConnection->client, &clientConnection->state);
	if (fsmProcessMainEvent(&clientConnection->client, &clientConnection->state) == STATERESULT_OK)
	{
		clientConnection->client.recvBufferLength = 0;
		memset(clientConnection->client.recvBuffer, 0, CLIENTCONNECTION_BUFFER_SIZE);
	}
	fsmProcessAfterReadEvent(&clientConnection->client, &clientConnection->state);
	return SERVER_CONNECTION_OK;
}

int writeToClient(ClientConnection *clientConnection)
{
	fsmProcessBeforeSendEvent(&clientConnection->client, &clientConnection->state);
	int writtenBytes = send(clientConnection->socket, clientConnection->client.sendBuffer, clientConnection->client.sendBufferLength, 0);
	if (writtenBytes == SOCKET_ERROR)
	{
		return handleSocketErr(clientConnection->socket) == WSAEWOULDBLOCK ? SERVER_CONNECTION_OK : SERVER_CONNECTION_ERR;
	}
	fsmProcessAfterSendEvent(&clientConnection->client, &clientConnection->state);

	if (writtenBytes == clientConnection->client.sendBufferLength)
	{
		clientConnection->client.sendBufferLength = 0;
		memset(clientConnection->client.sendBuffer, 0, CLIENTCONNECTION_BUFFER_SIZE);
	}
	else
	{
		clientConnection->client.sendBufferLength -= writtenBytes;
		memmove(clientConnection->client.sendBuffer, clientConnection->client.sendBuffer + writtenBytes, clientConnection->client.sendBufferLength);
	}

	return SERVER_CONNECTION_OK;
}

int handleSocketErr(SOCKET socket)
{
	int err;
	int errLen = sizeof(err);
	getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&err, &errLen);
	return err;
}

void cleanupSocket(listNode *node)
{
	free(node->value);
	listDelNode(clients, node);
}


void cleanupSession()
{
	closesocket(listenerSocket);
	WSACleanup();
}
