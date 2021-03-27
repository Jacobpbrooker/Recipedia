#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecipediaSaveLoadtests
{
	TEST_CLASS(adminFunctions)
	{
	public:
		
		TEST_METHOD(TestMethod_TestingOneandOne_ReturnTrue)
		{
			// arrange
			int x = 1;
			int y = 1;
			// act
			// N\A
			// assert
			Assert::AreEqual(x, y);
			//Assert::assertion(test, result);
		}
		TEST_METHOD(adminMode_returnAdminConfirmation_Return1)
		{
			// arrange
			unsigned char x[9] = "10011001";
			int y = 8;
			int expectedReturn = 1;
			// act
			int testReturn = returnAdminConfirmation(x, y);
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
	};
}
