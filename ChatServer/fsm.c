#include "fsm.h"
#include "Client.h"
#include "initState.h"
#include "sharedStates.h"
#include "awaitingNameState.h"
#include "commandModeState.h"
#include "onAfterRead.h"
#include <stdlib.h>

static const stateFunc *fsm[STATE_COUNT][EVENT_COUNT] = {
	{ initStateMainEvent, NULL, NULL, NULL, NULL }, //STATE_INIT
	{ awaitingNameMainEvent, awaitingNameOnBeforeRead, onAfterRead, NULL, NULL }, //STATE_AWAITING_NAME
	{ commandModeMainEvent, commandModeOnBeforeRead, onAfterRead, NULL, NULL }, //STATE_COMMAND_MODE
	{ NULL, NULL, NULL, NULL, NULL }, //STATE_IDLE
	{ NULL, NULL, NULL, NULL, NULL }, //STATE_READABLE
	{ NULL, NULL, NULL, NULL, NULL }, //STATE_WRITEABLE
	//EVENT_MAIN	 //EVENT_BEFORE_READ  //EVENT_AFTER_READ //EVENT_BEFORE_SEND //EVENT_AFTER_SEND
};

StateResult fsmProcessBeforeReadEvent(Client *client, ClientState *state)
{
	return fsmProcessEvent(fsm[*state][EVENT_BEFORE_READ], client, state);
}

StateResult fsmProcessMainEvent(Client *client, ClientState *state)
{
	return fsmProcessEvent(fsm[*state][EVENT_MAIN], client, state);
}

StateResult fsmProcessAfterReadEvent(Client *client, ClientState *state)
{
	return fsmProcessEvent(fsm[*state][EVENT_AFTER_READ], client, state);
}

StateResult fsmProcessBeforeSendEvent(Client *client, ClientState *state)
{
	return fsmProcessEvent(fsm[*state][EVENT_BEFORE_SEND], client, state);
}

StateResult fsmProcessAfterSendEvent(Client *client, ClientState *state)
{
	return fsmProcessEvent(fsm[*state][EVENT_AFTER_SEND], client, state);
}

StateResult fsmProcessEvent(stateFunc *func, Client *client, ClientState *state)
{
	if (func != NULL){
		return func(client, state);
	}
	return STATERESULT_UNIMPLEMENTED;
}




