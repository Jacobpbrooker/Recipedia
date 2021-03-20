#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "admin.h"
//#include "restaurant.h"

#define ADMINCODE 0x99										// this makes the admin code 1001 1001
#define RESTAURANTNAME 50
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
	int userSelection = 1;
	char restaurantDelete[RESTAURANTNAME];
	char* testRestaurantDelete = "arpegetestname\0";
	do {
		displayMenu();
		//scanf_s("%d", &userSelection);
		switch (userSelection)
		{
		case 1:
			printf("You have selected remove restaurant\n");
			printf("Enter name of restaurant to be deleted\n");
			printf("Restuarant - ");
			restaurantList = deleteRestaurant(restaurantList, testRestaurantDelete);
			//scanf_s("%s", restaurantDelete, RESTAURANTNAME);
			//find and delete(free) the node on the linked list

			break;
		case 2:
			break;
		default:
			break;
		}
	} while (userSelection != 0);

}

PRESTAURANTNODE deleteRestaurant(PRESTAURANTNODE restaurantList, char* restaurant)
{
	return recursiveFindAndDeleteRestaurant(restaurantList, restaurant, restaurantList);
}


PRESTAURANTNODE recursiveFindAndDeleteRestaurant(PRESTAURANTNODE restaurantNode, char* restaurant, PRESTAURANTNODE previousNode)
{
	PRESTAURANTNODE tempNode = restaurantNode;
	
	if (restaurantNode == NULL)	// exit condition
	{
		return;
	}


	if (strcmp(restaurantNode->restaurant.restaurantName, restaurant) == 0)			// node is head of list (working)
	{
		restaurantNode = tempNode->nextNode;
		free(tempNode);
		return restaurantNode;
	}
	else if (strcmp(restaurantNode->nextNode->restaurant.restaurantName, restaurant) == 0) // searched for node is next node
	{
		// connect current node to next->next node
		// free node at tempnode->next
		// return the list? that doesnt make sense
		previousNode->nextNode->nextNode = restaurantNode->nextNode->nextNode->nextNode; // this is working but there has to be a better way
		free(tempNode->nextNode); // this is not working its freeing the wrong value
		return restaurantNode;
	}
	else {
		recursiveFindAndDeleteRestaurant(restaurantNode->nextNode, restaurant, restaurantNode);
	}

	return tempNode;
}

bool addRestaurant(PRESTAURANTNODE restaurantList)
{

}

void displayMenu(void)
{
	printf("Welcome to Adminstrator Menu for Recipedia\n\n");
	printf("Sections\n");
	printf("1 - Delete Restaurant\n");
	printf("2 - Add Restaurant\n");
	printf("Selection - ");
}