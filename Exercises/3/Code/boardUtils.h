#ifndef _BOARD_UTILS_H_
#define _BOARD_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include "boardEntities.h"


/*
	boardUtils 
		This module contains general board utilities, so that the game is encapsulated from the solver part. 
*/


/* board - pointer to the sudoku board
 * x, y - cell position in the board
 * board_width - width of the board
 *
 * return TRUE iff the number at x,y appears only once in the given row (row y) 
 */
int validateCellRowByLoc(BoardCell*** board, int x, int y, int board_width);

/* board - pointer to the sudoku board
 * x, y - cell position in the board
 * board_height - height of the board
 *
 * return TRUE iff the number at x,y appears only once in the given column (column x) 
 */
int validateCellColByLoc(BoardCell*** board, int x, int y, int board_height);

/* board - pointer to the sudoku board
 * x, y - cell position in the board
 * boxW, int boxH - width and height of a box
 *
 * return TRUE iff the number at x,y appears only once in the given box (box containing x,y) 
 */
int validateCellBoxByLoc(BoardCell*** board, int x, int y, int boxW, int boxH);

/* board - pointer to the sudoku board
 * x, y - cell position in the board
 * board_width, board_height - width and height of the board
 * boxW, int boxH - width and height of a box
 *
 * return TRUE iff n is not in row y, column x, and box contaning cell x,y
 */
int validateCellByLoc(BoardCell*** board, int x, int y, int board_width, int board_height, int boxW, int boxH);



/* board - pointer to the sudoku board
 * y - row number
 * n - value to check
 * board_width - width of the board
 *
 * return TRUE iff the number n appears only once in the given row (row y) 
 */
int validateRowByVal(BoardCell*** board, int y, int n, int board_width);

/* board - pointer to the sudoku board
 * x - column number
 * n - value to check
 * board_height - height of the board
 *
 * return TRUE iff the number n appears only once in the given column (column x) */
int validateColByVal(BoardCell*** board, int x, int n, int board_height);

/* board - pointer to the sudoku board
 * x - column number
 * y - row number
 * n - value to check
 * board_width - width of the board
 *
 * return TRUE iff the number n appears only once in the box containing cell x,y */
int validateBoxByVal(BoardCell*** board, int x, int y, int n, int boxW, int boxH);

/* board - pointer to the sudoku board
 * x - column number
 * y - row number
 * n - value to check
 * board_width, board_height - width and height of the board
 * boxW, int boxH - width and height of a box
 *
 * return TRUE iff n is not in row y, column x, and box contaning x,y*/
int validateCellByVal(BoardCell*** board, int x, int y, int n, int board_width, int board_height, int boxW, int boxH);



/* arr - pointer to array of ints
 * arrayLen - pointer to int representing the size of the array (will be decreased on shrinking)
 * removedElemIndex - index of the element to be removed
 * 
 * remove the element in the given index and decrease array len */
void shrinkArray(int* arr, int *arrayLen, int removedElemIndex);

/* x, y - current cell position
 * nx, ny - position of the next cell 
 * w, h - width and height of the board
 *
 * set the nx and ny to the index of the next cell in the board relative to x and y */
int calcNextCell(int x, int y, int *nx, int *ny, int w, int h);


/* board - pointer to the sudoku board
 * x - column number
 * y - row number
 * validsArray - pointer to an array of valid values for the cell
 * arrLen - pointer to the valid values array length
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 *
 * filter non-valid values from possible values array*/
void removeInvalidArrValues(BoardCell*** board, int x, int y, int* validsArray, int* arrLen, int boardW, int boardH, int boxW, int boxH);

/* print the given array arr of length len */
void printArr(int* arr, int len);

/* put sequential values in the given array. i.e 1,2,3,4,5,6... */
void putSeqValuesInArr(int* arr, int arrLen);

/* get a random int from [0, x] */
int getRandInt(int x);



/* board - pointer to the sudoku board
 * w, h - width and height of the board
 *
 * returns TRUE iff all cell's values in board are != 0*/
int isBoardFilled(BoardCell*** board, int w, int h);


/* board - pointer to the sudoku board
 * boardW, boardH - width and height of the board
 * boxW, boxH - width and height of a box
 *
 * returns TRUE iff the board is a filled and valid sudoku board */
int isFilledBoardValid(BoardCell*** board, int boardW, int boardH, int boxW, int boxH);

/* board - pointer to the sudoku board
 * w, h - width and height of the board
 *
 * set all the cells to 'fixed' */
void makeBoardCellsFixed(BoardCell*** board, int w, int h);

/* board - pointer to the sudoku board
 * board_width, board_height - width and height of the board
 *
 * create a new board of size board_width, board_height */
BoardCell*** allocateBoard(int board_width, int board_height);

/* board - pointer to the sudoku board
 * board_width, board_height - width and height of the board
 *
 * free the memory allocated by the board and the board itself */
void freeBoard(BoardCell*** board, int board_width, int board_height);


/* board - pointer to the sudoku board
 * w, h - width and height of the board
 *
 * hide random cells in the board so that there are only #cellsToShow shown */
void hideCellsInBoard(BoardCell*** board, int w, int h, int cellsToShow);


/* dst - copy to this board
 * src - copy from this board
 * w, h - width and height of the board
 *
 * copy all the data of 'src' to 'dst'*/
void copyBoard(BoardCell*** dst, BoardCell*** src, int w, int h);


/* board - pointer to the sudoku board
 * board_width, board_height - width and height of the board
 * 
 *print the board to console */
void printBoard(BoardCell*** board, int board_width, int board_height);


/* init board to zeros */
void zerosBoard(BoardCell*** board, int board_width, int board_height);


/* create a dummy board for testing */
void dummyBoard2(BoardCell*** board);

/* create a dummy board for testing */
void dummyBoard3(BoardCell*** board);



#endif /*_BOARD_UTILS_H_*/
