#include "server.h"

void onClientEventsSocketRecv(ClientConnection *connection)
{
	if (connection->client.clientEvents.onClientEventsSocketRecv.eventFunc){
		connection->client.clientEvents.onClientEventsSocketRecv.eventFunc(connection);
	}
}