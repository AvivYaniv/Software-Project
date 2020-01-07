#ifndef _BOARD_ENTITIES_H_
#define _BOARD_ENTITIES_H_

#include <math.h>
#include <stdio.h>


/*
	boardEntities 
		This module contains the basic entities and structs for the sudoku board game
*/


#define	TRUE	1
#define	FALSE	0


/*
 * cell 'object' containing cell's value and who set it's value
 */
typedef struct boardCell_t
{
	int val; /* holds the value that is stored in the cell. 0 means the cell is blank. */
	int isUserSet; /* TRUE if the cell value was set by the user */
	int isFixed; /* TRUE if the cell is fixed */
	int isError; /* TRUE if the cell is erroneus */
	int isChanged; /* TRUE if the cell was changed by the last operation. For undo/redo commands */
} BoardCell;


#endif /*_BOARD_ENTITIES_H_*/
