#pragma once
#include "restaurant.h"
// accessing admin mode
unsigned char* convertCharToBits(char*, int);
bool returnAdminConfirmation(unsigned char*, int);

// admin functionality
void adminMode(PRESTAURANTNODE);
PRESTAURANTNODE deleteRestaurant(PRESTAURANTNODE, char*);
PRESTAURANTNODE recursiveFindAndDeleteRestaurant(PRESTAURANTNODE, char*);
bool addRestaurant(PRESTAURANTNODE);

//admin displays
void displayMenu(void);