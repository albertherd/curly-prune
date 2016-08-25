#pragma once

typedef struct Command {
	char cmdName[16];
	void(*cmdFunc)(char *params);
} Command;

typedef struct CommandParams{
	char *cmdName;
	char *cmdAction;
	char *cmdParams;
} CommandParams;

typedef void CommandFunc(char *params);

int cmdsInit();
CommandFunc *getCmdFuncByName(char *cmdName);
void setCommand(Command command, char *cmdName, CommandFunc cmdFunc);
void cmdsExitFunc(char **params);
void cmdsCreateFunc(char **params);
void cmdsReleseCommands();