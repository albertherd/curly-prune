#include "fsm.h"
#include "initState.h"
#include "constants.h"

StateResult initStateMainEvent(Client *client, ClientState *state)
{
	strcpy_s(client->sendBuffer, motdLen, motd);
	client->sendBufferLength = motdLen;
	*state = STATE_AWAITING_NAME;
	return STATERESULT_OK;
}