#include "boardUtils.h"


int countEmptyCells(BoardCell*** board, int boardW, int boardH)
{
	int x = 0, y = 0, emptyCnt = 0;
	for ( y = 0 ; y < boardH ; y++ ) {
		for ( x = 0 ; x < boardW ; x++ ) {
			if ( 0 == board[y][x]->val ) {
				emptyCnt++;
			}
		}
	}
	return emptyCnt;
}


void printUndoChanges(BoardCell*** current, BoardCell*** prev, int w, int h) {
	int x, y;

	/* check all cells in the boards */
	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {

			/* if boards differ by the value of current cell */
			if ( current[y][x]->isChanged ) {

				/* print message for each different cell */
				printf("Undo ");

				printf("%d,%d: from ", x+1, y+1);

				if ( 0 == current[y][x]->val ) {
					printf("_");
				} else {
					printf("%d", current[y][x]->val);
				}

				printf(" to ");
				
				if ( 0 == prev[y][x]->val ) {
					printf("_");
				} else {
					printf("%d", prev[y][x]->val);
				}
				
				printf("\n");
			}
		}
	}
}

void printRedoChanges(BoardCell*** current, BoardCell*** next, int w, int h) {
	int x, y;

	/* check all cells in the boards */
	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {

			/* if boards differ by the value of current cell */
			if ( next[y][x]->isChanged ) {

				/* print message for each different cell */
				printf("Redo ");

				printf("%d,%d: from ", x+1, y+1);

				if ( 0 == current[y][x]->val ) {
					printf("_");
				} else {
					printf("%d", current[y][x]->val);
				}

				printf(" to ");
				
				if ( 0 == next[y][x]->val ) {
					printf("_");
				} else {
					printf("%d", next[y][x]->val);
				}
				
				printf("\n");
			}
		}
	}
}



void findFirstEmptyCellLoc(BoardCell*** board, int boardW, int boardH, int* xArg, int* yArg)
{
	int x = 0, y = 0;
	for ( y = 0 ; y < boardH ; y++ ) {
		for ( x = 0 ; x < boardW ; x++ ) {
			if ( 0 == board[y][x]->val ) {
				*xArg = x;
				*yArg = y;
				return;
			}
		}
	}

	*xArg = 0;
	*yArg = 0;
}



int autofillCell(BoardCell*** board, int x, int y, int boxW, int boxH) {
	int size = boxW * boxH;
	int i;
	int possibleValCounter = 0;
	int lastPossibleVal = 0;

	if ( 0 != board[y][x]->val ) {
		return possibleValCounter;
	}	

	/* check all possible cell values */
	for ( i = 1 ; i <= size ; i++ ) {
		if ( validateCellByVal(board, x, y, i, size, size, boxW, boxH) ) {
			lastPossibleVal = i;
			possibleValCounter++;
		}
	}

	if ( 1 == possibleValCounter) {
		return lastPossibleVal;
	} else {
		return -1;
	}

}


int validateCellRowByLoc(BoardCell*** board, int x, int y, int board_width)
{
	int i;
	int cellVal = (board[y][x])->val;

	for ( i = 0 ; i < board_width ; i++ ) {
		if ( i != x && (board[y][i])->val == cellVal)
		{
			return FALSE;
		}
	}

	return TRUE;
}


int validateCellColByLoc(BoardCell*** board, int x, int y, int board_height)
{
	int j;
	int cellVal = (board[y][x])->val;

	for ( j = 0 ; j < board_height ; j++ ) {
		if ( j != y && (board[j][x])->val == cellVal)
		{
			return FALSE;
		}
	}

	return TRUE;
}


