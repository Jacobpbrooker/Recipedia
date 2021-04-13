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