#include "list.h"

#define LISTEN_PORT 23
#define MAX_CLIENTS 24
#define CLIENTCONNECTION_BUFFER_SIZE 1024
#define SERVER_CONNECTION_OK 0
#define SERVER_CONNECTION_ERR SOCKET_ERROR
#define SERVER_CONNECTION_CLOSED 1

typedef struct ClientConnection {
	SOCKET client;
	char buffer[CLIENTCONNECTION_BUFFER_SIZE];
	short bufferLength;
} ClientConnection;

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