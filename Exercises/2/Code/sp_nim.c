#include "sp_nim.h"

void computerPlayTurn(int number_of_heaps, int* heaps)
{
	/* Variables Section */	
	int i;
	int nim_sum;	
	int min_heap_index;
		
	/* Code Section */
	nim_sum = 0;	
	for (i = 0; i < number_of_heaps; ++i)
	{
		nim_sum ^= heaps[i];
	}
	
	if (0 != nim_sum)
	{		
		min_heap_index = 0;
		for (i = 0; i < number_of_heaps; ++i)
		{
			if ((heaps[i] ^ nim_sum) < heaps[i])
			{
				min_heap_index = i;				
				break;
			}			
		}
		
		printf("Computer takes %d objects from heap %d.\n", (heaps[min_heap_index]-(heaps[min_heap_index] ^ nim_sum)), (1+min_heap_index));
		heaps[min_heap_index] -= heaps[min_heap_index]-(heaps[min_heap_index] ^ nim_sum);
	}
	else
	{
		for (i = 0; i < number_of_heaps; ++i)
		{
			if (heaps[i] > 0)
			{
				heaps[i]--;
				printf("Computer takes %d objects from heap %d.\n", 1, (1+i));
				break;
			}			
		}
	}
}
