#include <stdio.h>

#include "display.h"

void displayMainMenu()
{
	printf("Welcome to Recipedia!\n");
	printf("Please select an option:\n");
	printf("1) Search for restaurant\n");
	printf("2) Randomly select a restaurant\n");
	printf("3) Display all restaurants\n");
	printf("4) Exit\n");
}

void colourDisplayMainMenu()
{
	displayTitle();
	printf("\tWelcome to Recipedia!\n");
	printf("\tPlease select an option:\n");
	printf("\x1b[%dm", BRIGHT_CYAN_FG);
	printf("\t1) Search for restaurant\n");
	printf("\t2) Randomly select a restaurant\n");
	printf("\t3) Display all restaurants\n");
	printf("\x1b[%dm", BRIGHT_RED_FG);
	printf("\t0) Exit\n");
	printf("\x1b[%dm", DEFAULT_FG);
	printf("\n");
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
	printf("\x1b[%dm", BRIGHT_GREEN_FG);
	printf("\nPlease enter a restaurant name: ");
	printf("\x1b[%dm", DEFAULT_FG);
}

void displayRestaurant(PRESTAURANTNODE r)
{
	printf("\n");
	printf("\x1b[%dm", BRIGHT_MAGENTA_FG);
	printf("%s\n", r->restaurant.restaurantName);
	printf("\x1b[%dm", DEFAULT_FG);
	printf("About - %s\n", r->restaurant.restaurantSypnopsis);
	printf("Executive Chef - %s\n", r->restaurant.headChef);
	printf("\n");
	printf("Specials - \n");

	for (int i = 0; i < MENUSIZE; i++)
	{
		printf("%s\n", r->restaurant.specialityMenu[i]);
	}

	printf("Would you like to see the recipes for today's dishes?\n");
	printf("1 - Yes\n2 - No\n");
	printf("Selection - ");
	
	int selection;
scanf_s("%d", &selection);
	switch (selection)
	{
	default:
		printf("Selection not valid, exiting to main menu\n");
		break;
	case 1:
		displayIngredients(r);
		displayRecipe(r);
		break;
	case 2:
		printf("Returning to main menu!\n");
		break;
	}


}

void displayAllRestaurants(PRESTAURANTNODE r)
{
	printf("\n");
	printf("\x1b[%dm", CYAN_FG);
	printf("Restaurants!");
	printf("\x1b[%dm", DEFAULT_FG);
	printf("\n");
	recursiveDisplayAllRestaurants(r);
}

void recursiveDisplayAllRestaurants(PRESTAURANTNODE r)
{
	if (r == NULL)
		return;
	else
		printf("%s\n", r->restaurant.restaurantName);

	recursiveDisplayAllRestaurants(r->nextNode);
}

void displayRecipe(PRESTAURANTNODE p)
{
	printf("\nRecipe for %s\n", p->restaurant.specialityMenu[0]);
	recursiveDisplayRecipe(p->restaurant.instructionQueueHead->head);
}

void recursiveDisplayRecipe(PINSTRUCTION p)
{
	if (p == NULL)
		return;
	else
	{
		printf("%s\n", p->instruction);
	}
	recursiveDisplayRecipe(p->nextNode);
}

void displayIngredients(PRESTAURANTNODE p)
{
	printf("Ingredients required!\n");
	printf("Dish - %s\n", p->restaurant.specialityMenu[0]);
	recursiveDisplayIngredients(p->restaurant.ingredientQueueHead->head);
}

void recursiveDisplayIngredients(PINGREDIENT p)
{
	if (p == NULL)
		return;
	else
	{
		printf("%f ", p->measurement);
		printf("%s - ", p->unitOfMeasurement);
		printf("%s \n", p->ingredient);
	}
	recursiveDisplayIngredients(p->nextNode);
}