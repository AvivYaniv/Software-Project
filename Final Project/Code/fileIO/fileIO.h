#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../boardUtils/boardEntities.h"
#include "../boardUtils/boardUtils.h"

/*
 * 	FILE IO 
 * This module manages opening a text file and importing it as a sudoku board and vice versa, saving
 * a sudoku board as a text file.
 *
 */


/* according to the format of input board text file */
#define FILE_NUMBERS_IN_FIRST_LINE  2
#define FILE_FIXED_CELL_CHAR  '.'


/* load a board stored as text file to memory
 *
 * filePath - string with the path to the text file
 * boardp - pointer to the 2D board containing the data
 * bw - box width
 * bh - box height
 */
int loadBoardFromFile(char* filePath, BoardCell**** boardp, int* bwp, int* hwp);


/* save given board as text file
 *
 * filePath - string with the path to the text file
 * board - the 2D board containing the data
 * bw - box width
 * bh - box height
 */
int saveBoardToFile(char* filePath, BoardCell*** board, int bw, int hw);


#endif /* _FILEIO_H_ */