int validateCellBoxByLoc(BoardCell*** board, int x, int y, int boxW, int boxH)
{
	int i, j;
	int cellVal = (board[y][x])->val;

	int k = boxW * (x / boxW);
	int l = boxH * (y / boxH);

	for ( i=k ; i < k + boxW ; i++ ) {
		for ( j = l ; j < l + boxH ; j++ ) {
			if ( i != x && j != y && (board[j][i])->val == cellVal)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}




/* return TRUE iff n is not in row y, column x, and box contaning x,y*/
int validateCellByLoc(BoardCell*** board, int x, int y, int board_width, int board_height, int boxW, int boxH)
{
	if ( !( 0 != (board[y][x])->val &&
			validateCellRowByLoc(board, x, y, board_width) &&
			validateCellColByLoc(board, x, y, board_height) &&
			validateCellBoxByLoc(board, x, y, boxW, boxH) ) ) {
		
		return FALSE;
	}

	return TRUE;
}




int validateRowByVal(BoardCell*** board, int y, int n, int board_width)
{
	int i;

	for ( i = 0 ; i < board_width ; i++ ) {
		if ((board[y][i])->val == n)
		{
			return FALSE;
		}
	}

	return TRUE;
}


int validateColByVal(BoardCell*** board, int x, int n, int board_height)
{
	int j;

	for ( j = 0 ; j < board_height ; j++ ) {
		if ((board[j][x])->val == n)
		{
			return FALSE;
		}
	}

	return TRUE;
}

int validateBoxByVal(BoardCell*** board, int x, int y, int n, int boxW, int boxH)
{
	int i;
	int j;

	int k = boxW * (x / boxW);
	int l = boxH * (y / boxH);


	for ( i=k ; i < k + boxW ; i++ ) {
		for ( j = l ; j < l + boxH ; j++ ) {
			if ((board[j][i])->val == n)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}


int validateCellByVal(BoardCell*** board, int x, int y, int n, int board_width, int board_height, int boxW, int boxH)
{

	if ( !( 0 != n &&
			validateRowByVal(board, y, n, board_width) &&
			validateColByVal(board, x, n, board_height) &&
			validateBoxByVal(board, x, y, n, boxW, boxH) ) ) {
		
		return FALSE;
	}

	return TRUE;
}



int markErrorsInBoard(BoardCell*** board, int boxW, int boxH) {
	int x, y;
	int boardW = boxW * boxH;
	int boardH = boxW * boxH;
	int numOfErrors = 0;

	for ( y = 0 ; y < boardH ; y++ ) {
		for ( x = 0 ; x < boardW ; x++ ) {
			if (0 != board[y][x]->val) {
				board[y][x]->isError = 	(!validateCellByLoc(board, x, y, boardW, boardH, boxW, boxH)) ||
										( 0 > board[y][x]->val ) || ( boardW < board[y][x]->val );

				if (board[y][x]->isError) {
					numOfErrors++;
				} 
			} else {
				board[y][x]->isError = FALSE;
			}
		}
	}

	return numOfErrors;
}



void shrinkArray(int* arr, int *arrayLen, int removedElemIndex) {
    int i;
    for ( i = removedElemIndex ; i < *arrayLen - 1 ; i++ ) {
        arr[i]=arr[i+1];
    }
    arr[ *arrayLen - 1 ] = 0;
    *arrayLen -= 1;
}




int calcNextCell(int x, int y, int *nx, int *ny, int w, int h) {
	*ny = y;
	*nx = x + 1;
	if (w == *nx) {
		*nx = 0;
		*ny += 1;
	}	

	if (h == *ny) {
		return FALSE;
	}

	return TRUE;
}


void printArr(int* arr, int len) {
    int i;
    for (i = 0 ; i < len ; i++ ) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}


void removeInvalidArrValues(BoardCell*** board, int x, int y, int* validsArray, int* arrLen, int boardW, int boardH, int boxW, int boxH) {
	int arrInitialLen = *arrLen;
	int arrIndex = 0;
	int i;
	for ( i = 0 ; i < arrInitialLen ; i++ ) {
		if ( !validateCellByVal(board, x, y, validsArray[arrIndex], boardW, boardH, boxW, boxH) ) {
			shrinkArray(validsArray, arrLen, arrIndex);
		} else {
			arrIndex++;
		}
	}
}


void putSeqValuesInArr(int* arr, int arrLen) {
	int i;
	for ( i = 0 ; i < arrLen ; i++ ) {
		arr[i] = i+1;
	}
}


int getRandInt(int x) {
	int r = ( (x+1) > 0 ? (rand() % (x+1)) : 0);
	/* printf("getRandInt was called. num: %d \n", r);*/
	return r;
}



int isBoardFilled(BoardCell*** board, int w, int h) {
	int x, y;
	
	if (NULL == board)
	{
		printf("isBoardFilled(): Game board null reference.\n");
		return FALSE;
	}			
	
	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {
			if ( 0 == (board[y][x])->val ) {
				return FALSE;
			}
		}	
	}	

	return TRUE;
}


int isBoardEmpty(BoardCell*** board, int w, int h) {
	int x, y;
	
	if (NULL == board)
	{
		printf("isBoardFilled(): Game board null reference.\n");
		return FALSE;
	}			
	
	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {
			if ( 0 != (board[y][x])->val ) {
				return FALSE;
			}
		}	
	}	

	return TRUE;
}


int isFilledBoardValid(BoardCell*** board, int boardW, int boardH, int boxW, int boxH) {
	int x, y;
	
	if (NULL == board)
	{
		printf("isBoardFilled(): Game board null reference.\n");
		return FALSE;
	}			

	for ( y = 0 ; y < boardH ; y++ ) {
		for ( x = 0 ; x < boardW ; x++ ) {
			/* check that the cell contain valid value and that it is valid in the board */
			if ( ( 1 > board[y][x]->val ) || ( board[y][x]->val > boardW ) || 
				(FALSE == validateCellByLoc(board, x, y, boardW, boardH, boxW, boxH)) ) {
				/*printf("board not valid: %d %d\n", x, y);*/
				return FALSE;
			}
		}	
	}	

	return TRUE;
}


void makeBoardCellsFixed(BoardCell*** board, int w, int h) {
	int x, y;

	if (NULL == board)
	{
		printf("makeBoardCellsFixed(): Game board null reference.\n");
		return;
	}			

	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {
			(board[y][x])->isFixed = ( 0 != (board[y][x])->val );
		}
	}
}

void makeBoardCellsUnfixed(BoardCell*** board, int w, int h) {
	int x, y;

	if (NULL == board)
	{
		printf("makeBoardCellsUnfixed(): Game board null reference.\n");
		return;
	}			

	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {
			(board[y][x])->isFixed = FALSE;
		}
	}
}



