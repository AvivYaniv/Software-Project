#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <stdio.h>
#include <stdlib.h>
#include "../boardUtils/boardEntities.h"
#include "../boardUtils/boardUtils.h"
#include "../Stack/Stack.h"

/* if the program is tested locally, gurobi is not used */
#ifndef SOLVER_BT
#include "grbSolver.h"
#endif /* SOLVER_BT */

/*
	Solver Module
		board solving routines. This module implements:
		a. The stacked backtrack algorithms for 'num_solutions' command.  
		b. The board solving function. 

		The function 'solveBoard()' is a wrapper function for the actual board solving routine. 
		If the program is compiled regularly (i.e 'make all', without 'SOLVER_BT' flag), gurobi 
		ILP is used to solve the board (WORKS ON NOVA).
		If the program is compiled with the 'SOLVER_BT' flag ('make all SOLVER_BT=1'), regular 
		backtrack algorithm is used to solve the board (USED FOR LOCAL TESTING).

*/



/*
 * which type of backtracking we use (used for testing)
 */
typedef enum BackTrackMode {
	DETERMINISTIC,
	RANDOM
} BackTrackMode;



/* run board solving algorithm to get the number of possible solutions to the board.
 *
 * board - pointer to the sudoku board
 * boxW, boxH - width and height of a box
 *
 * @ret: number of solutions to the board
 */
int getNumOfSolutions(BoardCell*** board, int boxW, int boxH);




/* board - pointer to the sudoku board
 * boxW, boxH - width and height of a box
 *
 * run board solving algorithm on board and return TRUE if board is solvable and store results in the board.
 *
 * @ret: TRUE <-> board solved successfully
 */
int solveBoard(BoardCell*** board, int boxW, int boxH);



/* USED FOR TESTING PURPOSES, NOT USED IN THE NOVA VERSION!!! 
 *
 * run backtrack algorithm on board and return TRUE if board is solvable and store results in
 * the board, this function calls the recursive backtrack function below.
 *
 * board - pointer to the sudoku board
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 * btMode - backtracking algorithm mode: random or deterministic
 *
 */
int runBacktrack(BoardCell*** board, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode);


/* USED FOR TESTING PURPOSES, NOT USED IN THE NOVA VERSION!!! 
 *
 * run BT algorithm on board and return TRUE if board is solvable and store results in the board,
 * this is the recursive BT function 
 *
 * board - pointer to the sudoku board
 * x, y - current postion of the backtrack algorithm
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 * btMode - backtracking algorithm mode: random or deterministic
 */
int recBackTrack(BoardCell*** board, int x, int y, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode);



#endif /*_SOLVER_H_*/
