/*
Recipedia
By: Jakob, Mason, Torin, Raven
Date: 

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char* argv[])
{
	bool keepGoing = true;
	int userInput;
	do {
		//displayMainMenu()
		scanf_s("%d", &userInput);
		switch (userInput)
		{
		case 1://search for restaurant
		{

		}
		case 2://search for recipe
		{

		}
		case 3://random search
		{

		}
		case 4://exit
		{
			printf("Exiting...");
			keepGoing = false;
			break;
		}
		default:
		{
			printf("Sorry that was not one of the choices please choose again:\n");
		}
		}

	} while (keepGoing);
	clrscr();
	printf("Thank you for using Recipedia =)\n");
}