BoardCell*** allocateBoard(int board_width, int board_height) {
	int i;
	BoardCell* cell;
	BoardCell** contBoard;

	/* allocate the 2D board */
	BoardCell*** board = (BoardCell***)malloc(sizeof(BoardCell**) * board_height);
	
	if (NULL == board)
	{
		printf("Game board allocation error\n");
		exit(0);
	}			

	/* allocate contigious space for the board */
	contBoard = (BoardCell**)malloc(sizeof(BoardCell*) * board_width * board_height);
	
	if (NULL == contBoard)
	{
		printf("Game board allocation error\n");
		exit(0);
	}			

	/* point 2D board rows to contigious board rows */
	for ( i = 0 ; i < board_height ; i++ ) {
		board[i] = contBoard + i*board_width;
	}

	/* allocate cells */
	for ( i = 0 ; i < board_width*board_height ; i++ ) {

		cell = (BoardCell*) malloc( sizeof(BoardCell) );

		if (NULL == cell) {
			printf("allocateBoard(): malloc has failed\n");
			exit(0);
		}

		cell->val = 0;
		cell->isFixed = FALSE;
		cell->isUserSet = FALSE;
		cell->isError = FALSE;
		cell->isChanged = FALSE;

		contBoard[i] = cell;
	}

    /*printf("allocBoard: %p\n", (void*)(board));*/

	return board;
}

void freeBoard(BoardCell*** board, int board_width, int board_height) {
	int x, y;

	if (NULL == board) {
		return;
	}

    /*printf("freeBoard: %p\n", (void*)(board));*/

	for ( y = 0 ; y < board_height ; y++ ) {
		for ( x = 0 ; x < board_width ; x++ ) {
			if (NULL != board[y] && NULL != board[y][x]) {
				free(board[y][x]);
			}
		}	
	}	
	
	if (NULL != *board) {
		free(*board);
	}

	/*
	for ( y = 0 ; y < board_height ; y++ ) {
		free(board[y]);
	}	
	*/

	free(board);
}

/*
 * inv: board is filled with values
 * 		0 <= cellsToHide <= w*h
*/
void hideCellsInBoard(BoardCell*** board, int w, int h, int cellsToHide) {
	int i, x, y, randCellPos;
	int nonBlankCellsCounter = w*h;

	if (NULL == board)
	{
		printf("hideCellsInBoard(): Game board null reference.\n");
		return;
	}

	/* while there are still cells needed to be hidden */
	while ( 0 < cellsToHide ) {
		/* pick random cell index [1 .. w*h] */
		randCellPos = 1 + getRandInt(nonBlankCellsCounter-1);
		/*printf("non-blank pos: %d \n", randCellPos);*/

		/* get the i-th non-blank cell from top-right corner */
		for ( i = 0 ; i < w*h ; i++ ) {
			x = i % w;
			y = i / h;

			/* non-blank cell, so decrease the remaining cells to traverse */
			if ( 0 != (board[y][x])->val ) {
				randCellPos--;
			}

			/* we arrived at the cell needed to be hidden! (i.e no more remaining non-blank cells) */
			if ( 0 == randCellPos ) {
				/*printf("hide cell (%d, %d)\n", x+1, y+1);*/
				(board[y][x])->val = 0;
				(board[y][x])->isFixed = FALSE;
				(board[y][x])->isUserSet = FALSE;
				break;
			}
		}

		/* decrease the non blank cells counter */
		nonBlankCellsCounter--;

		/* decrease cells to hide counter */
		cellsToHide--;
	}

}
/*
void hideCellsInBoard(BoardCell*** board, int w, int h, int cellsToHide) {
	int i = 0;
	int x, y;

	if (NULL == board)
	{
		printf("hideCellsInBoard(): Game board null reference.\n");
		return;
	}

	while ( i < cellsToHide ) {
		x = getRandInt(w-1);
		y = getRandInt(h-1);

		if ( 0 != (board[y][x])->val ) {
			(board[y][x])->val = 0;
			(board[y][x])->isFixed = FALSE;
			(board[y][x])->isUserSet = FALSE;
			i++;
		}
	}
}
*/

void copyBoard(BoardCell*** dst, BoardCell*** src, int w, int h) {
	int x, y;

	if (NULL == dst) {
		printf("copyBoard(): dst board null reference.\n");
		return;
	} else if (NULL == src) {
		printf("copyBoard(): src board null reference.\n");
		return;
	}

	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {
			(dst[y][x])->val		 = (src[y][x])->val;
			(dst[y][x])->isUserSet	 = (src[y][x])->isUserSet;
			(dst[y][x])->isFixed	 = (src[y][x])->isFixed;		
			(dst[y][x])->isError	 = (src[y][x])->isError;		
			(dst[y][x])->isChanged	 = (src[y][x])->isChanged;		
		}
	}
}



