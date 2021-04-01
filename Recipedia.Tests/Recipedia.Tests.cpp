#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "search.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecipediaTests
{
	TEST_CLASS(SearchNumTests)
	{
	public:
		
		TEST_METHOD(T001_Five)
		{
			//Arrange
			int input = 5;
			char* expected = "centraltestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T002_One)
		{
			//Arrange
			int input = 1;
			char* expected = "maidotestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T003_Ten)
		{
			//Arrange
			int input = 1;
			char* expected = "mirazurtestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}
	};

	TEST_CLASS(SearchRestaurantTests)
	{
	public:

		TEST_METHOD(T004_maidotestname3)
		{
			//Arrange
			char* input = "maidotestname3";
			char* expected = "maidotestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRestaurant(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T005_geraniumtestname3)
		{
			//Arrange
			char* input = "geraniumtestname3";
			char* expected = "geraniumtestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRestaurant(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T006_mirazurtestname3)
		{
			//Arrange
			char* input = "mirazurtestname3";
			char* expected = "mirazurtestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRestaurant(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}
	};

	TEST_CLASS(SearchRecipeTests)
	{
	public:

		TEST_METHOD(T007_maidoribs3)
		{
			//Arrange
			char* input = "maidoribs3";
			char* expected = "maidoribs3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRecipe(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.specialityMenu[0]);
		}

		TEST_METHOD(T008_centralmashedpotatoes3)
		{
			//Arrange
			char* input = "centralmashed potatoes3";
			char* expected = "centralmashed potatoes3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRecipe(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.specialityMenu[1]);
		}

		TEST_METHOD(T009_mirazurcoffee3)
		{
			//Arrange
			char* input = "mirazurcoffee3";
			char* expected = "mirazurcoffee3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchRecipe(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.specialityMenu[2]);
		}
	};
}
