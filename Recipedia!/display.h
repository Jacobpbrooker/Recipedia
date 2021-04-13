#pragma once

#include "restaurant.h"


#define BREAK \x1b[%dm
// Ascii Characters
#define UPPER_BLOCK 223
#define BLOCK 219
#define LOWER_BLOCK 220
#define TOP_RIGHT_CORNER 187
#define LOWER_LEFT_CORNER 200
#define HORIZONTAL_LINE 205
#define VERTICAL_LINE 186
#define TOP_LEFT_CORNER 201
#define LOWER_RIGHT_CORNER 188
#define SHADING 176
#define STAR 42
#define SPACE 255
#define REG_SPACE 32
#define TEXTBLOCK 33
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
void ColourdisplayMainMenu(void);
void displayTitle(void);
void displaySearch();
void displayRestaurant(PRESTAURANTNODE);
void displayAllRestaurants(PRESTAURANTNODE);
void displayRecipe(PRESTAURANT);