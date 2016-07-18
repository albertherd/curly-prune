#include "server.h"

void clientEventsAfterAccept(ClientConnection *connection)
{
	if (connection->client.clientEvents.afterAccept.eventFunc){
		connection->client.clientEvents.afterAccept.eventFunc(connection);
	}
}

void clientEventsBeforeRead(ClientConnection *connection)
{
	if (connection->client.clientEvents.beforeRead.eventFunc){
		connection->client.clientEvents.beforeRead.eventFunc(connection);
	}
}

void clientEventsAfterRead(ClientConnection *connection)
{
	if (connection->client.clientEvents.afterRead.eventFunc){
		connection->client.clientEvents.afterRead.eventFunc(connection);
	}
}

void clientEventsBeforeSend(ClientConnection *connection)
{
	if (connection->client.clientEvents.beforeSend.eventFunc){
		connection->client.clientEvents.beforeSend.eventFunc(connection);
	}
}

void clientEventsAfterSend(ClientConnection *connection)
{
	if (connection->client.clientEvents.afterSend.eventFunc){
		connection->client.clientEvents.afterSend.eventFunc(connection);
	}
}