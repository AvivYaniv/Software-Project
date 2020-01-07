#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gameLogic/gameLogic.h"

int main()
{	
	/* Variables Section */
	int seed = time(NULL);
	int res;

	/* Code Section */		
	SP_BUFF_SET();

	srand(seed); 

	/* if the gurobi solver is used (default), initialize it's environment */
	#ifndef SOLVER_BT
	if ( !initGrbEnvironment() ) {
		printf("Error: could not initialize gurobi solver\n");
		return -1;
	}
	#endif /* SOLVER_BT */
 
	/* start the sudoku game loop */
	res = runSudokuConsoleGame();

	/* if the gurobi solver is used (default), close it's environment */
	#ifndef SOLVER_BT
	closeGrbEnvironment();
	#endif /* SOLVER_BT */

	return res;
}
