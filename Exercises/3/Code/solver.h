#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <stdio.h>
#include <stdlib.h>
#include "boardEntities.h"
#include "boardUtils.h"


/*
	Solver 
		a. This module implements the Backtrack algorithms. 
		
		b. Notice that it is importvoid printBoard(BoardCell*** board, int board_width, int board_height);
ant that the user of this module is not aware of the algorithm behind the module, i.e., it solves the board and the actual implementation may freely change without "breaking" the public interface of the module. 

		c. The interface is thus recommended to contain a solver method, and a puzzle generator method (which supplies a puzzle as well as a solution).

*/




typedef enum BackTrackMode {
	DETERMINISTIC,
	RANDOM
} BackTrackMode;

/*
typedef enum CellStatus {
	VALID,
	USER_SET,
	COLLISION
} CellStatus;
*/



/* board - pointer to the sudoku board
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 * btMode - backtracking algorithm mode: random or deterministic
 *
 * run BC algorithm on board and return TRUE if board is solvable and store results in the board,
 * this function calls the recursive BC function below
  */
int runBacktrack(BoardCell*** board, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode);

/* board - pointer to the sudoku board
 * x, y - current postion of the backtrack algorithm
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 * btMode - backtracking algorithm mode: random or deterministic
 *
 * run BC algorithm on board and return TRUE if board is solvable and store results in the board,
 * this is the recursive BC function */
int recBackTrack(BoardCell*** board, int x, int y, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode);



#endif /*_SOLVER_H_*/
