#include "gameLogic.h"

void printInvalidCmdMsg() {
	printf("ERROR: invalid command\n");
}


/* Get command (input) from the user */
void promptUserCommand(Command *cmdPtr) {
	while ( TRUE ) {

		printf("Enter your command:\n");		

		if ( !getCommandFromUser(cmdPtr) ) {
			cmdPtr->commandType = COMMAND_EXIT;
			cmdPtr->argX = EOF_ENCOUNTERED;
		}
		
		if ( COMMAND_INVALID == cmdPtr->commandType ) {
			printInvalidCmdMsg();
		} else {
			break;		
		}
	}	
}

void checkIsBoardSolved(BoardCell*** board, int boxWidth, int boxHeight, GameStates *currGameModePtr) {
	int boardWidth = boxWidth*boxHeight; 
	int boardHeight = boxWidth*boxHeight; 

	/* check if game was completed */
	if ( GAME_SOLVE == *currGameModePtr ) {

		/* check if board is filled */
		if ( isBoardFilled(board, boardWidth, boardHeight) ) {

			/* check if board is valid */
			if ( isFilledBoardValid(board, boardWidth, boardHeight, boxWidth, boxHeight) ) {
				printf("Puzzle solved successfully\n");
				*currGameModePtr = GAME_INIT;

			} else {
				printf("Puzzle solution erroneous\n");
			}
		}			
	}
}


int runSudokuConsoleGame() {
	int isMarkErrors = TRUE, boxWidth = DEFAULT_BOX_SIZE, boxHeight = DEFAULT_BOX_SIZE, boardWidth = boxWidth*boxHeight, boardHeight = boxWidth*boxHeight;
	GameStates currGameMode = GAME_INIT;
	Command cmd;
    
	/* Doubly linked list for undo and redo */
    DLLNode *historyList = NULL, *historyListCursor = NULL;

	/* 2D boards */	
	BoardCell ***board = NULL, ***loadedBoard = NULL, ***solvedBoard = NULL;

	/* Code Section */
	printf("Sudoku\n------\n");

	/* game loop */
	while ( TRUE ) {
		resetCommand(&cmd);

		/* get command from user  */
		promptUserCommand(&cmd);

	/* solve command */
		if ( COMMAND_SOLVE == cmd.commandType ) {

			handleSolveCommand(	&currGameMode, cmd, &historyListCursor, 
								&historyList, isMarkErrors, &boardWidth, &boardHeight,
								&boxWidth, &boxHeight, &board, 
								&solvedBoard, &loadedBoard);

	/* edit command */
		} else if (COMMAND_EDIT == cmd.commandType ) { 

			handleEditCommand(	&currGameMode, cmd, &historyListCursor, 
								&historyList, isMarkErrors, &boardWidth, &boardHeight,
								&boxWidth, &boxHeight, &board, 
								&solvedBoard, &loadedBoard);

	/* mark_errors command */
		} else if (COMMAND_MARK_ERRORS == cmd.commandType ) { 

			handleMarkErrorsCommand(currGameMode, cmd, &isMarkErrors);

	/* print_board command */
		} else if (COMMAND_PRINT_BOARD == cmd.commandType ) { 

			handlePrintBoardCommand(	currGameMode, boxWidth, boxHeight, 
										isMarkErrors, board);

	/* set command */
		} else if (COMMAND_SET == cmd.commandType ) { 

			handleSetCommand(	currGameMode, cmd, &historyListCursor, 
								&historyList, boxWidth, boxHeight, isMarkErrors, board);

	/* validate command */
		} else if (COMMAND_VALIDATE == cmd.commandType ) { 

			handleValidateCommand(	currGameMode, boxWidth, boxHeight, 
									board, solvedBoard);;

	/* generate command */
		} else if (COMMAND_GENERATE == cmd.commandType ) { 

			handleGenerateCommand(	currGameMode, cmd, &historyListCursor, 
									&historyList, boxWidth, boxHeight, isMarkErrors, board, 
									solvedBoard);

	/* undo command */
		} else if (COMMAND_UNDO == cmd.commandType ) { 

			handleUndoCommand(	currGameMode, &historyListCursor,
								boxWidth, boxHeight, isMarkErrors, board);

	/* redo command */
		} else if (COMMAND_REDO == cmd.commandType ) { 

			handleRedoCommand(	currGameMode, &historyListCursor,
								boxWidth, boxHeight, isMarkErrors, board);

	/* save command */
		} else if (COMMAND_SAVE == cmd.commandType ) { 

			handleSaveCommand(	currGameMode, cmd, boxWidth, boxHeight, 
								board, solvedBoard);

	/* hint command */
		} else if (COMMAND_HINT == cmd.commandType ) { 

			handleHintCommand(	currGameMode, cmd, boxWidth, boxHeight, 
								board, solvedBoard);

	/* num_solutions command */
		} else if (COMMAND_NUM_SOLUTIONS == cmd.commandType ) { 
			
			handleNumSolutionsCommand(	currGameMode, boxWidth, boxHeight, 
										board, solvedBoard);

	/* autofill command */
		} else if (COMMAND_AUTOFILL == cmd.commandType ) { 

			handleAutofillCommand(	currGameMode, &historyListCursor, 
									&historyList, boxWidth, boxHeight, isMarkErrors, board, 
									solvedBoard);

	/* reset command */
		} else if (COMMAND_RESET == cmd.commandType ) { 

			handleResetCommand( currGameMode, &historyListCursor, 
								&historyList, boxWidth, boxHeight, board);


	/* exit command */
		} else if (COMMAND_EXIT == cmd.commandType ) { 

			handleExitCommand(	&historyList, boxWidth, boxHeight, 
								board, solvedBoard);

			return TRUE;

	/* invalid command */
		} else if (COMMAND_INVALID == cmd.commandType ) { 
			printInvalidCmdMsg();
		}

		/* check if game was completed */
		if ( GAME_SOLVE == currGameMode ) {
			checkIsBoardSolved(board, boxWidth, boxHeight, &currGameMode);
		}

	} /* while(TRUE) */

	freeBoard(board, boardWidth, boardHeight);
	freeBoard(solvedBoard, boardWidth, boardHeight);
	return TRUE;
}



