#pragma once

#include "restaurant.h"

// ANSI Colours
#define BLUE_FG 34
#define CYAN_FG 36
#define GREEN_FG 32
#define BRIGHT_RED_FG 31
#define LIGHT_RED_FG 91
#define BRIGHT_GREEN_FG 92
#define BRIGHT_BLUE_FG 94
#define BRIGHT_MAGENTA_FG 95
#define BRIGHT_CYAN_FG 96
#define DEFAULT_FG 0


void displayMainMenu();
void colourDisplayMainMenu(void);
void displayTitle(void);
void displaySearch();
void displayRestaurant(PRESTAURANTNODE);
void displayAllRestaurants(PRESTAURANTNODE);
void recursiveDisplayAllRestaurants(PRESTAURANTNODE);
void displayRecipe(PRESTAURANTNODE);
void recursiveDisplayRecipe(PINSTRUCTIONQUEUE);
void displayIngredients(PRESTAURANTNODE);
void recursiveDisplayIngredients(PINGREDIENTQUEUE);