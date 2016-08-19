#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "stringhelper.h"

char *upperString(char *src)
{
	char *result = src;

	while (*src){
		*src = toupper(*src);
		src++;
	}

	return result;
}


char** splitString(const char *src, char delimiter, int *splits)
{
	if (!src || !splits || delimiter == '\0'){
		return NULL;
	}

	//Start from 1 since we're always going to return an array of at least 1.
	*splits = 1;
	char *worker = src;

	while (*worker != '\0'){
		if (*worker == delimiter){
			*splits++;
		}
		worker++;
	}

	/*if (!splits){
		char **result = malloc(sizeof(char *));
		result[0] = src;
		return result;
	}	*/

	char **stringArr = malloc(*splits * sizeof(char *));
	char **result = stringArr;
	size_t writtenBytes;
	worker = src;

	//pick up all apart from last entry
	while (*worker != '\0'){
		if (*worker == delimiter || *worker == '\0'){
			writtenBytes = getSplitStringPortion(stringArr, src, worker);
			stringArr++;
			src += writtenBytes;
		}
		worker++;	
	}

	//pick up last entry
	getSplitStringPortion(stringArr, src, worker);
	return result;
}

static size_t getSplitStringPortion(char **dst, const char *src, const char *currentPosition)
{
	//Length of portion of token plus null terminator
	size_t take = ((currentPosition - src) * sizeof(char) + 1);
	*dst = malloc(take);
	//Do not pick up the delimiter hence why removing 1 from take
	strncpy_s(*dst, take, src, take - 1);
	return take;
}

static void splitStringFree(char **splitStrings, int length)
{
	for (int i = 0; i < length; i++){
		free(splitStrings[i]);
	}
	free(splitStrings);
}

int convertEolToString(char *str, short *len)
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

int getNewLineType(const char *str, short len)
{
	if (!len){
		return EOL_NONE;
	}

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