char* getGameModeStr(GameStates currGameMode) {
	if (GAME_INIT == currGameMode) {
		return "GAME_INIT";
	} else if (GAME_SOLVE == currGameMode) {
		return "GAME_SOLVE";
	} else if (GAME_EDIT == currGameMode) {
		return "GAME_EDIT";
	} else if (GAME_ENDED == currGameMode) {
		return "GAME_ENDED";
	} else {
		return "UNDEFINED";
	} 
}




void handleSolveCommand(GameStates* currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
						DLLNode** historyListPtr, int isMarkErrors, int* boardWidthPtr, int* boardHeightPtr,
						int* boxWidthPtr, int* boxHeightPtr, BoardCell**** boardPtr, 
						BoardCell**** solvedBoardPtr, BoardCell**** loadedBoardPtr) {

	int prevBoardWidth, prevBoardHeight, showErrors, showFixed;
	char* trimmedStr;

	/* check if a path was given */
	if ( NULL == cmd.str ) {
		printInvalidCmdMsg();
		return;
	} 

	/* check if only whitespaces */
	trimmedStr = trimStr(cmd.str);
	if ( 0 == strlen(trimmedStr) ) {
		printInvalidCmdMsg();
		free(trimmedStr);
		return;
	} 
	free(trimmedStr);

	/* try to open the file */
	if ( !loadBoardFromFile(cmd.str, loadedBoardPtr, boxWidthPtr, boxHeightPtr) ) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return;
	}	

	/* free previous boards */
	if (NULL != *boardPtr) {
		freeBoard(*boardPtr, *boardWidthPtr, *boardHeightPtr);
	}

	if (NULL != *solvedBoardPtr) {
		freeBoard(*solvedBoardPtr, *boardWidthPtr, *boardHeightPtr);
	}

	/* save board dimensions in order to free resources in case the size changes */
	prevBoardWidth = *boardWidthPtr;
	prevBoardHeight = *boardHeightPtr;

	/* update pointers and board size */
	*boardWidthPtr	= (*boxWidthPtr) * (*boxHeightPtr);
	*boardHeightPtr	= (*boxWidthPtr) * (*boxHeightPtr);

	*boardPtr = allocateBoard(*boardWidthPtr, *boardHeightPtr);
	*solvedBoardPtr = allocateBoard(*boardWidthPtr, *boardHeightPtr);
	copyBoard(*boardPtr, *loadedBoardPtr, *boardWidthPtr, *boardHeightPtr);
	freeBoard(*loadedBoardPtr, *boardWidthPtr, *boardHeightPtr);

	/* mark errors in the board */
	markErrorsInBoard(*boardPtr, *boxWidthPtr, *boxHeightPtr);

	/* change game mode to solve */
	*currGameMode = GAME_SOLVE;

	/* clear history list */
	dllDeleteFromNode(historyListPtr, prevBoardWidth, prevBoardHeight);    
	addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, *boardPtr, *boardWidthPtr, *boardHeightPtr);

	/* print the board */
	showErrors = (GAME_EDIT == *currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != *currGameMode);
	printBoard(*(*boardPtr), *boxWidthPtr, *boxHeightPtr, showFixed, showErrors);

}


