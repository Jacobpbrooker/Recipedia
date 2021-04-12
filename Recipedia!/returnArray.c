#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "returnArrays.h"


char* nullTerminate(char* string)
{
	char* returnString = (char*)malloc(sizeof(char) * strlen(string));
	
	if (!returnString)
		exit(EXIT_FAILURE);

	memset(returnString, '\0', sizeof(char) * strlen(returnString));
	int sizeOfString = sizeof(char) * strlen(string);
	
	sizeOfString++;
	strcpy_s(returnString, sizeOfString, string);
	
	int stringLength = strlen(returnString) + 1;

	for (int i = 0; i < stringLength; i++)
			if (returnString[i] == '\n')
				returnString[i] = '\0';

	return returnString;
}

char* newLineTerminate(char* string)
{
	char* returnString = (char*)malloc(sizeof(char) * strlen(string));

	if (!returnString)
		exit(EXIT_FAILURE);
	
	memset(returnString, '\0', sizeof(char)*strlen(returnString));

	int sizeOfString = sizeof(char) * strlen(string);
	
	sizeOfString++;
	
	strcpy_s(returnString, sizeOfString, string);

	int stringLength = strlen(returnString) + 1;

	for (int i = 0; i < stringLength; i++)
		if (returnString[i] == '\0')
			returnString[i] = '\n';

	return returnString;
}
