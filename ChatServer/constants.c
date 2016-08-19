#include "constants.h"

const char motd[] = "Welcome to C Chat Server!\r\nPlease enter your name: ";
const int motdLen = sizeof(motd);

const char errorNoName[] = "Don't be shy! Tell us your name.";
const int errorNoNameLen = sizeof(errorNoName);

const char errorNameTooLong[] = "Your name is too long; please choose a shorter name.\r\n";
const int errorNameTooLongLen = sizeof(errorNameTooLong);

const char welcomeNameBefore[] = "Welcome, ";
const int welcomeNameBeforeLen = sizeof(welcomeNameBefore);

const char welcomeNameAfter[] = "! ";
const int welcomeNameAfterLen = sizeof(welcomeNameAfter);

const char instructions[] = "These are some instructions to get you started.\r\n";
const int instructionsLen = sizeof(instructions);

const char newLine[] = "\r\n";
const int newLineLen = sizeof(newLine);

const char endPrompt[] = ">";
const int endPromptLen = sizeof(endPrompt);

const char createCommand[] = "create";
const int createCommandLen = sizeof(createCommand);