void handleEditCommand(	GameStates* currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
						DLLNode** historyListPtr, int isMarkErrors, int* boardWidthPtr, int* boardHeightPtr,
						int* boxWidthPtr, int* boxHeightPtr, BoardCell**** boardPtr, 
						BoardCell**** solvedBoardPtr, BoardCell**** loadedBoardPtr) {

	int prevBoardWidth, prevBoardHeight, showErrors, showFixed;

	/* check if a path was given */
	if ( NULL == cmd.str ) {
		printf("Error: File cannot be opened\n");
		return;
	} 

	/* if no file name given as a parameter, create a new default board */
	if ( 0 == strlen(cmd.str) ) {
		*boxWidthPtr = *boxHeightPtr = DEFAULT_BOX_SIZE;
		*loadedBoardPtr = allocateBoard((*boxWidthPtr) * (*boxHeightPtr), (*boxWidthPtr)*(*boxHeightPtr));

	/* otherwise, load the board from file */
	} else {
		if ( !loadBoardFromFile(cmd.str, loadedBoardPtr, boxWidthPtr, boxHeightPtr) ) {	
			printf("Error: File cannot be opened\n");
			return;
		}	
	}	

	/* free previous boards */
	if (NULL != *boardPtr) {
		freeBoard(*boardPtr, *boardWidthPtr, *boardHeightPtr);
	}

	if (NULL != *solvedBoardPtr) {
		freeBoard(*solvedBoardPtr, *boardWidthPtr, *boardHeightPtr);
	}

	/* save board dimensions in order to free resources in case the size changes */
	prevBoardWidth = *boardWidthPtr;
	prevBoardHeight = *boardHeightPtr;

	/* update pointers and board size */
	*boardWidthPtr	= (*boxWidthPtr) * (*boxHeightPtr);
	*boardHeightPtr	= (*boxWidthPtr) * (*boxHeightPtr);

	*boardPtr = allocateBoard(*boardWidthPtr, *boardHeightPtr);
	*solvedBoardPtr = allocateBoard(*boardWidthPtr, *boardHeightPtr);
	copyBoard(*boardPtr, *loadedBoardPtr, *boardWidthPtr, *boardHeightPtr);
	freeBoard(*loadedBoardPtr, *boardWidthPtr, *boardHeightPtr);

	/* make board cells unfixed */
	makeBoardCellsUnfixed(*boardPtr, *boardWidthPtr, *boardHeightPtr);
	
	/* mark errors in the board */
	markErrorsInBoard(*boardPtr, *boxWidthPtr, *boxHeightPtr);

	/* change game mode to solve */
	*currGameMode = GAME_EDIT;

	/* clear history list */
	dllDeleteFromNode(historyListPtr, prevBoardWidth, prevBoardHeight);    
	addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, *boardPtr, *boardWidthPtr, *boardHeightPtr);

	/* print the board */
	showErrors = (GAME_EDIT == *currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != *currGameMode);
	printBoard(*(*boardPtr), *boxWidthPtr, *boxHeightPtr, showFixed, showErrors);

}


