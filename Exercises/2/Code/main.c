#include <stdio.h>
#include <stdlib.h>

#include "main_aux.h"

int main()
{
	
	/* Variables Section */
	int i;
	int heap_size;
	int number_of_heaps;
	int number_of_arguments;
	
	int heaps[32] = {0};
	

	/* Code Section */		
	SP_BUFF_SET();

	/* Getting number of heaps */
	printf("Enter the number of heaps:\n");
	
	if (1 > (number_of_arguments = scanf("%d", &number_of_heaps)) || (1 > number_of_heaps) || (32 < number_of_heaps))
	{
		printf("Error: the number of heaps must be between 1 and 32.\n");
		
		/* Program ends peacfully */
		return 0;
	}
	
	printf("Enter the heap sizes:\n");
	
	/* Getting heap sizes */
	for (i = 0; i < number_of_heaps; ++i)
	{
		if (1 > (number_of_arguments = scanf("%d", &heap_size)) || (0 > heap_size))
		{
			printf("Error: the size of heap %d should be positive.\n", (1+i));
									
			/* Program ends peacfully */
			return 0;
		}
						
		/* Getting size of each heap */
		heaps[i] = heap_size;
	}
	
	/* Running Nim game */
	runNim(number_of_heaps, heaps);	
	
	/* Program ends peacfully */
	return 0;
}
