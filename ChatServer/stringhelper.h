#pragma once
#include <stddef.h>

#define EOL_NONE 0
#define EOL_LF 1
#define EOL_CRLF 2

char** splitString(const char *src, char delimiter);
char *upperString(char *src);
int convertEolToString(char *str, int *len);
int getNewLineType(char *str, int len);
size_t getSplitStringPortion(char *dst, const char *src, const char *currentPosition);
static void splitStringFree(char **splitStrings, int length);