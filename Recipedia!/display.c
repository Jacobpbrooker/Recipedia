#include "display.h"
#include <stdio.h>

void displayMainMenu()
{
	printf("Welcome to Recipedia!\n");
	printf("Please select an option:\n");
	printf("1) Search for restaurant\n");
	printf("2) Randomly select a restaurant\n");
	printf("3) Display all restaurants\n");
	printf("4) Exit\n");
}

void ColourdisplayMainMenu()
{
	displayTitle();
	printf("\tWelcome to Recipedia!\n");
	printf("\tPlease select an option:\n");
	printf("\t1) Search for restaurant\n");
	printf("\t2) Randomly select a restaurant\n");
	printf("\t3) Display all restaurants\n");
	printf("\t\x1b[%dm4) Exit\n", BRIGHT_RED_FG);
	printf("\x1b[%dm", DEFAULT_FG);
}

void displayTitle(void) 
{
	printf("\n");
	printf("\x1b[%dm", BRIGHT_BLUE_FG);
	printf("     _______     ________    ______  _____  _______  ________  ______   _____       _				\n");
	printf("    |_   __ \\   |_   __  | .' ___  ||_   _||_   __ \\|_   __  ||_   _ `.|_   _|     / \\				\n");
	printf("      | |__) |    | |_ \\_|/ .'   \\_|  | |    | |__) | | |_ \\_|  | | `. \\ | |      / _ \\			\n");
	printf("      |  __ /     |  _| _ | |         | |    |  ___/  |  _| _   | |  | | | |     / ___ \\			\n");
	printf("     _| |  \\ \\_  _| |__/ |\\ `.___.'\\ _| |_  _| |_    _| |__/ | _| |_.' /_| |_  _/ /   \\ \\_			\n");
	printf("    |____| |___||________| `.____ .'|_____||_____|  |________||______.'|_____||____| |____|		\n");
	printf("\x1b[%dm", DEFAULT_FG);
	printf("\n");
}

void displaySearch()
{
	printf("Please enter a restaurant name: ");
}

void displayRestaurant(PRESTAURANTNODE r)
{
	printf("Name - %s\n", r->restaurant.restaurantName);
	printf("Location - %s\n", r->restaurant.restaurantSypnopsis);
	printf("Executive Chef - %s\n", r->restaurant.headChef);
	printf("Specials - \n");

	for (int i = 0; i < MENUSIZE; i++)
	{
		printf("%s", r->restaurant.specialityMenu[i]);
	}

	printf("Would you like to see the recipes for today's dishes? (Y/N): ");
}

void displayAllRestaurants(PRESTAURANTNODE r)
{
	if (r == NULL)
		return;
	printf("%s\n", r->restaurant.restaurantName);
	displayAllRestaurants(r->nextNode);
}

void displayRecipe(PINSTRUCTIONQUEUE q)
{
	q->tail = q->head;

	while (q->tail != NULL)
	{
		printf("%s\n", q->tail);
		q->tail = q->tail->nextNode;
	}
}