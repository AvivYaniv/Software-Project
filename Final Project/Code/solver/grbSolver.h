#ifndef _GRB_SOLVER_H_
#define _GRB_SOLVER_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gurobi_c.h>

#include "../boardUtils/boardUtils.h"
#include "../boardUtils/boardEntities.h"


/* names of the gurobi's output files */
#define GUROBI_LOG_FILE_NAME "grbLog.txt"
#define GUROBI_LP_FILE_NAME "grbSudoku.lp"

/* names of the gurobi's model */
#define GUROBI_LOG_MODEL_NAME "sudoku"

/* minimal length of name used in the gurobi ILP */
#define NAME_MIN_LEN 10


/* 
 * Call this function once at the begining of the program's runtime to initialize the gurobi
 * ILP sudoku solver and setup gurobi's environment.
 * 
 * @ret: TRUE <-> environment initialized successfully.
 */
int initGrbEnvironment();

/* 
 * Call this function once at the end of the program's runtime to close the gurobi ILP sudoku 
 * solver and free gurobi's environment. 
 */
void closeGrbEnvironment();


/*
 * solve 'orig_board' with gurobi's ILP and store the solution in the in place.
 *  
 * orig_board - pointer to sudoku board for solving
 * boxW, boxH - size of box
 *  
 * @ret: if 'orig_board' has a solution and was solved, the function returns TRUE.
 * if the 'orig_board' does not have a solution or the gurobi's ILP failed or 
 * encountered an error, the function returns FALSE.
 */
int runGurobiSolver(BoardCell** orig_board, int boxW, int boxH);


/* 
 * Set constraints for the gurobi solver based on the rules of the sudoku game. 
 * 
 * grbEnv - pointer to gurobi's environment.
 * model - pointer to gurobi's current model.
 * dim - size of the board (width or height)
 * boxW, boxH - board's box size
 * indexArr - array of variables
 * constraintValArr - array of values of constraints
 * lowerBoundsArr - array of lower bounds of the constraints
 * valType - type of values
 * names - array of variables names
 * nameStorage - name storage (string)
 * sol - array of solution values
 * board - board's 2D array of values
 * 
 * @ret: TRUE <-> constraints were set successfully
 */
int setGrbModelConstraints(	GRBenv *grbEnv, GRBmodel *model, int dim, int boxW, int boxH, int* indexArr, 
							double* constraintValArr, double* lowerBoundsArr, char* valType, char** names, 
							char* nameStorage, double* sol, int* board[] );


/* Create a new empty model in the environment
 * 
 * board - board's 2D array of values
 * dim - size of the board (width or height)
 * nameStorage - name storage (string)
 * lowerBoundsArr - array of lower bounds of the constraints
 * valType - type of values
 * names - array of variables names
 */
void createEmptyGrbModel(	int **board, int dim, char* nameStorage, double *lowerBoundsArr, 
							char *valType, char **names);


/* copy sudoku board to gurobi 2D array 
 * 
 * board - board's 2D array of values
 * sudokuBoard - game's sudoku board data structure
 * dim - size of the board (width or height)
 */
void sudokuBoardToGrbBoard(int** board, BoardCell** sudokuBoard, int dim);

/* Write 'sol' content to game's sudoku board ('sudokuBoard') 
 * 
 * sudokuBoard - game's sudoku board data structure
 * sol - board's 2D array of values
 * dim - size of the board (width or height)
*/
void grbBoardToSudokuBoard(BoardCell** sudokuBoard, double* sol, int dim);



/* Helper subroutine for memory allocations of the gurobi sudoku solver.
 * Return TRUE if succeeded allocating memeory, FALSE otherwise.
 * 
 * env - pointer to gurobi's environment.
 * model - pointer to gurobi's current model.
 * dim - size of the board (width or height)
 * indexArr - pointer to array of variables
 * constraintValArr - pointer to array of values of constraints
 * lowerBoundsArr - pointer to array of lower bounds of the constraints
 * valType - pointer to type of values
 * names - pointer to array of variables names
 * nameStorage - pointer to name storage (string)
 * sol - pointer to array of solution values
 * board - board's 2D array of values
 * 
 * @ret: TRUE <-> constraints were set successfully
 */
int allocateGrbMem(	GRBenv *env, GRBmodel *model, int dim, int** indexArr, double** constraintValArr, 
					double** lowerBoundsArr, char** valType, char*** names, char** nameStorage, 
					double** sol, int** board[] );


/* call this function to free all memory that was allocated by the 'runGurobiSolver' function
 * arguments are pointers to allocated memory in 'runGurobiSolver' function  
 * 
 * env - pointer to gurobi's environment.
 * model - pointer to gurobi's current model.
 * dim - size of the board (width or height)
 * ind - array of variables
 * val - array of values of constraints
 * lb - array of lower bounds of the constraints
 * vtype - type of values
 * names - pointer to array of variables names
 * nameStorage - name storage (string)
 * sol - array of solution values
 * board - board's array of values
 */
void freeGrbMem(GRBenv *env, GRBmodel *model, int dim, int* ind, double* val, double* lb, 
				char* vtype, char** names, char* namestorage, double* sol, int* board[]); 



#endif /*_GRB_SOLVER_H_*/
