#include "boardUtils.h"



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

/*
	int sizeX = (int)sqrt((double)board_width);
	int sizeY = (int)sqrt((double)board_width);
*/
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
/*
	printf("(%d, %d)=%d is valid? row: %d, col: %d, box: %d\n", x, y, n,
		validateCellRowByLoc(board, x, y, board_width),
		validateCellColByLoc(board, x, y, board_height),
		validateCellBoxByLoc(board, x, y, board_width));
*/
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

/*
	int size = (int)sqrt((double)board_width);
*/
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
	int r = rand() % (x+1);
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


int isFilledBoardValid(BoardCell*** board, int boardW, int boardH, int boxW, int boxH) {
	int x, y;
	
	if (NULL == board)
	{
		printf("isBoardFilled(): Game board null reference.\n");
		return FALSE;
	}			

	for ( y = 0 ; y < boardH ; y++ ) {
		for ( x = 0 ; x < boardW ; x++ ) {
			if ( FALSE == validateCellByLoc(board, x, y, boardW, boardH, boxW, boxH) ) {
				printf("board not valid: %d %d\n", x, y);
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
			(board[y][x])->isFixed = TRUE;
		}
	}
}

BoardCell*** allocateBoard(int board_width, int board_height) {
	int x, y;
	BoardCell* cell;

	/* allocate column */
	BoardCell*** board = malloc(sizeof(BoardCell*) * board_height);
	
	if (NULL == board)
	{
		printf("Game board allocation error\n");
		exit(0);
	}			
	
	/* allocate rows */
	for ( x = 0 ; x < board_height ; x++ ) {
		board[x] = (BoardCell**) malloc(sizeof(BoardCell*) * board_width);
		if (NULL == board[x]) {
			printf("Game board allocation error\n\n");
			exit(0);
		}
	}	

	/* allocate cells */
	for ( y = 0 ; y < board_height ; y++ ) {
		for ( x = 0 ; x < board_width ; x++ ) {

			cell = (BoardCell*) malloc( sizeof(BoardCell) );

			if (NULL == cell) {
				printf("allocateBoard(): malloc has failed\n");
				exit(0);
			}

			cell->val = 0;
			cell->isFixed = FALSE;
			cell->isUserSet = FALSE;

			board[y][x] = cell;
		}	
	}

	return board;
}

void freeBoard(BoardCell*** board, int board_width, int board_height) {
	int x, y;

	for ( y = 0 ; y < board_height ; y++ ) {
		for ( x = 0 ; x < board_width ; x++ ) {
			free(board[y][x]);
		}	
	}	
	
	for ( y = 0 ; y < board_height ; y++ ) {
		free(board[y]);
	}	
	
	free(board);
}

void hideCellsInBoard(BoardCell*** board, int w, int h, int cellsToShow) {
	int i = 0;
	int x, y;

	if (NULL == board)
	{
		printf("hideCellsInBoard(): Game board null reference.\n");
		return;
	}

	/* mark cells randomly for deletion */
	while ( i < cellsToShow ) {
		x = getRandInt(w-1);
		y = getRandInt(h-1);

		if ( FALSE == (board[y][x])->isFixed ) {
			(board[y][x])->isFixed = TRUE;
			i++;
		}
	}

	/* clear non-fixed cells */
	for ( y = 0 ; y < h ; y++ ) {
		for ( x = 0 ; x < w ; x++ ) {

			if (NULL == board[y][x]) {
				printf("hideCellsInBoard(): null cell reference \n");
				exit(0);
			}

			if ( FALSE == (board[y][x])->isFixed ) {
				(board[y][x])->val = 0;
				(board[y][x])->isUserSet = FALSE;
			} 
		}	
	}

}


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
			(dst[y][x])->val = 			(src[y][x])->val;
			(dst[y][x])->isUserSet = 	(src[y][x])->isUserSet;
			(dst[y][x])->isFixed = 		(src[y][x])->isFixed;		
		}
	}
}



/* print the board to console */
void printBoard(BoardCell*** board, int board_width, int board_height) {
	int i, j;
	BoardCell* cell;

	printf("----------------------------------\n");
	for ( i = 0 ; i < board_height ; i++ ) {
		printf("|");
		for ( j = 0 ; j < board_width ; j++ ) {


			if (NULL == board[i] || NULL == board[i][j]) {
				printf("printBoard error: NULL == board[%d][%d]\n", i, j);
				exit(0);
			}
			
			cell = board[i][j];

			if ( TRUE == cell->isFixed ) {
				printf(" .");
			} else {
				printf("  ");
			}

			if ( 0 == cell->val ) {
				printf(" ");
			} else {
				printf("%d", cell->val);
			}

			if ( 2 == j%3 ) {
				printf(" |");
			} 

		}		
		printf("\n");
		if ( 2 == i%3 ) {
			printf("----------------------------------\n");
		} 

	}
}



void zerosBoard(BoardCell*** board, int board_width, int board_height) {
	int i, j;		
	for ( i = 0 ; i < board_height ; i++ ) {
		for ( j = 0 ; j < board_width ; j++ ) {
			(board[i][j])->val = 0; (board[i][j])->isFixed = FALSE; (board[i][j])->isUserSet = FALSE; 
		}
	}	
}



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
	/*(board[0][1])->val = 3; (board[0][1])->isFixed = TRUE; (board[0][1])->isUserSet = FALSE; */
	(board[0][2])->val = 0; (board[0][2])->isFixed = FALSE; (board[0][2])->isUserSet = FALSE; 
	/*(board[0][2])->val = 5; (board[0][2])->isFixed = TRUE; (board[0][2])->isUserSet = FALSE; */
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
