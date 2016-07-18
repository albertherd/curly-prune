#pragma once

#define EOL_NONE 0
#define EOL_LF 1
#define EOL_CRLF 2

void lowerString(char *dst, const char *src, int len); 
int convertEolToString(char *str, int *len);
int getNewLineType(char *str, int len);