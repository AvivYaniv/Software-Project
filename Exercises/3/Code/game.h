#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include "solver.h"
#include "parser.h"


/*
	Game 
		a. This module encapsulates the Sudoku puzzle game and the Sudoku board. 

		b. It will be used to store and manipulate the game status, validate, and set moves, and so on.
*/


typedef enum GameStates_t {
	GAME_STARTED,
	GAME_ENDED
} GameStates;


/*
 * run the sudoku game, return 
 */
int runSudokuGame();



#endif /*_GAME_H_*/