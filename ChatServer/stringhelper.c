#include "stringhelper.h"
#include <string.h>

void upperString(char *dst, const char *src, int len)
{
	int i = 0;
	while (i != len)
	{
		dst[i] = toupper(src[i]);
		i++;
	}

	dst[i] = '\0';
}

int convertEolToString(char *str, int *len)
{
	int eolType = getNewLineType(str, *len);
	if (eolType == EOL_NONE)
	{
		return -1;
	}
	str[*len - eolType] = '\0';
	*len = *len - (eolType - 1);
	return 0;
}

int getNewLineType(const char *str, int len)
{
	if (str[len - 1] == '\n')
	{
		if (str[len - 2] == '\r')
		{
			return EOL_CRLF;
		}
		return EOL_LF;
	}
	return EOL_NONE;
}