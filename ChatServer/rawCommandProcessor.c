#include "rawCommandProcessor.h"
#include "stringhelper.h"
#include "room.h"
#include <string.h>

static Command commandList[16];

int cmdsInit()
{
	Command exitCommand = { "EXIT" , cmdsExitFunc };
	commandList[0] = exitCommand;

	Command roomCommand = { "ROOM", cmdsRoomMain };
	commandList[1] = roomCommand;

	return 1;
}

CommandFunc *getCmdFuncByName(char *cmdName)
{
	cmdName = upperString(cmdName);

	for (int i = 0; i < sizeof(commandList) / sizeof(Command); i++){
		if (strcmp(cmdName, commandList[i].cmdName) == 0){
			return commandList[i].cmdFunc;
		}
	}

	return NULL;
}

void cmdsExitFunc(char **params)
{
	printf("exit invoked!");
}

