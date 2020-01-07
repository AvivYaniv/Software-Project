#include "solver.h"


int runBacktrack(BoardCell*** board, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode) {
	return recBackTrack(board, 0, 0, boardW, boardH, boxW, boxH, btMode);
}


int recBackTrack(BoardCell*** board, int x, int y, 
				int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode) {

	int nextX, nextY;
	int bcRes;
	int currCheckedIndex;

	/* create array */
	const int INITIAL_ARRAY_LENGTH = boardW;
	int arrLen = INITIAL_ARRAY_LENGTH;
	int* validsArray;
	calcNextCell(x, y, &nextX, &nextY, boardW, boardH);

	/* if backtrack reached the last cell in the board, it is a valid board */
	if ( 0 == x && boardH == y ) {
		return TRUE;
	}

	if ( board[y][x]->isFixed || board[y][x]->isUserSet || 0 != board[y][x]->val ) {
		/*printf("cell has value. move to next cell\n");*/
		return recBackTrack(board, nextX, nextY, boardW, boardH, boxW, boxH, btMode);

	} else {
		/*printf("cell has NO value. building valids array...\n");*/

		/* put all possible values in array */
		validsArray = (int*) malloc(INITIAL_ARRAY_LENGTH * sizeof(int));
		putSeqValuesInArr(validsArray, arrLen);
		
		/* filter non-valid values */
		removeInvalidArrValues(board, x, y, validsArray, &arrLen, boardW, boardH, boxW, boxH);

		/* run next backtracks */
		while ( 0 < arrLen ) {

			if ( RANDOM == btMode && 1 < arrLen ) {
				/*printf("pick random between 0 to %d \n", arrLen-1);*/
				currCheckedIndex = getRandInt(arrLen-1);
			} else {
				currCheckedIndex = 0;
			}

			(board[y][x])->val = validsArray[currCheckedIndex];

			bcRes = recBackTrack(board, nextX, nextY, boardW, boardH, boxW, boxH, btMode);

			if ( bcRes == FALSE ) {
				shrinkArray(validsArray, &arrLen, currCheckedIndex);
			} else {
				free(validsArray);
				return TRUE;
			}

		}

		/* reset the cell for future backtracks */
		(board[y][x])->val = 0;
		free(validsArray);
		return FALSE;		
	}

	/* unreachable code - written only so the compiler pass */
	return FALSE;		
}




