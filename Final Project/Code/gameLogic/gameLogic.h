#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <stdio.h>
#include "../boardUtils/boardUtils.h"
#include "../parser/parser.h"
#include "../fileIO/fileIO.h"
#include "../solver/solver.h"
#include "../LinkedList/LinkedList.h"


/*
	Game Logic
		This module encapsulates the Sudoku puzzle game and the Sudoku board. 
		The 'main' function is  'runSudokuConsoleGame()' which is called by the main function and
		returns on exit (or error).
		It will be used to store and manipulate the game status, validate, and set moves, and so on.

		Also, each commands has it own handler function that is called when the command was issued.
*/


/* when the commands are given from file, and the command has EOF 
 * character, exit the game with EOF way (no new line at the end of output) 
 */
#define EOF_ENCOUNTERED 777


/* initial box size for game start and 'edit' with no parameters  */
#define DEFAULT_BOX_SIZE 3


/* strings for 0 and 1 for checking 'mark_errors' command argument */
#define ZERO_AS_STRING "0"
#define ONE_AS_STRING "1"

/* for limiting the number of puzzle generation tries */
#define GENERATE_ITERATIONS_LIMIT 1000



/*
 * game modes: 	GAME_INIT - initializing a game
 * 				GAME_EDIT - edit a board
 * 				GAME_SOLVE - regular playing mode
 *				GAME_ENDED - game has ended, only support 'restart' and 'exit' (was used for testing)
 */
typedef enum GameStates_t {
	GAME_INIT,
	GAME_SOLVE,
	GAME_EDIT,
	GAME_ENDED
} GameStates;


/*
 * Command handlers
 *
 */

/* Handle 'solve' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * isMarkErrors - should errors be marked in the board when printed
 * boardWidthPtr, boardHeightPtr - pointers to the variables holding the board's dimensions
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 * loadedBoardPtr - pointer to the board used for loading from text file
 */
void handleSolveCommand(GameStates* currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
						DLLNode** historyListPtr, int isMarkErrors, int* boardWidthPtr, int* boardHeightPtr,
						int* boxWidthPtr, int* boxHeightPtr, BoardCell**** boardPtr, 
						BoardCell**** solvedBoardPtr, BoardCell**** loadedBoardPtr);

/* Handle 'edit' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * isMarkErrors - should errors be marked in the board when printed
 * boardWidthPtr, boardHeightPtr - pointers to the variables holding the board's dimensions
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 * loadedBoardPtr - pointer to the board used for loading from text file
 */
void handleEditCommand(	GameStates* currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
						DLLNode** historyListPtr, int isMarkErrors, int* boardWidthPtr, int* boardHeightPtr,
						int* boxWidthPtr, int* boxHeightPtr, BoardCell**** boardPtr, 
						BoardCell**** solvedBoardPtr, BoardCell**** loadedBoardPtr);

/* Handle 'mark_errors' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * isMarkErrors - should errors be marked in the board when printed
 */
void handleMarkErrorsCommand(GameStates currGameMode, Command cmd, int* isMarkErrors);

/* Handle 'print_board' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * isMarkErrors - should errors be marked in the board when printed
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 */
void handlePrintBoardCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
								int isMarkErrors, BoardCell*** board);

/* Handle 'set' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * isMarkErrors - should errors be marked in the board when printed
 * boardPtr - pointer to the playing board
 */
void handleSetCommand(	GameStates currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
						DLLNode** historyListPtr, int boxWidth, int boxHeight, int isMarkErrors, 
						BoardCell*** board);

/* Handle 'validate' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleValidateCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
							BoardCell*** board, BoardCell*** solvedBoard);

/* Handle 'generate' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * isMarkErrors - should errors be marked in the board when printed
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleGenerateCommand(	GameStates currGameMode, Command cmd, DLLNode** historyListCursorPtr, 
							DLLNode** historyListPtr, int boxWidth, int boxHeight, int isMarkErrors, 
							BoardCell*** board, BoardCell*** solvedBoard);

/* Handle 'undo' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * isMarkErrors - should errors be marked in the board when printed
 * boardPtr - pointer to the playing board
 */
void handleUndoCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr,
						int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board);

/* Handle 'redo' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * isMarkErrors - should errors be marked in the board when printed
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 */
void handleRedoCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr,
						int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board);

/* Handle 'save' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleSaveCommand(	GameStates currGameMode, Command cmd, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard);

/* Handle 'hint' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * cmd - current command
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleHintCommand(	GameStates currGameMode, Command cmd, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard);

/* Handle 'num_solutions' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleNumSolutionsCommand(	GameStates currGameMode, int boxWidth, int boxHeight, 
								BoardCell*** board, BoardCell*** solvedBoard);

/* Handle 'autofill' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * isMarkErrors - should errors be marked in the board when printed
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleAutofillCommand(	GameStates currGameMode, DLLNode** historyListCursorPtr, DLLNode** historyListPtr, 
							int boxWidth, int boxHeight, int isMarkErrors, BoardCell*** board, 
							BoardCell*** solvedBoard);

/* Handle 'reset' command 
 * 
 * currGameMode - pointer to the current game mode variable
 * historyListCursorPtr - pointer to the current node in the history doubly linked list
 * historyListPtr - pointer to the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 */
void handleResetCommand(GameStates currGameMode, DLLNode** historyListCursorPtr, DLLNode** historyListPtr,
						int boxWidth, int boxHeight, BoardCell*** board);

/* Handle 'exit' command 
 * 
 * historyListPtr - pointer to the history doubly linked list
 * boxWidthPtr, boxHeightPtr - pointers to the variables holding the board boxes dimensions
 * boardPtr - pointer to the playing board
 * solvedBoardPtr - pointer to the board used for solving the playing board (we solve on a copy)
 */
void handleExitCommand(	DLLNode** historyListPtr, int boxWidth, int boxHeight, 
						BoardCell*** board, BoardCell*** solvedBoard);


/* get string representation of a game mode (mainly for testing) 
 *
 * currGameMode - current game mode value
 */
char* getGameModeStr(GameStates currGameMode);

/*
 * run the sudoku game, return exit code on error or successful game end. 
 * this is the 'main' game function, it contains the game loop, the event and command handling logic.
 */
int runSudokuConsoleGame();



#endif /*_GAME_LOGIC_H_*/
