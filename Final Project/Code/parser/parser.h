#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "../SPBufferset/SPBufferset.h"
#include "../boardUtils/boardEntities.h"

/*
	Parser Module 
		
		This module parses user input to program's commands. 
		Each parsed command is stored in a struct ('Command').
		As the user inputs lines that represents commands, they will be read and interpreted. 
		The 'main' function of this module is 'promptUserCommand(...)' that prompt a command 
		from the user, and should be called at the begining of every game loop iteration. 
*/

/* value that means the strings are equal */
#define STRINGS_EQUAL	0

/* bounds (used for testing the program) */
#define MIN_NUM_OF_CELLS_TO_FILL	0
#define MAX_NUM_OF_CELLS_TO_FILL	80

/* max buffer sizes */
#define MAX_COMMAND_LENGTH	258
#define MAX_INPUT_LENGTH	2048

/* whitespace characters */
#define COMMAND_DELIM " \t\r\n"
/*#define COMMAND_PARSING_FAILURE NULL*/


/* commands textual forms */
#define COMMAND_SOLVE_STR "solve"
#define COMMAND_EDIT_STR "edit"
#define COMMAND_MARK_ERRORS_STR "mark_errors"
#define COMMAND_PRINT_BOARD_STR "print_board"
#define COMMAND_SET_STR "set"
#define COMMAND_VALIDATE_STR "validate"
#define COMMAND_GENERATE_STR "generate"
#define COMMAND_UNDO_STR "undo"
#define COMMAND_REDO_STR "redo"
#define COMMAND_SAVE_STR "save"
#define COMMAND_HINT_STR "hint"
#define COMMAND_NUM_SOLUTIONS_STR "num_solutions"
#define COMMAND_AUTOFILL_STR "autofill"
#define COMMAND_RESET_STR "reset"
#define COMMAND_EXIT_STR "exit"

/* excpected number of tokens in each command */
/*
#define COMMAND_SOLVE_TOKENS 2
#define COMMAND_EDIT_TOKENS 2
#define COMMAND_MARK_ERRORS_TOKENS 2
#define COMMAND_PRINT_BOARD_TOKENS 1
#define COMMAND_SET_TOKENS 4
#define COMMAND_VALIDATE_TOKENS 1
#define COMMAND_GENERATE_TOKENS 3
#define COMMAND_UNDO_TOKENS 1
#define COMMAND_REDO_TOKENS 1
#define COMMAND_SAVE_TOKENS 2
#define COMMAND_HINT_TOKENS 3
#define COMMAND_NUM_SOLUTIONS_TOKENS 1
#define COMMAND_AUTOFILL_TOKENS 1
#define COMMAND_RESET_TOKENS 1
#define COMMAND_EXIT_TOKENS 1
*/


/*
 * all valid commands types
 */
typedef enum CommandTypes_t {
	COMMAND_SOLVE,
	COMMAND_EDIT,
	COMMAND_MARK_ERRORS,
	COMMAND_PRINT_BOARD,
	COMMAND_SET,
	COMMAND_VALIDATE,
	COMMAND_GENERATE,
	COMMAND_UNDO,
	COMMAND_REDO,
	COMMAND_SAVE,
	COMMAND_HINT,
	COMMAND_NUM_SOLUTIONS,
	COMMAND_AUTOFILL,
	COMMAND_RESET,
	COMMAND_EXIT,
	COMMAND_INVALID,
	COMMAND_BLANK
} CommandTypes;



/*
 * cammand struct
 * 
 * commandType - type of the command (from the 'CommandTypes' described above)
 * argX, argY, argZ - parsed numeric command parameters 
 * str - string arguments (file paths for example)
 * numOfTokens - number of words in the user input (used in order to print the correct error message)
 */
typedef struct command_t
{
	CommandTypes commandType;
	int argX;
	int argY;
	int argZ;
	char str[MAX_INPUT_LENGTH];
	int numOfTokens;
} Command;



/* return a pointer to the first non-zero character in the string
 * (ignore the 0's at the beginning of a number)
 * 
 * str - string argument
 * @ret: pointer to the position of the first non-zero character in the string 'str'
 */
char* strSkipPrependingZeros(char* str);


/* check whether two strings are equal (wrapper function to 'strcmp')
 * 
 * str - string argument
 * @ret: TRUE <=> string in str1 is equal to string str2.
 */
int isStrEqual(char* str1, char* str2);


/* return a copy of 'str' without padding whitespace
 *  
 * str - string argument
 * @ret: pointer to trimmed string (new string, not in the given str).
 */
char* trimStr(char* str);

/* prompt an integer from the user representing how many cells will not be hidden (used for testing)
 * 
 * @ret: TRUE on success. FALSE on failure.
 */
int getFilledCellsFromUser();

/* prompt a command from the user and modify the given 'command' arg to store the current command
 *
 * command - command to be filled from user
 * @ret: TRUE on success. FALSE on failure.
 */
int getCommandFromUser(Command* command);


/* set command's fields to "reset" values
 *
 * cmd - commend to be reset
 */
void resetCommand(Command* cmd);


/* get the relevant command arguments by the command type from the currently processed string
 *
 * command -commend to be filled with parsed data
 * cmdType - type of the command
 */
void assignArgumentsToCommand(Command *command, char *cmdType);

/* parse a text to a command and it's data
 *
 * command -commend to be filled with parsed data
 * str - command string to be parsed
 */
void parseCommand(Command* command, char* str);


/*
 * print the command data and parameters
 *
 * cmd - command to print
 */
void printCommand( Command* cmd );



#endif /*_PARSER_H_*/
