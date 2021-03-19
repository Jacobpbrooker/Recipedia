#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "admin.h"

#define ADMINCODE 0x99										// this makes the admin code 1001 1001

unsigned char* convertCharToBits(char* adminCode, int codeLength)
{
	unsigned char* adminBitShiftCode;
	adminBitShiftCode = (unsigned char*)malloc(sizeof(unsigned char*) * codeLength);
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
}

bool adminMode(unsigned char* commandLineCode, int codeLength) 
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



//PARITY Parity(unsigned char* buf, int iBufLen) {
//
//	// this is going to take an unsigned char which will be the char represented by the binary code
//	// the iBufLen is the number of bytes we need to go through (so every 8 bits iBufLen will increase by 1)
//
//	PARITY returnParity = PAR_ERROR;		// set return variable to error default, defensive coding in case of mistake function will return error if other value not changed
//	unsigned char maskReset = 0x80;			// 0x80 is is 1000 0000 in binary 
//	unsigned char bitMask = maskReset;		// set the bitmask to the 1000 0000
//	int onesForParity = 0;					// set the initial number of ones to zero so that we can increment within the loop
//
//	printf("*****************************************\n");
//	printf("Binary - ");
//
//	int runs = 0;							// this is a counter for me later to check the numbers of runs
//
//	for (int i = 0; i < iBufLen;)
//	{
//		if (*buf & bitMask)					// now we check the buf that was passed (will be binary) against the bit mask using an & (and)
//			onesForParity++;				// the & will check if there are 1 in the bit mask and 1 in the inputted data
//											// if both have 1's the parity 1's increment (show notepad)
//
//		printf("%d", !!(*buf & bitMask));	// I just want to print the bits here so I actually print the bitmask
//											// the !! operator checks if the value is zero (if it is returns 0) and if it is any other value we return 1
//											// this makes us able to print the 1's and 0's of binary (but does not actually check if the value is one (just that the value is not 0))
//											// functionally identical to (!(int) == 0) if int is not zero return true.
//
//		bitMask >>= 1;						// we shift the bit within the bit mask by one to the right and repeat again (check against mask and increment if 1 and 1)
//
//		if (bitMask == 0)					// if the bitmask is 0000 0000 (meaning we have bitshifted the one completely off) we reset it back to 1000 0000 to continue
//		{
//			bitMask = maskReset;			// we use the maskReset varaible initialized above to return the bitMask to the correct position
//			buf++;							// we then move to the next inputed argument (next inputted binary from command line)
//			i++;							// then we increment i to go again with the next argument
//			runs++;							// this is a counter for me later to check the numbers of runs against
//		}
//
//	}
//	printf("\n");							// formatting to print the binary
//
//	if (onesForParity % 2 == 0)				// modulo check for even or odd return
//		returnParity = PAR_EVEN;			// set return variable
//	else
//		returnParity = PAR_ODD;
//
//	// this section is entirely for printing to the terminal (no functional changed to data)
//	printf("This is inside the Parity() function\n");
//	printf("Number of Ones - %d\n", onesForParity);
//	printf("Parity (0 - Even | 1 - Odd) - %d\n", returnParity);
//	printf("Number of loops through the program (should match the number of bytes entered) - %d\n", runs);
//	printf("-----------------------------------------\n");
//
//	return returnParity;					// return the parity
//}