/* print the board to console - for final project */
void printBoard(BoardCell** board, int box_width, int box_height, int isMarkFixed, int isMarkErrors) {
	int i = box_width;
	BoardCell* cell;
	int board_width = box_width*box_height;

	printSepLine(board_width, box_height);

	for ( i = 0 ; i < board_width*board_width ; i++ ) {

		if ( 0 == i%board_width ) {
			printf("|");
		} 

		if (NULL == board[i]) {
			printf("printBoard error: NULL == board[%d]\n", i);
			exit(0);
		}
			
		cell = board[i];

		printf(" ");

		if ( 0 == cell->val ) {
			printf("  ");
		} else {
			printf("%2d", cell->val);
		}

		if ( TRUE == cell->isFixed && isMarkFixed) {
			printf(".");
		} else if ( TRUE == cell->isError && isMarkErrors ) {
			printf("*");
		} else {
			printf(" ");
		}

		/* last pipe in the box */
		if ( (box_width-1) == i%box_width ) {
			printf("|");
		} 

		/* start a new row */
		if ( (board_width-1) == i%board_width ) {
			printf("\n");
		} 

		/* start a new box */
		if ( ((box_height*board_width)-1) == i%(box_height*board_width) ) {
			printSepLine(board_width, box_height);
		} 

	}

}


/* print the board to console with 'C' where the cell was changed by the previous command - for testing */
void printBoardIsChangedField(BoardCell** board, int box_width, int box_height) {
	int i = box_width;
	BoardCell* cell;
	int board_width = box_width*box_height;

	printSepLine(board_width, box_height);

	for ( i = 0 ; i < board_width*board_width ; i++ ) {

		if ( 0 == i%board_width ) {
			printf("|");
		} 

		if (NULL == board[i]) {
			printf("printBoard error: NULL == board[%d]\n", i);
			exit(0);
		}
			
		cell = board[i];

		printf(" ");

		if ( cell->isChanged ) {
			printf(" C");
		} else {
			printf("  ");
		}

		printf(" ");

		/* last pipe in the box */
		if ( (box_width-1) == i%box_width ) {
			printf("|");
		} 

		/* start a new row */
		if ( (board_width-1) == i%board_width ) {
			printf("\n");
		} 

		/* start a new box */
		if ( ((box_height*board_width)-1) == i%(box_height*board_width) ) {
			printSepLine(board_width, box_height);
		} 

	}

}



/* print a line of '-' for the print board function */ 
void printSepLine(int N, int m) {
	int i;
	for ( i = 0 ; i < 4*N + m + 1 ; i++ ) {
		printf("-");
	}
	printf("\n");	
}


void zerosBoard(BoardCell*** board, int board_width, int board_height) {
	int i, j;		
	for ( i = 0 ; i < board_height ; i++ ) {
		for ( j = 0 ; j < board_width ; j++ ) {
			(board[i][j])->val = 0;
			(board[i][j])->isFixed = FALSE;
			(board[i][j])->isUserSet = FALSE; 
			(board[i][j])->isChanged = FALSE; 
		}
	}	
}


void setBoardChangedToFalse(BoardCell*** board, int board_width, int board_height) {
	int i, j;		
	for ( i = 0 ; i < board_height ; i++ ) {
		for ( j = 0 ; j < board_width ; j++ ) {
			(board[i][j])->isChanged = FALSE; 
		}
	}	
}

void setBoardNonBlankToChanged(BoardCell*** board, int board_width, int board_height) {
	int i, j;		
	for ( i = 0 ; i < board_height ; i++ ) {
		for ( j = 0 ; j < board_width ; j++ ) {
			if (0 != board[i][j]->val) {
				(board[i][j])->isChanged = TRUE; 
			} else {
				(board[i][j])->isChanged = FALSE; 
			}

		}
	}	
}



