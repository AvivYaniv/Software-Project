#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

int main( int argc, char *argv[] )
{	
	/* Const Section */
	
	/* Variables Section */
	int seed = 0;
	
	/* Code Section */		
	SP_BUFF_SET();
	
	/* get seed from command line arguments */
	if ( 1 < argc ) {
		sscanf( (const char*)argv[1], "%d", &seed);
	}
	srand(seed); 
	/*printf("seed: %d \n", seed);*/
 
	return runSudokuGame();
}
