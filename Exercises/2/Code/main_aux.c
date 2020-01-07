#include "main_aux.h"

void printHeaps(int turn, int number_of_heaps, int* heaps)
{
	int i = 0;
	
	printf("In turn %d heap sizes are:", turn);
	
	for(i = 0; i < number_of_heaps; i++)
	{
		printf(" h%d=%d", (1+i), heaps[i]);		
	}
	
	printf(".\n");
}

int isNimEndOfGame(int number_of_heaps, int* heaps)
{
	int i = 0;	
		
	for(i = 0; i < number_of_heaps; i++)
	{
		if (0 != heaps[i])
		{
			return FALSE;		
		}
	}
	
	return TRUE;
}



int isCharWhitespace(char c) {
	return ( (' ' == c) || ('\n' == c) || ('\t' == c) || ('\r' == c) || 
			 ('\f' == c) || ('\v' == c) || (EOF == c) );
}

void consumeInputUntilWhitespace() {
	char c;
	while ( FALSE == isCharWhitespace( c = getchar() ) );
	/*
	while ( FALSE == isCharWhitespace( c = getchar() ) ) {printf("[%d]\n", c);}
	*/
}

void userPlayTurn(int number_of_heaps, int* heaps)
{		

	/* Variables Section */		
	int is_valid_input;
	int heap_index;
	int number_of_removed_objects;	
	
	/* Code Section */		
	printf("Your turn: please enter the heap index and the number of removed objects.\n");
	
	do
	{	
		is_valid_input = TRUE;

		if (1 == scanf("%d", &heap_index) ) {

			if ( 1 == scanf("%d", &number_of_removed_objects) ) {
				
				if ( (1 <= heap_index) && (number_of_heaps >= heap_index) )
				{
					/* Correcting according to place in zero-based array */ 
					heap_index -= 1;
					
					if ( 0 > (heaps[heap_index] - number_of_removed_objects) )
					{
/*
						printf("--%d\n", 3);
*/
						is_valid_input = FALSE;
					}

				} else {
/*
					printf("--%d\n", 1);
*/
					is_valid_input = FALSE;	
				}	
			} else {
/*
				printf("--%d\n", 02);
*/
				consumeInputUntilWhitespace();
				is_valid_input = FALSE;	
			}

		} else {

/*
			printf("--%d\n", 01);
*/
			consumeInputUntilWhitespace();
			is_valid_input = FALSE;	
		}

						
		if (TRUE != is_valid_input)
		{
			printf("Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n");
		}
	}
	while (TRUE != is_valid_input);
	
	printf("You take %d objects from heap %d.\n", number_of_removed_objects, (1+heap_index));
	
	heaps[heap_index] = heaps[heap_index] - number_of_removed_objects;
	
}

void runNim(int number_of_heaps, int* heaps)
{	
	/* Variables Section */	
	int trun_number = 1;	
	
	/* Code Section */
	while (FALSE == isNimEndOfGame(number_of_heaps, heaps))
	{
		printHeaps(trun_number, number_of_heaps, heaps);
		
		if (0 == (trun_number % 2))
		{
			computerPlayTurn(number_of_heaps, heaps);
		}
		else
		{
			userPlayTurn(number_of_heaps, heaps);			
		}
						
		++trun_number;
	}
	
	if (0 == (trun_number % 2))
	{
		printf("You win!\n");
	}
	else
	{
		printf("Computer wins!\n");
	}
}
