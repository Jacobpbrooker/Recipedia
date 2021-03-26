#pragma once

#include "queue.h"

#define MAXSTRINGLENGTH 100
#define MAXINSTRUCTIONLENGTH 1000
#define MENUSIZE 3
#define MAXRECIPEINGRDIENT 15


typedef struct restaurant {								// restaurants will be stored individually in a linked list, with pointers to head of linked lists ingredients and instructions
	char* restaurantName;								// name of the restaurant
	char* headChef;										// name of the head chef of the restaurant
	char* restaurantSypnopsis;							// brief sypnopsis including location and awards, maybe famous people who have dined there - basically fun facts
	char specialityMenu[MENUSIZE][MAXSTRINGLENGTH];		// multi dimensional array for 3 specialty items (char array for each)
	struct ingredientQueue* ingredientQueueHead;		// pointer to ingredient linked list
	struct instructionQueue* instructionQueueHead;		// pointer to instruction linked list
} RESTAURANT, * PRESTAURANT;

typedef struct restaurantNode {							// this will be used for encapsulation of the restaurant struct and the next node
	struct restaurant restaurant;						// this can be passed into function as the head of the list
	struct restaurantNode* nextNode;					// this is a prototype I may just use the restaurant struct and have the nextNode in that struct 
}RESTAURANTNODE, *PRESTAURANTNODE;


/*RESTAURANTNODE createRestaurant(PRESTAURANTNODE, char*, char*, char*, char*, char*, char*);*/
PRESTAURANT returnRestaurant(char*);
PRESTAURANTNODE createRestaurant(PRESTAURANTNODE, PRESTAURANT);
void push(PRESTAURANTNODE*, RESTAURANT);
PRESTAURANTNODE newNode(RESTAURANT);
PRESTAURANTNODE fetchNextNode(PRESTAURANTNODE);
PRESTAURANT returnNewRestaurant(void);

// free functions (worry about after)
void freeRestaurantList(PRESTAURANTNODE);
void freeNode(PRESTAURANTNODE);

