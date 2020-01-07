#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "SPBufferset.h"
#include "boardEntities.h"

/*
	Parser 

		a. As the user inputs lines that represents commands, you need to read and interpret them. This should be the responsibility of the Parser module. 

		b. It is highly recommended to use the standard function strtok, which can be found in the header file string.h. This function is similar to Java's split method. Use " \t\r\n" (note the space) as a delimiter string. More information can be found online.
*/



#define STRINGS_EQUAL	0

#define MIN_NUM_OF_CELLS_TO_FILL	0
#define MAX_NUM_OF_CELLS_TO_FILL	80

#define MAX_INPUT_LENGTH	1025

#define COMMAND_DELIM " \t\r\n"
#define COMMAND_PARSING_FAILURE NULL


/* maybe replace with consts??? */
#define COMMAND_SET_STR "set"
#define COMMAND_HINT_STR "hint"
#define COMMAND_VALIDATE_STR "validate"
#define COMMAND_RESTART_STR "restart"
#define COMMAND_EXIT_STR "exit"

typedef enum CommandTypes_t {
	COMMAND_SET,
	COMMAND_HINT,
	COMMAND_VALIDATE,
	COMMAND_RESTART,
	COMMAND_EXIT,
	COMMAND_INVALID
} CommandTypes;

/*
const char * COMMAND_SET = "set";
const char * COMMAND_HINT = "hint";
const char * COMMAND_VALIDATE = "validate";
const char * COMMAND_RESTART = "restart";
const char * COMMAND_EXIT = "exit";
*/

typedef struct command_t
{
	CommandTypes commandType;
	int argX;
	int argY;
	int argZ;
} Command;

/*
 * prompt an integer from the user representing how many cells will not be hidden
 */
int getFilledCellsFromUser();

/*
 * prompt a command from the user and modify the given 'command' arg to store the current command
 */
void getCommandFromUser(Command* command);


/*
 * parse a text to a command and it's data
 */
void parseCommand(Command* command, char* str);


/*
 * print the command data
 */
void printCommand( Command* cmd );


/* 
 * unit test for the parsing module
 */
void testCommandsParser();



#endif /*_PARSER_H_*/
