#include "game.h"



int resetGame(BoardCell*** board, BoardCell*** solvedBoard, int board_width, int board_height, 
				int box_width, int box_height, GameStates *gameState) {
	int numberOfCellsToFill;

	/* for testing */
	/*fillBoardWithDummyData(board, board_width, board_height);*/
	/*dummyBoard2(board, board_width, board_height);*/

	zerosBoard(board, board_width, board_height);

	/* randomly solve a board*/
	runBacktrack(board, board_width, board_height, box_width, box_height, RANDOM);

	/* copy to solved */
	copyBoard(solvedBoard, board, board_width, board_height);

	/* get number of cells to fill */
	numberOfCellsToFill = getFilledCellsFromUser(0, board_width*board_height-1);
	if ( -1 == numberOfCellsToFill ) {
		freeBoard(board, board_width, board_height);
		freeBoard(solvedBoard, board_width, board_height);
		return FALSE;
	}

	/* hide cells */
	hideCellsInBoard(board, board_width, board_height, numberOfCellsToFill);

	*gameState = GAME_STARTED;
	
	printBoard(board, board_width, board_height);

	return TRUE;
}


int runSudokuGame() {
	int board_width 		= 9;
	int board_height 		= 9;
	int board_box_width 	= 3;
	int board_box_height 	= 3;

	int btRes;
	GameStates gameState;
	Command cmd;
	
	/* Code Section */
	/* Allocating boards */	
	BoardCell*** board = allocateBoard(board_width, board_height);
	BoardCell*** solvedBoard = allocateBoard(board_width, board_height);

	if (FALSE == resetGame(board, solvedBoard, board_width, board_height, board_box_width, board_box_height, &gameState) ) {
		return FALSE;
	}

	/* game loop */
	while ( TRUE ) {

		/* get command from user  */
		while ( TRUE ) {

			getCommandFromUser(&cmd);
			if ( COMMAND_INVALID == cmd.commandType ) {
				printf("Error: invalid command\n");		
			} else {
				break;		
			}

		}	

		/*printCommand(command);*/

		/* game logic */
		if ( COMMAND_SET == cmd.commandType ) {
			
			if ( GAME_STARTED != gameState ) {
				printf("Error: invalid command\n");
			
			/* check if command args are valid */
			} else if ( !(1 <= cmd.argX && cmd.argX <= board_width &&
				   1 <= cmd.argY && cmd.argY <= board_height &&
				   0 <= cmd.argZ && cmd.argZ <= board_width ) ) {

				printf("Error: value is invalid\n");

			/* check if the user try to set a fixed cell */
			} else if ( TRUE == (board[cmd.argY-1][cmd.argX-1])->isFixed  ) {
				printf("Error: cell is fixed\n");
				
			/* command args are valid */
			} else {
				if ( GAME_STARTED != gameState ) {
					printf("Error: invalid command\n");
				} else if ( 0 == cmd.argZ || TRUE == validateCellByVal(board, cmd.argX-1, cmd.argY-1, cmd.argZ, board_width, board_height, board_box_width, board_box_height) ) {
					
					/* put value in cell */
					(board[cmd.argY-1][cmd.argX-1])->val = cmd.argZ;

					/* if reseting a cell, remove 'isUserSet' flag from cell */
					if ( 0 == cmd.argZ ) {
						(board[cmd.argY-1][cmd.argX-1])->isUserSet = FALSE;			
					}

					printBoard(board, board_width, board_height);

				} else {
					printf("Error: value is invalid\n");
				}

		
			}


		} else if ( COMMAND_HINT == cmd.commandType ) {

			if ( GAME_STARTED != gameState ) {
				printf("Error: invalid command\n");
			
			/* check if command args are valid */
			} else if ( !(1 <= cmd.argX && cmd.argX <= board_width &&
				   1 <= cmd.argY && cmd.argY <= board_height ) ) {

				printf("Error: value is invalid\n");
			} else {
				printf("Hint: set cell to %d\n", (solvedBoard[cmd.argY-1][cmd.argX-1])->val);
			}
			

		} else if ( COMMAND_VALIDATE == cmd.commandType ) {

			if ( GAME_STARTED != gameState ) {
				printf("Error: invalid command\n");
			} else {
				copyBoard(solvedBoard, board, board_width, board_height);

				btRes = runBacktrack(solvedBoard, board_width, board_height, board_box_width, board_box_height, DETERMINISTIC);
				
				if ( TRUE == btRes ) {
					printf("Validation passed: board is solvable\n");
				} else {
					printf("Validation failed: board is unsolvable\n");
				}
			}

		} else if ( COMMAND_RESTART == cmd.commandType ) {

			if (FALSE == resetGame(board, solvedBoard, board_width, board_height, board_box_width, board_box_height, &gameState) ) {
				return FALSE;
			}
		
		} else if ( COMMAND_EXIT == cmd.commandType ) {
			printf("Exiting...\n");
			freeBoard(board, board_width, board_height);
			freeBoard(solvedBoard, board_width, board_height);
			return TRUE;
		}


		/* check if the entire board was filled */
		if ( gameState == GAME_STARTED && TRUE == isBoardFilled(board, board_width, board_height) ) {

			/* check if board is correct */
			if ( TRUE == isFilledBoardValid(board, board_width, board_height, board_box_width, board_box_height) ) {
				gameState = GAME_ENDED;
				printf("Puzzle solved successfully\n");
			}
		}

	}

	freeBoard(board, board_width, board_height);
	freeBoard(solvedBoard, board_width, board_height);
	return TRUE;
}


/* fill the board with dummy content */
void fillBoardWithDummyData(BoardCell*** board, int board_width, int board_height) {
	int i, j;		
	BoardCell* cell;

	for ( i = 0 ; i < board_height ; i++ ) {
		for ( j = 0 ; j < board_width ; j++ ) {
			cell = (BoardCell*) malloc( sizeof(BoardCell) );

			if (NULL == cell) {
				printf("Error: malloc has failed\n");
				exit(0);
			}
						

			/*printf("[%d, %d] : %p \n", i, j, (void*)cell);*/
			
			board[i][j]=cell;

			/* printf("[%d, %d] : %p \n", i, j, (void*)cell);*/
			
			cell->val = (3*i+4*j)%9;
			cell->isUserSet = (0 != cell->val? TRUE : FALSE );
			if ( 0 == cell->val % 3 ) {
				cell->isFixed = FALSE;
			} else {
				cell->isFixed = (2*j+i)%2;
			}

		}			
	}	
}
