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
	int restaurantSelect;
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
				printf("Please choose a restaurant to view: ");
				scanf_s("%d", &restaurantSelect);
				displayRestaurant(searchNum(restaurantList, restaurantSelect));

			}
			case 2://Random restaurant
			{

			}
			case 3://Display all restaurants
			{
				displayAllRestaurants(restaurantList);
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
