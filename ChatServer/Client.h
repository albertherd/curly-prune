#pragma once

#define CLIENTCONNECTION_BUFFER_SIZE 10240
#define CLIENT_NAME_SIZE 256
#define CLIENTCONNECTION_WRITE_ADDITIONAL_PADDING 24

typedef struct Client{
	short recvBufferLength;
	short sendBufferLength;
	char name[CLIENT_NAME_SIZE];
	char recvBuffer[CLIENTCONNECTION_BUFFER_SIZE];
	char sendBuffer[CLIENTCONNECTION_BUFFER_SIZE];
} Client;
