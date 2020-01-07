#ifndef _BOARD_ENTITIES_H_
#define _BOARD_ENTITIES_H_

#include <math.h>
#include <stdio.h>


/*
	boardEntities 
		This module contains the basic entities and strucst for the sudoku board game
*/

#define	TRUE	1
#define	FALSE	0


typedef struct boardCell_t
{
	int val;
	int isUserSet;
	int isFixed;
} BoardCell;




#endif /*_BOARD_ENTITIES_H_*/
