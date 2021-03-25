#pragma once

#include "queue.h"

// save files
bool saveFile(PRESTAURANTNODE, char*);
char* getRestaurantFileName(char*);
char* getIngredientsFileName(char*);
char* getInstructionsFileName(char*);
void saveRestaurantInfo(PRESTAURANTNODE, char*);
void saveIngredients(PRESTAURANTNODE, char*);
void saveInstructions(PRESTAURANTNODE, char*);

// load files
PRESTAURANTNODE loadRestaurants(char*);