void handleMarkErrorsCommand(GameStates currGameMode, Command cmd, int* isMarkErrors) {

	char* trimmedStr;
	char* unpaddedStr;

	if ( !(GAME_SOLVE == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if only whitespaces */
	trimmedStr = trimStr(cmd.str);

	/* point to the start of the string after the padding 0's */
	unpaddedStr = strSkipPrependingZeros(trimmedStr);

	/*printf("cmd.str: '%s' | trimmedStr: '%s' | unpaddedStr: '%s'\n", cmd.str, trimmedStr, unpaddedStr);*/
	if ( isStrEqual(ZERO_AS_STRING, unpaddedStr) ) {
		*isMarkErrors = FALSE;
	} else if ( isStrEqual(ONE_AS_STRING, unpaddedStr) ) {
		*isMarkErrors = TRUE;
	} else if (0 < strlen(trimmedStr)) {
		printf("Error: the value should be 0 or 1\n");		
	} else {
		printInvalidCmdMsg();
	}

	free(trimmedStr);
	/*printf("mark_errors args: %d %d %d '%s' | current mode: %s | board:%dx%d | isMarkErrors: %d \n", cmd.argX, cmd.argY, cmd.argZ, cmd.str, getGameModeStr(currGameMode), boardWidth, boardHeight, isMarkErrors);*/
}


void handlePrintBoardCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
								int isMarkErrors, BoardCell*** board) {

	int showErrors, showFixed;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check errors in the board and mark them */
	markErrorsInBoard(board, boxWidth, boxHeight);

	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*board, boxWidth, boxHeight, showFixed, showErrors );
}


void handleSetCommand(	GameStates currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
							DLLNode** historyListPtr, int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int x, y, showErrors, showFixed, isDifferentVal;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/*printf("set args: %d %d %d '%s' | current mode: %s | board:%dx%d\n", cmd.argX, cmd.argY, cmd.argZ, cmd.str, getGameModeStr(currGameMode), boardWidth, boardHeight);*/

	/* check if command args are valid */
	if ( !(1 <= cmd.argX && cmd.argX <= boardWidth &&
		   1 <= cmd.argY && cmd.argY <= boardHeight &&
		   0 <= cmd.argZ && cmd.argZ <= boardWidth ) ) {

		printf("Error: value not in range 0-%d\n", boardWidth);
		return;
	}

	/* check if the user try to set a fixed cell */
	if ( TRUE == (board[cmd.argY-1][cmd.argX-1])->isFixed  ) {
		printf("Error: cell is fixed\n");
		return;				
	}

	/* command args are valid */
	/* convert location arguments (starts from 1) to board location (starts from 0) */
	x = cmd.argX-1;
	y = cmd.argY-1;

	/* is the new value different to the value in board */
	isDifferentVal = ( cmd.argZ != (board[y][x])->val );

	/* put value in cell */
	(board[y][x])->val = cmd.argZ;

	/* if reseting a cell, remove 'isUserSet' flag from cell */
	(board[y][x])->isUserSet = (0 == cmd.argZ ? FALSE : TRUE);			

	/* mark changed cells in history list current board */
	board[y][x]->isChanged = TRUE;

	
	/* check errors in the board and mark them */
	markErrorsInBoard(board, boxWidth, boxHeight);

	/* In Edit mode, all cells containing values are marked as "fixed". */
	/* print the board */
	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*board, boxWidth, boxHeight, showFixed, showErrors);

	/* add the action to the history list if the board was changed */
	if ( isDifferentVal ) {
		/* add to history list */
		dllDeleteFromNode(&((*historyListCursorPtr)->next), boardWidth, boardHeight);
		addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, board, boardWidth, boardHeight);
	}

	/* clear 'isChanged' marked cells from playing board */
	setBoardChangedToFalse(board, boardWidth, boardHeight);
}


void handleValidateCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
							BoardCell*** board, BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if there are errors in the board */
	if ( 0 < markErrorsInBoard(board, boxWidth, boxHeight) ) {
		printf("Error: board contains erroneous values\n");
		return;
	}

	/* we find solution on solvedBoard, so copy board data to it */
	copyBoard(solvedBoard, board, boardWidth, boardHeight);

	/* check if board is solvable */
	if ( solveBoard(solvedBoard, boxWidth, boxHeight) ) {
		printf("Validation passed: board is solvable\n");
	} else {
		printf("Validation failed: board is unsolvable\n");
	}
}



