#include "commands.h"

Command *commandList[16];

int cmdsInit()
{
	Command *exitCommand = malloc(sizeof(Command));
	setCommand(exitCommand, "EXIT", cmdsExitFunc);
	commandList[0] = exitCommand;

	Command *createCommand = malloc(sizeof(Command));
	setCommand(createCommand, "CREATE", cmdsCreateFunc);
	commandList[1] = createCommand;

	return 1;
}

void setCommand(Command *command, char *commandText, void(*cmdFunc)(char *params))
{
	strcpy_s(command->cmdName, sizeof(command->cmdName), commandText);
	command->cmdFunc = cmdFunc;
}

Command* cmdsGetCommands()
{
	return commandList;
}

void cmdsExitFunc(char *params)
{
	printf("exit invoked!");
}

void cmdsCreateFunc(char *params)
{
	printf("Create invoked!");
}

void cmdsReleseCommands()
{
	//TODO
}
