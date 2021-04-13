
/*This .c file contains all the definitions for the functions declared in main.h*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

#define MAX_CHAR 100

int mainMenuInput(void)
{
	char userInput[MAX_CHAR] = { '\0' };

	printf("Which action do you wish to take:");
	scanf_s("%s", &userInput, MAX_CHAR);
	char selection = userInput[0];
	while (selection != '1' || selection != '2' || selection != '3' || selection != '0')
	{
		switch (selection)
		{
		case'1':
			return 1;

		case'2':
			return 2;

		case'3':
			return 3;

		case'0':
			return 0;

		}
		if (selection != '1' || selection != '2' || selection != '3' || selection != '4')
		{
			printf("Please select one of the options provided: ");
			scanf_s("%s", &userInput, MAX_CHAR);
			selection = userInput[0];
		}
	}
}

int randomSearch(void)
{
	int length_of_list = RESTAURANT_LIST_SIZE;
	int randomNumber = 1;

	randomNumber = (rand() % length_of_list) + 1;


return randomNumber;
}


