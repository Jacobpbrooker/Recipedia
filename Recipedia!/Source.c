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

#define MAXUSERNAME 50

int main(int argc, char* argv[])
{
	
	srand(time(NULL));
	PRESTAURANTNODE	restaurantList = loadRestaurants(RECIPEDIADIRECTORY);
	//saveFile(restaurantList, RECIPEDIADIRECTORY);
	//freeRestaurantList(restaurantList);
	//if (!saveFile(restaurantList, RECIPEDIADIRECTORY))
	//	exit(EXIT_FAILURE);

	//exit(EXIT_SUCCESS);
	
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
			displayMainMenu();

			switch (mainMenuInput())
			{
			case 1://search for restaurant
			{
				displayAllRestaurants(restaurantList);
				char* restaurantSelect = (char*)malloc(sizeof(char)*100);
				if (!restaurantSelect)
					exit(EXIT_FAILURE);

				memset(restaurantSelect, '\0', 100);

				printf("Please enter a restaurant name: ");
				//fgets(restaurantSelect, 100, stdin);
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
						break;
					}
				}
				else
				{
					printf("Sorry nothing was found on your input\n");
				}

				break;
			}
			case 2://Random restaurant
			{
				displayRestaurant(searchNum(restaurantList, randomSearch()));

				break;
			}
			case 3://Display all restaurants
			{
				displayAllRestaurants(restaurantList);
				break;
			}
			case 4://exit
			{
				printf("Exiting...\n");
				keepGoing = false;
				break;
			}
			}

		} while (keepGoing);
		printf("Thank you for using Recipedia =)\n");


	}
	
	//loadOrCreate(RECIPEDIALOADFILE);
	//PRESTAURANTNODE	restaurantList = loadOrCreate(RECIPEDIALOADFILE);

	//saveFile(restaurantList);

	
	
	exit(EXIT_SUCCESS);
}