/* Try generating sudoku board by randomly filling X cells with random legal values.
 * The board created by this function may not be valid!
 * subroutine for the generate handler
 */
int putRandomValuesInBoard(BoardCell*** board, int boxWidth, int boxHeight, int argX, int *possibleValsArr) {
	int boardWidth = boxWidth * boxHeight, boardHeight = boxWidth * boxHeight;
	int numOfBlanksInBoard, randIndex, j, k, x, y, v, numOfPossibleValues, res = TRUE;

	/* randomly fill X cells with legal values */
	j = 0;

	/* the board is empty at the start of each generation */
	numOfBlanksInBoard = boardWidth * boardHeight;

	while ( j < argX ) {

		numOfPossibleValues = 0;

		/* pick random cell index [1 .. w*h] */
		randIndex = 1 + getRandInt(numOfBlanksInBoard-1);

		/* get the k-th blank cell from top-right corner */
		for ( k = 0 ; k < boardWidth*boardHeight ; k++ ) {
			x = k % boardWidth;
			y = k / boardHeight;

			/* non-blank cell, so decrease the remaining cells to traverse */
			if ( 0 == (board[y][x])->val ) {
				randIndex--;
			}

			/* we arrived at the cell needed to be hidden! (i.e no more remaining non-blank cells) */
			if ( 0 == randIndex ) {
				break;
			}
		}

		/* set possible values in array */
		for ( v = 1 ; v <= boardWidth ; v++ ) {
			if ( validateCellByVal(board, x, y, v, boardWidth, boardHeight, boxWidth, boxHeight) ) {
				possibleValsArr[numOfPossibleValues] = v;
				numOfPossibleValues++;
			}
		}

		/*printf("iter: %d-%d | try num: %d , trying (%d, %d) arr: ", i, j, numOfTries, x+1, y+1);
		printArr(possibleValsArr, numOfPossibleValues);*/

		/* are there possible values for the cell? */
		if ( 0 < numOfPossibleValues ) { 
			/* pick random possible value */
			randIndex = getRandInt(numOfPossibleValues-1);

			/* set value in cell */
			board[y][x]->val = possibleValsArr[randIndex];

			/* decrease the blank cells counter */
			numOfBlanksInBoard--;

			j++;

		} else {
			/* no possible value, board is invalid */
			res = FALSE;
			break;
		}
	
		/*printf("iter: %d-%d | try num: %d , trying (%d, %d)->%d \n", i, j, numOfTries, x, y, v);*/
	}

	return res;
}

/* Generate a VALID puzzle by randomly filling X cells with random legal values, solve the resulting
 * board, and then clearing all but Y random cells.
 * 
 * subroutine for the generate handler
 */
int generateValidRandomBoard(	int boxWidth, int boxHeight, BoardCell*** board, BoardCell*** solvedBoard,  
								int argX, int argY, int iterationsLimit) {

	int boardWidth = boxWidth * boxHeight, boardHeight = boxWidth * boxHeight, i, isGenSuccessful = FALSE;
	int *possibleValsArr = (int*) calloc(boardWidth, sizeof(int));

	if ( NULL == possibleValsArr ) {
		printf("Generation failed: putRandomValsInBoard() could not allocate memory.\n");
		exit(0);
	}

	/* put values in X cells and so the board is valid */
	for ( i = 0 ; i < iterationsLimit ; i++ ) {

		if (0 < argX) {
			isGenSuccessful = putRandomValuesInBoard(board, boxWidth, boxHeight, argX, possibleValsArr);
		}

		/* solve the board to verify it is solvable */
		copyBoard(solvedBoard, board, boardWidth, boardHeight);

		/* check if board is solvable (if no possible values or ) */
		if ( (0 == argX || isGenSuccessful) && solveBoard(solvedBoard, boxWidth, boxHeight) ) {
			/*printf("** %d - board is solvable. inner tries: %d. filled: %d\n", i, numOfTries, j);*/
			/*printBoard(*(board), boxWidth, boxHeight, FALSE, FALSE );*/
			break;
		} else {
			/*printf("** %d - board is NOT solvable. inner tries: %d. filled: %d\n", i, numOfTries, j);*/
			/*printBoard(*(board), boxWidth, boxHeight, FALSE, FALSE );*/
			zerosBoard(board, boardWidth, boardHeight);
		}

	}

	/* if puzzle generation failed */
	if ( iterationsLimit == i ) {
		free(possibleValsArr);
		return FALSE;
	}

	/* show only Y cells */
	copyBoard(board, solvedBoard, boardWidth, boardHeight);
	hideCellsInBoard(board, boardWidth, boardHeight, boardWidth*boardHeight - argY);

	/* mark changed cells in current board for history list */
	setBoardNonBlankToChanged(board, boardWidth, boardHeight);

	free(possibleValsArr);
	return TRUE;
}


