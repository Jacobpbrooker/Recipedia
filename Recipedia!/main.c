
/*This .c file contains all the definitions for the functions declared in main.h*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"


int mainMenuInput()
{
	char userInput;

	printf("Which action do you wish to take:");
	scanf_s("%ch", &userInput);

	while (userInput != 1 || userInput != 2 || userInput != 3 || userInput != 4)
	{
		switch (userInput)
		{
		case'1':
			return 1;

		case'2':
			return 2;

		case'3':
			return 3;

		case'4':
			return 4;

		}
		if (userInput != 1 || userInput != 2 || userInput != 3 || userInput != 4)
		{
			printf("Please select one of the options provided: ");
			scanf_s("%ch", &userInput);
		}
	
	}

}
/*
int randomSearch()
{
	int length_of_list; //=length of restaurant list
	int randomNumber = 1;

	randomNumber = rand() % length_of_list;


return randomNumber;
}
*/

