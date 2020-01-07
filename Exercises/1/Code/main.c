#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const int MIN_BASE = 2;
const int MAX_BASE = 16;

const int SRC_BASE = 0;
const int DST_BASE = 1;

const int RESULT_NOT_NUM_YET = 0;
const int RESULT_ZERO = 1;
const int RESULT_POSITIVE = 2;


int getBaseFromUser(int* dst, int isSrc) {
	int i;

	if ( 1 == scanf("%d", &i) ) {
    	/* Test if valid */
    	if ( MIN_BASE <= i && i <= MAX_BASE ) {    	
    		*dst = i;
		    return 1;
    	} else {
    		if ( isSrc == SRC_BASE ) {
				printf("Invalid input base\n");    						
    		} else {
				printf("Invalid desired base\n");    						
    		}

		    return 0;		    
    	}

    } else {
	    printf("An error occurred!\n");
	    return 0;
    }
}


/*
int getBaseFromUser(int* dst, int isSrc) {
	float f;
	char lastChar;
	    
	if ( 2 == scanf("%f%c", &f, &lastChar) && (('\n' == lastChar) || (EOF == lastChar))) {
    	
		*dst = (int)f;
				
    	if (((int)f != f) || (0 > f))
    	{	
    		printf("Invalid input base\n");    			
    		return 0;
    	}
    	
    	if ( MIN_BASE <= *dst && *dst <= MAX_BASE ) {    	
		    return 1;
    	} else {
    		if ( isSrc == SRC_BASE ) {
				printf("Invalid input base\n");    						
    		} else {
				printf("Invalid desired base\n");    						
    		}

		    return 0;		    
    	}

    } else {
	    printf("An error occurred!\n");
	    return 0;
    }
}
*/

long numberToDecimal(int* number, int digits, int base)
{
	int i;
	long baseExponent = 1;
	long decimal = 0;
	
	for (i=0; i < digits; ++i)
	{
		decimal += number[digits-i-1] * baseExponent;
		baseExponent *= base;
	}
	
	return decimal;
}

unsigned char digitToChar(int d)
{
	static const unsigned char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	return table[d];	
}

int decimalToNumber(long number, int base, unsigned char* arr)
{
	int resultDigits = 0;	
	int currentNumber = number;
	
	if (0 == currentNumber)
	{
		arr[0] = '0';
		return 1;
	}		
	
	while (0 < currentNumber)
	{ 
		arr[resultDigits] = digitToChar(currentNumber % base);
		currentNumber /= base;
		++resultDigits;
	}
	
	return resultDigits;
}

int charToDigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
	{	
		return c-'0';		
	}
	else if (c >= 'a' && c <= 'f')
	{
		return c-'a'+10;
	}
	else if (c >= 'A' && c <= 'F')
	{
		return c-'A'+10;
	}
	else
	{			
		return -1;
	}	
}

int main()
{
	const int MAX_NUM_OF_DIGITS = 1024; 

	int i;
	
	int baseA = 0;
	int baseB = 0;

	long decimal = 0;
	
	int numDigits = 0;
	int resultDigits = 0;
	
	int numADigitsArr[1024] = {0};
	unsigned char resultADigitsArr[1024] = {'0'};

    char c;
	int resStatus = RESULT_NOT_NUM_YET;
/*
    int numInDecimalBase = 0;

    int i;
*/

	/* Get base a */ 
    printf("Please enter the number's base:\n");
    if ( 0 == getBaseFromUser(&baseA, SRC_BASE) ) {
    	return 0;
    }

	/* Get base b */ 
    printf("Please enter the desired base:\n");
    if ( 0 == getBaseFromUser(&baseB, DST_BASE) ) {
    	return 0;
    }


    printf("Please enter a number in base %d:\n", baseA);    
    while ( 1 == scanf("%c", &c) ) {
    	int digit = 0;

    	/* End input gathering on new line or EOF */
    	if ( ( ('\n' == c) || (EOF == c) ) ) {
	    	/* do not consider white space from previous scanf's*/
    		if ( numDigits > 0 ) {
    			break;
    		}
    		continue;
    	}

    	/* Ignore everything after whitespace*/
   		if ( (' ' == c) || ('\n' == c) || ('\t' == c) || ('\r' == c) || ('\f' == c) || ('\v' == c) ) {
   			if (numDigits == 0 ) {			
	    		continue;
   			} else {
				break;			
   			}
   		}

    	/* Check if char is valid */
    	if ( ( ( digit = charToDigit(c) ) == -1) || 0 > digit || digit >= baseA ) {
		    printf("Invalid number!\n");
    		return 0;
    		
    	/* Leave only one preceeding 0 */
    	} else if ( 0 == digit ) {
    		if ( RESULT_NOT_NUM_YET == resStatus ) {
    			resStatus = RESULT_ZERO;
		    	numADigitsArr[0] = 0;
				numDigits = 1;	
    		}
    		
    	/* The digit is valid and greater than zero, so the number is positive */
    	} else {
    		resStatus = RESULT_POSITIVE;
    	}


    	/* Add char to array (ignor preceeding 0's) */
    	if ( numDigits < MAX_NUM_OF_DIGITS && resStatus == RESULT_POSITIVE) {
	    	numADigitsArr[numDigits] = digit;
			numDigits += 1;	
    	}    	
    }
    
    decimal = numberToDecimal(numADigitsArr, numDigits, baseA);

    if ( INT_MAX < decimal ) {
    	decimal = 0;
    }

    printf("The result is: ");
    
    resultDigits = decimalToNumber(decimal, baseB, resultADigitsArr);
    
    for (i = 0; i < resultDigits; ++i)
    {
    	printf("%c", resultADigitsArr[resultDigits-i-1]);	
    }
    printf("\n");
    
    return 0;
}