void handleGenerateCommand(	GameStates currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
							DLLNode** historyListPtr, int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board, 
							BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int showErrors, showFixed;
	int numOfEmptyCells;

	if ( !(GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* printf("generate args: %d %d \n", cmd.argX, cmd.argY);*/

	numOfEmptyCells = countEmptyCells(board, boardWidth, boardHeight);
	/* check if command args are valid */
	if ( !(0 <= cmd.argX && cmd.argX <= numOfEmptyCells &&
		   0 <= cmd.argY && cmd.argY <= numOfEmptyCells) ) {

		printf("Error: value not in range 0-%d\n", numOfEmptyCells );
		/* printf("Error: value not in range 0-%d\n", (boardWidth*boardHeight) );*/
		return;
	}

	/* check if board is empty */
	if ( !isBoardEmpty(board, boardWidth, boardHeight) ) {
		printf("Error: board is not empty\n");
		return;
	}


	/* try generating the board */
	if ( !generateValidRandomBoard(	boxWidth, boxHeight, board, solvedBoard,  
									cmd.argX, cmd.argY, GENERATE_ITERATIONS_LIMIT) ) {

		printf("Error: puzzle generator failed\n");
		return;
	}

	/* print the board */
	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*board, boxWidth, boxHeight, showFixed, showErrors );

	/* if number of generated cells is at least one i.e the board was changed, update
		the undo-redo history list */
	if ( 0 < cmd.argY ) {
		/* add to history list */
		dllDeleteFromNode(&((*historyListCursorPtr)->next), boardWidth, boardHeight);
		addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, board, boardWidth, boardHeight);
	}

	/* unmark changed cells playing board */
	setBoardChangedToFalse(board, boardWidth, boardHeight);
}


void handleUndoCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr,
						int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int showErrors, showFixed;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	if ( NULL == (*historyListCursorPtr)->prev ) {
		printf("Error: no moves to undo\n");
		return;
	}

	/* mark errors in the board */
	markErrorsInBoard(board, boxWidth, boxHeight);

	/* print the previous board */
	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*((*historyListCursorPtr)->prev->board), boxWidth, boxHeight, showFixed, showErrors );


	/* print the differnces between the boards */
	printUndoChanges((*historyListCursorPtr)->board, (*historyListCursorPtr)->prev->board, boardWidth, boardHeight);

	/* update history cursor */
	*historyListCursorPtr = (*historyListCursorPtr)->prev;

	/* update current board */
	copyBoard(board, (*historyListCursorPtr)->board, boardWidth, boardHeight);
	setBoardChangedToFalse(board, boardWidth, boardHeight);

}


void handleRedoCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr,
						int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int showErrors, showFixed;


	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}
	if ( NULL == (*historyListCursorPtr)->next ) {
		printf("Error: no moves to redo\n");
		return;
	}

	/* mark errors in the board */
	markErrorsInBoard(board, boxWidth, boxHeight);

	/* print the board */
	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*((*historyListCursorPtr)->next->board), boxWidth, boxHeight, showFixed, showErrors );

	/* print the differnces between the boards */
	printRedoChanges((*historyListCursorPtr)->board, (*historyListCursorPtr)->next->board, boardWidth, boardHeight);

	/* update history cursor */
	*historyListCursorPtr = (*historyListCursorPtr)->next;

	/* update current board */
	copyBoard(board, (*historyListCursorPtr)->board, boardWidth, boardHeight);
	setBoardChangedToFalse(board, boardWidth, boardHeight);

}



