#include "list.h"
#include "Ws2tcpip.h"

#define LISTEN_PORT 23
#define MAX_CLIENTS 24

#define SERVER_CONNECTION_OK 0
#define SERVER_CONNECTION_ERR SOCKET_ERROR
#define SERVER_CONNECTION_CLOSED 1

#define CLIENTCONNECTION_BUFFER_SIZE 10240
#define CLIENT_NAME_SIZE 256
#define CLIENTCONNECTION_WRITE_ADDITIONAL_PADDING 24

typedef enum ClientState{
	CLIENT_INIT,
	CLIENT_AWAITING_NAME,
	CLIENT_COMMAND_MODE,
	CLIENT_IDLE,
	CLIENT_READABLE,
	CLIENT_WRTIEABLE
} ClientState;

typedef struct Client{
	short recvBufferLength;
	short sendBufferLength;
	ClientState state;
	char name[CLIENT_NAME_SIZE];
	char recvBuffer[CLIENTCONNECTION_BUFFER_SIZE];
	char sendBuffer[CLIENTCONNECTION_BUFFER_SIZE];
} Client;

typedef struct ClientEvents{
	Event beforeAccept;
	Event afterAccept;
	Event beforeSend;
	Event afterSend;
	Event beforeRead;
	Event afteRead;
} ClientEvents;

typedef struct Event{
	void(*eventFunc)(ClientConnection *clientConnection);
} Event;

typedef struct ClientConnection {
	SOCKET socket;
	Client client;
	ClientEvents clientEvents;
} ClientConnection;


int initServer();
int startWinSock();
int setupListenerSocket();
void setsocketAddr(SOCKADDR_IN *server);
int listenForConnections();
int setUpFDSets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet, SOCKET listenerSocket);
int acceptConnection();
ClientConnection *initClientConnection(SOCKET incomingSocket);
void releseClientConnection(ClientConnection *clientConnection);
int processSockets(FD_SET *readSet, FD_SET *writeSet, FD_SET *exceptSet);
int readFromClient(listNode *node);
int writeToClient(ClientConnection *clientConnection);
int handleSocketErr(SOCKET socket);
void cleanupSocket(listNode *node);
void cleanupSession();