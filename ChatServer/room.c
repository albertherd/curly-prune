#include "room.h"
#include "stringhelper.h"
#include "constants.h"
#include <string.h>

void cmdsRoomMain(char **args)
{
	//Advance cursor -> we're not really interested in the command but the params
	args++;

	*args = upperString(args);
	if (strcmp(args, createCommand)){
		cmdsRoomCreateRoom();
	}
}

void cmdsRoomCreateRoom(char *roomName)

