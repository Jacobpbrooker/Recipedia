#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "admin.h"
//#include "restaurant.h"
#include "search.h"

#define ADMINCODE 0x99										// this makes the admin code 1001 1001
#define RESTAURANTNAME 50
#define MAXINPUT 150

unsigned char* convertCharToBits(char* adminCode, int codeLength)
{
	unsigned char* adminBitShiftCode;
	adminBitShiftCode = (unsigned char*)malloc(sizeof(unsigned char*) * codeLength);
	if (!adminBitShiftCode)
	{
		fprintf(stderr, "Failed to allocate memory for adminBitShiftCode\n");
		exit(EXIT_FAILURE);
	}

	memset(adminBitShiftCode, '\0', sizeof(unsigned char*) * codeLength);


	unsigned char one = 0x31;								// this is (char)one in hex
	unsigned char zero = 0x30;								// this is (char)zero in hex
	unsigned char maskReset = 0x80;							// this is 1000 0000 in hex
	unsigned char bitMask = maskReset;			
	int parityCheckCounter = 0;

	for (int i = 0; i < codeLength; i++)
	{
		if (*adminCode != one && *adminCode != zero)		// (check that this works properly) check for illegal character in array. If not 1 or 0 then return the original char array
		{
			free(adminBitShiftCode);						// error, free the malloced memory and return the initial adminCode argument
			return adminCode;
		}
		if (*adminCode == one)
		{
			*adminBitShiftCode |= bitMask;
		}
		
		bitMask >>= 1;										// bit shift all bits to the right

		if (bitMask == 0)
		{
			return(adminBitShiftCode);						// this is the end of the bitshift, as we will only check 8 bits, return the bit admin code to be checked in next equation
		}

		++adminCode;										// increment position in array
	}
	return(adminBitShiftCode);
}

bool returnAdminConfirmation(unsigned char* commandLineCode, int codeLength) 
{
	bool returnAdminMode = false;							// set return variable to false default
	
	unsigned char* adminCode = convertCharToBits(commandLineCode, codeLength);
	unsigned char savedAdmin = ADMINCODE;
	unsigned char grantAdmin;
	
	grantAdmin = *adminCode ^ savedAdmin;					// XOR argument bin code vs defined admin code 

	if (grantAdmin == 0)									// only change admin mode to true from successful XOR
		returnAdminMode = true;

	return returnAdminMode;
}

void adminMode(PRESTAURANTNODE restaurantList)
{
	int userSelection;
	//char restaurantDelete[RESTAURANTNAME];
	char* testRestaurantDelete = "maidotestname3\0";
	char restaurant[MAXSTRINGLENGTH] = { '\0' };
	do {
		displayAdminMenu();
		scanf_s("%d", &userSelection);
		switch (userSelection)
		{
		case 1:
			printf("You have selected remove restaurant\n");
			displayAllRestaurants(restaurantList);
			printf("Enter name of restaurant to be deleted\n");
			printf("Restuarant - ");
			scanf_s("%s", restaurant, MAXSTRINGLENGTH);
			for (unsigned int i = 0; i < strlen(restaurant); i++)
			{
				if (restaurant[i] == '\n')
					restaurant[i] = '\0';
			}
			restaurantList = deleteRestaurant(restaurantList, restaurant);
			displayAllRestaurants(restaurantList);
			break;
		case 2:
			printf("You have selected add new restaurant\n");
			addRestaurant(restaurantList);
			displayAllRestaurants(restaurantList);
			break;
		case 0:
			printf("Now Exiting Admin mode!\n");
			return;
		default:
			break;
		}
	} while (userSelection != 0);

}

PRESTAURANTNODE deleteRestaurant(PRESTAURANTNODE restaurantList, char* restaurant)
{
	return recursiveFindAndDeleteRestaurant(restaurantList, restaurant);
}


PRESTAURANTNODE recursiveFindAndDeleteRestaurant(PRESTAURANTNODE currentNode, char* restaurant)
{
	if (currentNode == NULL || currentNode->nextNode == NULL)	// exit condition
	{
		return NULL;
	}
	if (strcmp(currentNode->restaurant.restaurantName, restaurant) == 0)			// node is head of list (not working)
	{
		PRESTAURANTNODE tempnode = currentNode;
		currentNode = tempnode->nextNode;
		free(tempnode);
		return currentNode;
	}
	else if (strcmp(currentNode->nextNode->restaurant.restaurantName, restaurant) == 0) // searched for node is next node
	{
		PRESTAURANTNODE deleteNode = currentNode->nextNode;
		currentNode->nextNode = currentNode->nextNode->nextNode; 
		free(deleteNode); 
		return currentNode;
	}
	else {
		recursiveFindAndDeleteRestaurant(currentNode->nextNode, restaurant, currentNode);
	}
}

void addRestaurant(PRESTAURANTNODE restaurantList)
{
	PRESTAURANTNODE tempNode = restaurantList;

	while (tempNode->nextNode != NULL)
	{
		tempNode = tempNode->nextNode;
	}

	tempNode->nextNode = createRestaurant(tempNode->nextNode, returnNewRestaurant());
}

void displayAdminMenu(void)
{
	printf("\x1b[%dm", BRIGHT_GREEN_FG);
	printf("\t   _   ___  __  __ ___ _  _				\n");
	printf("\t  /_\\ |   \\|  \\/  |_ _| \\| |			\n");
	printf("\t / _ \\| |) | |\\/| || || .` |			\n");
	printf("\t/_/ \\_|___/|_|  |_|___|_|\\_|	\n");
	printf("\x1b[%dm", DEFAULT_FG);
	printf("\n");

	printf("Welcome to Adminstrator Menu for Recipedia\n\n");
	printf("Sections\n");
	printf("1 - Delete Restaurant\n");
	printf("2 - Add Restaurant\n");
	printf("\x1b[%dm", LIGHT_RED_FG);
	printf("0 - Exit Admin mode\n");
	printf("\x1b[%dm", DEFAULT_FG);
	printf("Selection - ");
}

