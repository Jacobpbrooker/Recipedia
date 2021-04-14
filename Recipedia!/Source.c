/*
RECIPEDIA
By: Jacob, Mason, Raven, Torin
Apr, 2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
#include "main.h"
#include "returnArrays.h"
#include "display.h"

#define MAXUSERNAME 50

int main(int argc, char* argv[])
{
	srand(time(NULL));
	PRESTAURANTNODE	restaurantList = loadRestaurants(RECIPEDIADIRECTORY);
	
	bool adminAccess = returnAdminConfirmation(argv[1], strlen(argv[1]));

	if (adminAccess)
	{
		// allow them to delete or add
		adminMode(restaurantList);
		exit(EXIT_SUCCESS);
	}
	else
	{
		char userName[MAXUSERNAME];
		strcpy_s(userName, MAXUSERNAME, argv[1]);

		bool keepGoing = true;
		do {
			colourDisplayMainMenu();
			//displayMainMenu();

			switch (mainMenuInput())
			{
			case 1://search for restaurant
			{
				displayAllRestaurants(restaurantList);
				char* restaurantSelect = (char*)malloc(sizeof(char)*100);
				if (!restaurantSelect)
					exit(EXIT_FAILURE);

				memset(restaurantSelect, '\0', 100);

				printf("\x1b[%dm", BRIGHT_GREEN_FG);
				printf("\nPlease enter a restaurant name: ");
				printf("\x1b[%dm", DEFAULT_FG);
				scanf_s("%s", restaurantSelect, 100);

				PRESTAURANTNODE restSearch = searchRestaurant(restaurantList, restaurantSelect);
				if (restSearch == NULL)
				{
					PRESTAURANTNODE recipeSearch = searchRecipe(restaurantList, restaurantSelect);
					if (recipeSearch != NULL)
					{
						displayRestaurant(recipeSearch);
					}
					else
					{
						printf("\x1b[%dm", BRIGHT_RED_FG);
						printf("Sorry nothing was found on your input\n");
						printf("\x1b[%dm", DEFAULT_FG);
						printf("Returning to main menu!\n");
						break;
					}
				}
				else
				{
					displayRestaurant(restSearch);
				}

				break;
			}
			case 2://Random restaurant
			{
				PRESTAURANTNODE randomnode = searchNum(restaurantList, randomSearch());
				displayRestaurant(randomnode);

				break;
			}
			case 3://Display all restaurants
			{
				displayAllRestaurants(restaurantList);
				break;
			}
			case 0://exit
			{
				printf("Exiting...\n");
				keepGoing = false;
				break;
			}
			}

		} while (keepGoing);
		printf("Thank you for using Recipedia =)\n");


	}

	// Do not uncomment
	//saveFile(restaurantList, RECIPEDIADIRECTORY);

	exit(EXIT_SUCCESS);
}