/*
void dummyBoard2(BoardCell*** board) {
	(board[0][0])->val = 0; (board[0][0])->isFixed = FALSE; (board[0][0])->isUserSet = FALSE; 
	(board[0][1])->val = 0; (board[0][1])->isFixed = FALSE; (board[0][1])->isUserSet = FALSE; 
	(board[0][2])->val = 0; (board[0][2])->isFixed = FALSE; (board[0][2])->isUserSet = FALSE; 
	(board[0][3])->val = 2; (board[0][3])->isFixed = TRUE; (board[0][3])->isUserSet = FALSE; 
	(board[0][4])->val = 6; (board[0][4])->isFixed = TRUE; (board[0][4])->isUserSet = FALSE; 
	(board[0][5])->val = 9; (board[0][5])->isFixed = TRUE; (board[0][5])->isUserSet = FALSE; 
	(board[0][6])->val = 0; (board[0][6])->isFixed = FALSE; (board[0][6])->isUserSet = FALSE; 
	(board[0][7])->val = 0; (board[0][7])->isFixed = FALSE; (board[0][7])->isUserSet = FALSE; 
	(board[0][8])->val = 0; (board[0][8])->isFixed = FALSE; (board[0][8])->isUserSet = FALSE; 

	(board[1][0])->val = 0; (board[1][0])->isFixed = FALSE; (board[1][0])->isUserSet = FALSE; 
	(board[1][1])->val = 0; (board[1][1])->isFixed = FALSE; (board[1][1])->isUserSet = FALSE; 
	(board[1][2])->val = 0; (board[1][2])->isFixed = FALSE; (board[1][2])->isUserSet = FALSE; 
	(board[1][3])->val = 5; (board[1][3])->isFixed = TRUE; (board[1][3])->isUserSet = FALSE; 
	(board[1][4])->val = 7; (board[1][4])->isFixed = TRUE; (board[1][4])->isUserSet = FALSE; 
	(board[1][5])->val = 1; (board[1][5])->isFixed = TRUE; (board[1][5])->isUserSet = FALSE; 
	(board[1][6])->val = 0; (board[1][6])->isFixed = FALSE; (board[1][6])->isUserSet = FALSE; 
	(board[1][7])->val = 0; (board[1][7])->isFixed = FALSE; (board[1][7])->isUserSet = FALSE; 
	(board[1][8])->val = 0; (board[1][8])->isFixed = FALSE; (board[1][8])->isUserSet = FALSE; 

	(board[2][0])->val = 0; (board[2][0])->isFixed = FALSE; (board[2][0])->isUserSet = FALSE; 
	(board[2][1])->val = 0; (board[2][1])->isFixed = FALSE; (board[2][1])->isUserSet = FALSE; 
	(board[2][2])->val = 0; (board[2][2])->isFixed = FALSE; (board[2][2])->isUserSet = FALSE; 
	(board[2][3])->val = 8; (board[2][3])->isFixed = TRUE; (board[2][3])->isUserSet = FALSE; 
	(board[2][4])->val = 3; (board[2][4])->isFixed = TRUE; (board[2][4])->isUserSet = FALSE; 
	(board[2][5])->val = 4; (board[2][5])->isFixed = TRUE; (board[2][5])->isUserSet = FALSE; 
	(board[2][6])->val = 5; (board[2][6])->isFixed = TRUE; (board[2][6])->isUserSet = FALSE; 
	(board[2][7])->val = 6; (board[2][7])->isFixed = TRUE; (board[2][7])->isUserSet = FALSE; 
	(board[2][8])->val = 2; (board[2][8])->isFixed = TRUE; (board[2][8])->isUserSet = FALSE; 

	(board[3][0])->val = 8; (board[3][0])->isFixed = TRUE; (board[3][0])->isUserSet = FALSE; 
	(board[3][1])->val = 2; (board[3][1])->isFixed = TRUE; (board[3][1])->isUserSet = FALSE; 
	(board[3][2])->val = 6; (board[3][2])->isFixed = TRUE; (board[3][2])->isUserSet = FALSE; 
	(board[3][3])->val = 1; (board[3][3])->isFixed = TRUE; (board[3][3])->isUserSet = FALSE; 
	(board[3][4])->val = 9; (board[3][4])->isFixed = TRUE; (board[3][4])->isUserSet = FALSE; 
	(board[3][5])->val = 5; (board[3][5])->isFixed = TRUE; (board[3][5])->isUserSet = FALSE; 
	(board[3][6])->val = 3; (board[3][6])->isFixed = TRUE; (board[3][6])->isUserSet = FALSE; 
	(board[3][7])->val = 4; (board[3][7])->isFixed = TRUE; (board[3][7])->isUserSet = FALSE; 
	(board[3][8])->val = 7; (board[3][8])->isFixed = TRUE; (board[3][8])->isUserSet = FALSE; 

	(board[4][0])->val = 3; (board[4][0])->isFixed = TRUE; (board[4][0])->isUserSet = FALSE; 
	(board[4][1])->val = 7; (board[4][1])->isFixed = TRUE; (board[4][1])->isUserSet = FALSE; 
	(board[4][2])->val = 4; (board[4][2])->isFixed = TRUE; (board[4][2])->isUserSet = FALSE; 
	(board[4][3])->val = 6; (board[4][3])->isFixed = TRUE; (board[4][3])->isUserSet = FALSE; 
	(board[4][4])->val = 8; (board[4][4])->isFixed = TRUE; (board[4][4])->isUserSet = FALSE; 
	(board[4][5])->val = 2; (board[4][5])->isFixed = TRUE; (board[4][5])->isUserSet = FALSE; 
	(board[4][6])->val = 9; (board[4][6])->isFixed = TRUE; (board[4][6])->isUserSet = FALSE; 
	(board[4][7])->val = 1; (board[4][7])->isFixed = TRUE; (board[4][7])->isUserSet = FALSE; 
	(board[4][8])->val = 5; (board[4][8])->isFixed = TRUE; (board[4][8])->isUserSet = FALSE; 

	(board[5][0])->val = 9; (board[5][0])->isFixed = TRUE; (board[5][0])->isUserSet = FALSE; 
	(board[5][1])->val = 5; (board[5][1])->isFixed = TRUE; (board[5][1])->isUserSet = FALSE; 
	(board[5][2])->val = 1; (board[5][2])->isFixed = TRUE; (board[5][2])->isUserSet = FALSE; 
	(board[5][3])->val = 7; (board[5][3])->isFixed = TRUE; (board[5][3])->isUserSet = FALSE; 
	(board[5][4])->val = 4; (board[5][4])->isFixed = TRUE; (board[5][4])->isUserSet = FALSE; 
	(board[5][5])->val = 3; (board[5][5])->isFixed = TRUE; (board[5][5])->isUserSet = FALSE; 
	(board[5][6])->val = 6; (board[5][6])->isFixed = TRUE; (board[5][6])->isUserSet = FALSE; 
	(board[5][7])->val = 2; (board[5][7])->isFixed = TRUE; (board[5][7])->isUserSet = FALSE; 
	(board[5][8])->val = 8; (board[5][8])->isFixed = TRUE; (board[5][8])->isUserSet = FALSE; 


	(board[6][0])->val = 5; (board[6][0])->isFixed = TRUE; (board[6][0])->isUserSet = FALSE; 
	(board[6][1])->val = 1; (board[6][1])->isFixed = TRUE; (board[6][1])->isUserSet = FALSE; 
	(board[6][2])->val = 9; (board[6][2])->isFixed = TRUE; (board[6][2])->isUserSet = FALSE; 
	(board[6][3])->val = 3; (board[6][3])->isFixed = TRUE; (board[6][3])->isUserSet = FALSE; 
	(board[6][4])->val = 2; (board[6][4])->isFixed = TRUE; (board[6][4])->isUserSet = FALSE; 
	(board[6][5])->val = 6; (board[6][5])->isFixed = TRUE; (board[6][5])->isUserSet = FALSE; 
	(board[6][6])->val = 0; (board[6][6])->isFixed = FALSE; (board[6][6])->isUserSet = FALSE; 
	(board[6][7])->val = 0; (board[6][7])->isFixed = FALSE; (board[6][7])->isUserSet = FALSE; 
	(board[6][8])->val = 0; (board[6][8])->isFixed = FALSE; (board[6][8])->isUserSet = FALSE; 

	(board[7][0])->val = 2; (board[7][0])->isFixed = TRUE; (board[7][0])->isUserSet = FALSE; 
	(board[7][1])->val = 4; (board[7][1])->isFixed = TRUE; (board[7][1])->isUserSet = FALSE; 
	(board[7][2])->val = 0; (board[7][2])->isFixed = FALSE; (board[7][2])->isUserSet = FALSE; 
	(board[7][3])->val = 0; (board[7][3])->isFixed = FALSE; (board[7][3])->isUserSet = FALSE; 
	(board[7][4])->val = 0; (board[7][4])->isFixed = FALSE; (board[7][4])->isUserSet = FALSE; 
	(board[7][5])->val = 0; (board[7][5])->isFixed = FALSE; (board[7][5])->isUserSet = FALSE; 
	(board[7][6])->val = 0; (board[7][6])->isFixed = FALSE; (board[7][6])->isUserSet = FALSE; 
	(board[7][7])->val = 0; (board[7][7])->isFixed = FALSE; (board[7][7])->isUserSet = FALSE; 
	(board[7][8])->val = 0; (board[7][8])->isFixed = FALSE; (board[7][8])->isUserSet = FALSE; 

	(board[8][0])->val = 0; (board[8][0])->isFixed = FALSE; (board[8][0])->isUserSet = FALSE; 
	(board[8][1])->val = 0; (board[8][1])->isFixed = FALSE; (board[8][1])->isUserSet = FALSE; 
	(board[8][2])->val = 0; (board[8][2])->isFixed = FALSE; (board[8][2])->isUserSet = FALSE; 
	(board[8][3])->val = 0; (board[8][3])->isFixed = FALSE; (board[8][3])->isUserSet = FALSE; 
	(board[8][4])->val = 0; (board[8][4])->isFixed = FALSE; (board[8][4])->isUserSet = FALSE; 
	(board[8][5])->val = 0; (board[8][5])->isFixed = FALSE; (board[8][5])->isUserSet = FALSE; 
	(board[8][6])->val = 0; (board[8][6])->isFixed = FALSE; (board[8][6])->isUserSet = FALSE; 
	(board[8][7])->val = 0; (board[8][7])->isFixed = FALSE; (board[8][7])->isUserSet = FALSE; 
	(board[8][8])->val = 9; (board[8][8])->isFixed = FALSE; (board[8][8])->isUserSet = TRUE; 
	
}

void dummyBoard3(BoardCell*** board) {
	(board[0][0])->val = 4; (board[0][0])->isFixed = TRUE; (board[0][0])->isUserSet = FALSE; 
	(board[0][1])->val = 0; (board[0][1])->isFixed = FALSE; (board[0][1])->isUserSet = FALSE; 
	(board[0][2])->val = 0; (board[0][2])->isFixed = FALSE; (board[0][2])->isUserSet = FALSE; 
	(board[0][3])->val = 2; (board[0][3])->isFixed = TRUE; (board[0][3])->isUserSet = FALSE; 
	(board[0][4])->val = 6; (board[0][4])->isFixed = TRUE; (board[0][4])->isUserSet = FALSE; 
	(board[0][5])->val = 9; (board[0][5])->isFixed = TRUE; (board[0][5])->isUserSet = FALSE; 
	(board[0][6])->val = 7; (board[0][6])->isFixed = TRUE; (board[0][6])->isUserSet = FALSE; 
	(board[0][7])->val = 8; (board[0][7])->isFixed = TRUE; (board[0][7])->isUserSet = FALSE; 
	(board[0][8])->val = 1; (board[0][8])->isFixed = TRUE; (board[0][8])->isUserSet = FALSE; 

	(board[1][0])->val = 6; (board[1][0])->isFixed = TRUE; (board[1][0])->isUserSet = FALSE; 
	(board[1][1])->val = 8; (board[1][1])->isFixed = TRUE; (board[1][1])->isUserSet = FALSE; 
	(board[1][2])->val = 2; (board[1][2])->isFixed = TRUE; (board[1][2])->isUserSet = FALSE; 
	(board[1][3])->val = 5; (board[1][3])->isFixed = TRUE; (board[1][3])->isUserSet = FALSE; 
	(board[1][4])->val = 7; (board[1][4])->isFixed = TRUE; (board[1][4])->isUserSet = FALSE; 
	(board[1][5])->val = 1; (board[1][5])->isFixed = TRUE; (board[1][5])->isUserSet = FALSE; 
	(board[1][6])->val = 4; (board[1][6])->isFixed = TRUE; (board[1][6])->isUserSet = FALSE; 
	(board[1][7])->val = 9; (board[1][7])->isFixed = TRUE; (board[1][7])->isUserSet = FALSE; 
	(board[1][8])->val = 3; (board[1][8])->isFixed = TRUE; (board[1][8])->isUserSet = FALSE; 

	(board[2][0])->val = 1; (board[2][0])->isFixed = TRUE; (board[2][0])->isUserSet = FALSE; 
	(board[2][1])->val = 9; (board[2][1])->isFixed = TRUE; (board[2][1])->isUserSet = FALSE; 
	(board[2][2])->val = 7; (board[2][2])->isFixed = TRUE; (board[2][2])->isUserSet = FALSE; 
	(board[2][3])->val = 8; (board[2][3])->isFixed = TRUE; (board[2][3])->isUserSet = FALSE; 
	(board[2][4])->val = 3; (board[2][4])->isFixed = TRUE; (board[2][4])->isUserSet = FALSE; 
	(board[2][5])->val = 4; (board[2][5])->isFixed = TRUE; (board[2][5])->isUserSet = FALSE; 
	(board[2][6])->val = 5; (board[2][6])->isFixed = TRUE; (board[2][6])->isUserSet = FALSE; 
	(board[2][7])->val = 6; (board[2][7])->isFixed = TRUE; (board[2][7])->isUserSet = FALSE; 
	(board[2][8])->val = 2; (board[2][8])->isFixed = TRUE; (board[2][8])->isUserSet = FALSE; 

	(board[3][0])->val = 8; (board[3][0])->isFixed = TRUE; (board[3][0])->isUserSet = FALSE; 
	(board[3][1])->val = 2; (board[3][1])->isFixed = TRUE; (board[3][1])->isUserSet = FALSE; 
	(board[3][2])->val = 6; (board[3][2])->isFixed = TRUE; (board[3][2])->isUserSet = FALSE; 
	(board[3][3])->val = 1; (board[3][3])->isFixed = TRUE; (board[3][3])->isUserSet = FALSE; 
	(board[3][4])->val = 9; (board[3][4])->isFixed = TRUE; (board[3][4])->isUserSet = FALSE; 
	(board[3][5])->val = 5; (board[3][5])->isFixed = TRUE; (board[3][5])->isUserSet = FALSE; 
	(board[3][6])->val = 3; (board[3][6])->isFixed = TRUE; (board[3][6])->isUserSet = FALSE; 
	(board[3][7])->val = 4; (board[3][7])->isFixed = TRUE; (board[3][7])->isUserSet = FALSE; 
	(board[3][8])->val = 7; (board[3][8])->isFixed = TRUE; (board[3][8])->isUserSet = FALSE; 

	(board[4][0])->val = 3; (board[4][0])->isFixed = TRUE; (board[4][0])->isUserSet = FALSE; 
	(board[4][1])->val = 7; (board[4][1])->isFixed = TRUE; (board[4][1])->isUserSet = FALSE; 
	(board[4][2])->val = 4; (board[4][2])->isFixed = TRUE; (board[4][2])->isUserSet = FALSE; 
	(board[4][3])->val = 6; (board[4][3])->isFixed = TRUE; (board[4][3])->isUserSet = FALSE; 
	(board[4][4])->val = 8; (board[4][4])->isFixed = TRUE; (board[4][4])->isUserSet = FALSE; 
	(board[4][5])->val = 2; (board[4][5])->isFixed = TRUE; (board[4][5])->isUserSet = FALSE; 
	(board[4][6])->val = 9; (board[4][6])->isFixed = TRUE; (board[4][6])->isUserSet = FALSE; 
	(board[4][7])->val = 1; (board[4][7])->isFixed = TRUE; (board[4][7])->isUserSet = FALSE; 
	(board[4][8])->val = 5; (board[4][8])->isFixed = TRUE; (board[4][8])->isUserSet = FALSE; 

	(board[5][0])->val = 9; (board[5][0])->isFixed = TRUE; (board[5][0])->isUserSet = FALSE; 
	(board[5][1])->val = 5; (board[5][1])->isFixed = TRUE; (board[5][1])->isUserSet = FALSE; 
	(board[5][2])->val = 1; (board[5][2])->isFixed = TRUE; (board[5][2])->isUserSet = FALSE; 
	(board[5][3])->val = 7; (board[5][3])->isFixed = TRUE; (board[5][3])->isUserSet = FALSE; 
	(board[5][4])->val = 4; (board[5][4])->isFixed = TRUE; (board[5][4])->isUserSet = FALSE; 
	(board[5][5])->val = 3; (board[5][5])->isFixed = TRUE; (board[5][5])->isUserSet = FALSE; 
	(board[5][6])->val = 6; (board[5][6])->isFixed = TRUE; (board[5][6])->isUserSet = FALSE; 
	(board[5][7])->val = 2; (board[5][7])->isFixed = TRUE; (board[5][7])->isUserSet = FALSE; 
	(board[5][8])->val = 8; (board[5][8])->isFixed = TRUE; (board[5][8])->isUserSet = FALSE; 


	(board[6][0])->val = 5; (board[6][0])->isFixed = TRUE; (board[6][0])->isUserSet = FALSE; 
	(board[6][1])->val = 1; (board[6][1])->isFixed = TRUE; (board[6][1])->isUserSet = FALSE; 
	(board[6][2])->val = 9; (board[6][2])->isFixed = TRUE; (board[6][2])->isUserSet = FALSE; 
	(board[6][3])->val = 3; (board[6][3])->isFixed = TRUE; (board[6][3])->isUserSet = FALSE; 
	(board[6][4])->val = 2; (board[6][4])->isFixed = TRUE; (board[6][4])->isUserSet = FALSE; 
	(board[6][5])->val = 6; (board[6][5])->isFixed = TRUE; (board[6][5])->isUserSet = FALSE; 
	(board[6][6])->val = 8; (board[6][6])->isFixed = TRUE; (board[6][6])->isUserSet = FALSE; 
	(board[6][7])->val = 7; (board[6][7])->isFixed = TRUE; (board[6][7])->isUserSet = FALSE; 
	(board[6][8])->val = 4; (board[6][8])->isFixed = TRUE; (board[6][8])->isUserSet = FALSE; 

	(board[7][0])->val = 2; (board[7][0])->isFixed = TRUE; (board[7][0])->isUserSet = FALSE; 
	(board[7][1])->val = 4; (board[7][1])->isFixed = TRUE; (board[7][1])->isUserSet = FALSE; 
	(board[7][2])->val = 8; (board[7][2])->isFixed = TRUE; (board[7][2])->isUserSet = FALSE; 
	(board[7][3])->val = 9; (board[7][3])->isFixed = TRUE; (board[7][3])->isUserSet = FALSE; 
	(board[7][4])->val = 5; (board[7][4])->isFixed = TRUE; (board[7][4])->isUserSet = FALSE; 
	(board[7][5])->val = 7; (board[7][5])->isFixed = TRUE; (board[7][5])->isUserSet = FALSE; 
	(board[7][6])->val = 1; (board[7][6])->isFixed = TRUE; (board[7][6])->isUserSet = FALSE; 
	(board[7][7])->val = 3; (board[7][7])->isFixed = TRUE; (board[7][7])->isUserSet = FALSE; 
	(board[7][8])->val = 6; (board[7][8])->isFixed = TRUE; (board[7][8])->isUserSet = FALSE; 

	(board[8][0])->val = 7; (board[8][0])->isFixed = TRUE; (board[8][0])->isUserSet = FALSE; 
	(board[8][1])->val = 6; (board[8][1])->isFixed = TRUE; (board[8][1])->isUserSet = FALSE; 
	(board[8][2])->val = 3; (board[8][2])->isFixed = TRUE; (board[8][2])->isUserSet = FALSE; 
	(board[8][3])->val = 4; (board[8][3])->isFixed = TRUE; (board[8][3])->isUserSet = FALSE; 
	(board[8][4])->val = 1; (board[8][4])->isFixed = TRUE; (board[8][4])->isUserSet = FALSE; 
	(board[8][5])->val = 8; (board[8][5])->isFixed = TRUE; (board[8][5])->isUserSet = FALSE; 
	(board[8][6])->val = 2; (board[8][6])->isFixed = TRUE; (board[8][6])->isUserSet = FALSE; 
	(board[8][7])->val = 5; (board[8][7])->isFixed = TRUE; (board[8][7])->isUserSet = FALSE; 
	(board[8][8])->val = 9; (board[8][8])->isFixed = TRUE; (board[8][8])->isUserSet = FALSE; 
	
}
*/