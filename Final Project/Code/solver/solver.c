#include "solver.h"


/* wrapping function for the board solver */
int solveBoard(BoardCell*** board, int boxW, int boxH) {

#ifdef SOLVER_BT
	int boardSize = boxW * boxH;
	return runBacktrack(board, boardSize, boardSize, boxW, boxH, DETERMINISTIC);
#else
	return runGurobiSolver(*board, boxW, boxH);
#endif /* SOLVER_BT */
	
}


int getNumOfSolutions(BoardCell*** board, int boxW, int boxH)
{
	int solsCounter = 0, boardW = boxW*boxH, boardH = boxW*boxH;
	BoardCell*** currBoard;
	StackNode tmpNode, *currNode, *nodeForDeletion;

	/* create the stack for recursion simulation */
    StackOfBoards* stack = createStack(boardW*boardH, boardW, boardH);

	/* copy the original board */
    currBoard = allocateBoard(boardW, boardH);
	copyBoard(currBoard, board, boardW, boardH);

	/* load the base board as the top of the stack */
	findFirstEmptyCellLoc(currBoard, boardW, boardH, &(tmpNode.x), &(tmpNode.y));
	tmpNode.v = 0;
	push(stack, tmpNode);
	
	/* find solutions as long as the stack is not empty */
	while ( !isEmpty(stack) ) {
		currNode = top(stack);
		/*printf("stack size: %d\n", getStackSize(stack) );
		printf("*current cell: (%d, %d) = %d\n", (currNode->x)+1, (currNode->y)+1, currNode->v);
		printBoard(*(currBoard), boxW, boxH, FALSE, FALSE );*/

		/* as long as there is a possible number to put in the cell... */
		while ( currNode->v <= boardW ) {
			/* advance the value in the cell */
			currNode->v++;
			currBoard[currNode->y][currNode->x]->val = currNode->v;

			/* if cell value is valid, continue solving with it */
			if ( validateCellByLoc(currBoard, currNode->x, currNode->y, boardW, boardH, boxW, boxH) ) {
				/*printf("		found valid val for cell: %d \n", currBoard[currNode->y][currNode->x]->val);*/
				break;
			}
		}

		/* if we checked all possible values, pop the node */
		if ( boardW < currNode->v ) {
			/*printf("		out of valid size, popping... \n");*/
			nodeForDeletion = pop(stack);
			/* reset the cell value in the board */
			currBoard[nodeForDeletion->y][nodeForDeletion->x]->val = 0;
			continue;
		}

		/* check if the board is filled and valid */
		if ( isBoardFilled(currBoard, boardW, boardH) ) {
			if (isFilledBoardValid(currBoard, boardW, boardH, boxW, boxH) ) {
				/*printf("		board is correct. adding solution. currSols: %d \n", solsCounter);*/
				solsCounter++;
			}
			/*printf("		popping... \n");*/
			nodeForDeletion = pop(stack);

			/* reset the cell value in the board */
			currBoard[nodeForDeletion->y][nodeForDeletion->x]->val = 0;

		/* board is not filled yet */
		} else {
			/* create new stack node for the next empty cell */
			findFirstEmptyCellLoc(currBoard, boardW, boardH, &(tmpNode.x), &(tmpNode.y));
			tmpNode.v = 0;
			push(stack, tmpNode);
			/*printf("		board is not filled yet. pushing next node in loc: (%d, %d)\n", currNode->x, currNode->y);*/
		}
	}

	freeStack(stack);
	freeBoard(currBoard, boardW, boardH);
	return solsCounter;
}




/* used for testing purposes, not used in the final version!!! */
int runBacktrack(BoardCell*** board, int boardW, int boardH, int boxW, int boxH, BackTrackMode btMode) {
	return recBackTrack(board, 0, 0, boardW, boardH, boxW, boxH, btMode);
}

/* used for testing purposes, not used in the final version!!! */
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

	/*
	printf("currCell: (%d, %d) val: %d isUserSet: %d isFixed: %d  | nextCell: (%d, %d)\n", x, y, board[y][x]->val, board[y][x]->isUserSet, board[y][x]->isFixed, nextX, nextY);
	printBoard(*board, boxW, boxH, TRUE);
	*/
	
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

			/* pick element from the array of values */
			if ( RANDOM == btMode && 1 < arrLen ) {
				/*printf("pick random between 0 to %d \n", arrLen-1);*/
				currCheckedIndex = getRandInt(arrLen-1);
			} else {
				currCheckedIndex = 0;
			}

			/* set cell value to chosen array value */
			(board[y][x])->val = validsArray[currCheckedIndex];

			/* continue backtrack from current cell */
			bcRes = recBackTrack(board, nextX, nextY, boardW, boardH, boxW, boxH, btMode);

			/* backtracking failed, remove value from array */
			if ( bcRes == FALSE ) {
				shrinkArray(validsArray, &arrLen, currCheckedIndex);
			} else {
			/* backtracking succeeded, free memory allocation and return 'TRUE' */
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




