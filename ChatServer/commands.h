#pragma once

typedef struct Command {
	char cmdName[16];
	void(*cmdFunc)(char *params);
} Command;

int cmdsInit();
Command* cmdsGetCommands();
void setCommand(Command *command, char *commandText, void(*cmdFunc)(char *params));
void cmdsExitFunc(char *params);
void cmdsCreateFunc(char *params);
void cmdsReleseCommands();