void handleSaveCommand(	GameStates currGameMode, Command cmd, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
    int trimmedStrLen;
    char* trimmedStr;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* is path to text file given */
	trimmedStr = trimStr(cmd.str);
	trimmedStrLen = strlen(trimmedStr);
	free(trimmedStr);
	if ( 0 == trimmedStrLen ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if there are errors in the board, only in edit mode */
	if ( (GAME_EDIT == currGameMode) && (0 < markErrorsInBoard(board, boxWidth, boxHeight)) ) {
		printf("Error: board contains erroneous values\n");
		return;
	}

	/* we find solution on solvedBoard, so copy board data to it */
	copyBoard(solvedBoard, board, boardWidth, boardHeight);

	/* check if board is solvable, only in edit mode */
	if ( (GAME_EDIT == currGameMode) && (!solveBoard(solvedBoard, boxWidth, boxHeight)) ) {
		printf("Error: board validation failed\n");
		return;
	}

	/* in edit mode, all cells saved as fixed */
	if ( GAME_EDIT == currGameMode ) {
		makeBoardCellsFixed(board, boardWidth, boardHeight);
	}

	if ( !saveBoardToFile(cmd.str, board, boxWidth, boxHeight) ) {
		printf("Error: File cannot be created or modified\n");

		/* in edit mode, all cells saved as fixed */
		if ( GAME_EDIT == currGameMode ) {
			makeBoardCellsUnfixed(board, boardWidth, boardHeight);
		}

		return;
	}

	/* in edit mode, all cells saved as fixed */
	if ( GAME_EDIT == currGameMode ) {
		makeBoardCellsUnfixed(board, boardWidth, boardHeight);
	}

	printf("Saved to: %s\n", cmd.str);


}


void handleHintCommand(	GameStates currGameMode, Command cmd, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int x, y;

	if ( !(GAME_SOLVE == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if command args are valid */
	if ( !(1 <= cmd.argX && cmd.argX <= boardWidth &&
		   1 <= cmd.argY && cmd.argY <= boardHeight ) ) {

		printf("Error: value not in range 1-%d\n", boardWidth);
		return;
	}

	/* board locations start from 0 (and ui locations start from 1) */
	x = cmd.argX - 1;
	y = cmd.argY - 1;

	/*printf("cell: (%d, %d) = %d | isFixed: %d \n", x, y, board[y][x]->val, board[y][x]->isFixed);*/

	/* check if there are errors in the board */
	if ( 0 < markErrorsInBoard(board, boxWidth, boxHeight) ) {
		printf("Error: board contains erroneous values\n");
		return;
	}

	/* check if cell is fixed */
	if ( board[y][x]->isFixed ) {
		printf("Error: cell is fixed\n");
		return;
	}

	/* check if cell already has value in it */
	if ( 0 != board[y][x]->val ) {
		printf("Error: cell already contains a value\n");
		return;
	}

	/* we find solution on solvedBoard, so copy board data to it */
	copyBoard(solvedBoard, board, boardWidth, boardHeight);

	/* check if board is solvable */
	if ( !solveBoard(solvedBoard, boxWidth, boxHeight) ) {
		printf("Error: board is unsolvable\n");
		return;
	}
	
	/* print the value in the solved board */
	printf("Hint: set cell to %d\n", solvedBoard[y][x]->val);
}

void handleNumSolutionsCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
								BoardCell*** board, BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int numOfSols;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if there are errors in the board */
	if ( 0 < markErrorsInBoard(board, boxWidth, boxHeight) ) {
		printf("Error: board contains erroneous values\n");
		return;
	}

	/* get number of solutions */
	/* we find solution on solvedBoard, so copy board data to it */
	copyBoard(solvedBoard, board, boardWidth, boardHeight);
	numOfSols = getNumOfSolutions(solvedBoard, boxWidth, boxHeight);
	printf("Number of solutions: %d\n", numOfSols);
	
	if ( 1 == numOfSols ) {
		printf("This is a good board!\n");
	} else if ( 1 < numOfSols ) {
		printf("The puzzle has more than 1 solution, try to edit it further\n");
	}

}


int autofillBoard(BoardCell*** board, BoardCell*** solvedBoard, int boxWidth, int boxHeight) {
	/* reset the autofill counter */
	int autofilledCounter = 0, x, y, res;
	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;

	for ( y = 0 ; y < boardWidth ; y++ ) {
		for ( x = 0 ; x < boardHeight ; x++ ) {
			res = autofillCell(board, x, y, boxWidth, boxHeight);

			/* if there is one option for cell value (it is the returned value) */
			if ( 1 <= res && res <= boardWidth ) {

				/* add value to the board */
				solvedBoard[y][x]->val = res;
				solvedBoard[y][x]->isChanged = TRUE;

				/* show message */
				printf("Cell <%d,%d> set to %d\n", x+1, y+1, res);

				/* advance the autofill counter */
				autofilledCounter++;
			}
		}
	}

	return autofilledCounter;
}



void handleAutofillCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr, DLLNode** historyListPtr, 
							int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board, 
							BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;
	int showErrors, showFixed;

	/* reset the autofill counter */
	int numOfAutofilledCells = 0;


	if ( !(GAME_SOLVE == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* check if there are errors in the board */
	if ( 0 < markErrorsInBoard(board, boxWidth, boxHeight) ) {
		printf("Error: board contains erroneous values\n");
		return;
	}

	/* autofill the board */
	/* set changes property to FALSE */
	setBoardChangedToFalse(board, boardWidth, boardHeight);
	setBoardChangedToFalse(solvedBoard, boardWidth, boardHeight);

	/* make changes on solvedBoard, so update it (not on the regular board because 
		we don't want previous filled cells affect the next cells) */
	copyBoard(solvedBoard, board, boardWidth, boardHeight);

	/* autofill the board */
	numOfAutofilledCells = autofillBoard(board, solvedBoard, boxWidth, boxHeight);

	/* save changes to regular board */
	copyBoard(board, solvedBoard, boardWidth, boardHeight);

	/* mark errors in the board */
	markErrorsInBoard(board, boxWidth, boxHeight);

	/* print the board */
	showErrors = (GAME_EDIT == currGameMode) || isMarkErrors;
	showFixed = (GAME_EDIT != currGameMode);
	printBoard(*board, boxWidth, boxHeight, showFixed, showErrors );

	/* if at least one cell was filled, we need to update the undo-redo history list */
	if ( 0 < numOfAutofilledCells ) {
		/* add to history list */
		dllDeleteFromNode(&((*historyListCursorPtr)->next), boardWidth, boardHeight);    
		addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, board, boardWidth, boardHeight);
	}

	/* unmark changed cells playing board */
	setBoardChangedToFalse(solvedBoard, boardWidth, boardHeight);
	setBoardChangedToFalse(board, boardWidth, boardHeight);
}


void handleResetCommand(GameStates currGameMode, DLLNode** historyListCursorPtr, DLLNode** historyListPtr,
						int boxWidth, int boxHeight, BoardCell*** board) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;

	if ( !(GAME_SOLVE == currGameMode || GAME_EDIT == currGameMode) ) {
		printInvalidCmdMsg();
		return;
	}

	/* undo all moves (move back to first board in history) */
	copyBoard(board, (*historyListPtr)->board, boardWidth, boardHeight);			

	/*
	printf("before: point: %p | ", (void*)historyListCursor);
	dllPrintNodesPtrs(historyList);
	*/

	/* clear the history list */
	dllDeleteFromNode(historyListPtr, boardWidth, boardHeight);    
	addBoardCopyToHistoryList(historyListPtr, historyListCursorPtr, board, boardWidth, boardHeight);

	/*
	printf("after: point: %p | ", (void*)historyListCursor);
	dllPrintNodesPtrs(historyList);
	*/

	/* show message */
	printf("Board reset\n");
}



void handleExitCommand(	DLLNode** historyListPtr, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard) {

	int boardWidth = boxWidth * boxHeight;
	int boardHeight = boxWidth * boxHeight;

	printf("Exiting...");

	/* print new line - ask in forum */
	printf("\n");

	/* on EOF (cmd.commandType == COMMAND_EXIT && cmd.argX==2) no new line is printed */
	/*
	if ( EOF_ENCOUNTERED != cmd.argX ) {
		printf("\n");
	}
	*/


	freeBoard(board, boardWidth, boardHeight);
	freeBoard(solvedBoard, boardWidth, boardHeight);

	dllDeleteFromNode(historyListPtr, boardWidth, boardHeight);    


}

