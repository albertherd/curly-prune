#pragma once
#include "Client.h"
#include "clientConnection.h"
#include "fsm.h"
#include "list.h"

#define LISTEN_PORT 23
#define MAX_CLIENTS 24

#define SERVER_CONNECTION_OK 0
#define SERVER_CONNECTION_ERR SOCKET_ERROR
#define SERVER_CONNECTION_CLOSED 1


int initServer();
int startWinSock();
int setupListenerSocket();
void setsocketAddr(SOCKADDR_IN *server);
int listenForConnections();
int setUpFDSets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet, SOCKET listenerSocket);
int acceptConnection();
int processSockets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet);
int readFromClient(listNode *node);
int writeToClient(ClientConnection *clientConnection);
int handleSocketErr(SOCKET socket);
void cleanupSocket(listNode *node);
void cleanupSession();