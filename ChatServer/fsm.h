#pragma once
#include "Client.h"

typedef enum ClientState{
	STATE_INIT,
	STATE_AWAITING_NAME,
	STATE_COMMAND_MODE,
	STATE_IDLE,
	STATE_READABLE,
	STATE_WRTIEABLE,
	STATE_COUNT
} ClientState;

typedef enum EventType{
	EVENT_MAIN,
	EVENT_BEFORE_READ,
	EVENT_AFTER_READ,
	EVENT_BEFORE_SEND,
	EVENT_AFTER_SEND,
	EVENT_COUNT
} EventType;

typedef enum StateResult{
	STATERESULT_OK,
	STATERESULT_UNIMPLEMENTED
} StateResult;

typedef StateResult stateFunc(Client *client, ClientState *state);

StateResult fsmProcessBeforeReadEvent(Client *client, ClientState *state);
StateResult fsmProcessMainEvent(Client *client, ClientState *state);
StateResult fsmProcessAfterReadEvent(Client *client, ClientState *state);
StateResult fsmProcessBeforeSendEvent(Client *client, ClientState *state);
StateResult fsmProcessAfterSendEvent(Client *client, ClientState *state);


