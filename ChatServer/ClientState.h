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
	EVENT_BEFORE_RECEIVE,
	EVENT_AFTER_RECEIVE,
	EVENT_BEFORE_SEND,
	EVENT_AFTER_SEND,
	EVENT_COUNT
} EventType;

typedef void state_func(Client *client);

