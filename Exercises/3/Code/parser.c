#include "parser.h"

int isCharWhitespace(char c) {
	return ( (' ' == c) || ('\n' == c) || ('\t' == c) || ('\r' == c) || 
			 ('\f' == c) || ('\v' == c) || (EOF == c) );
}

void consumeInputUntilWhitespace() {
	char c;
	while ( FALSE == isCharWhitespace( c = getchar() ) );
	/*
	while ( FALSE == isCharWhitespace( c = getchar() ) ) {printf("[%d]\n", c);}
	*/
}


/*asking the user to enter the number of cells to fill. */ 
int getFilledCellsFromUser() {

	int numberOfCellsToFill;
	int is_valid_input;

	do
	{	
		printf("Please enter the number of cells to fill [0-80]:\n");
		is_valid_input = TRUE;

		if (1 == scanf("%d", &numberOfCellsToFill) ) {
			if ( MIN_NUM_OF_CELLS_TO_FILL <= numberOfCellsToFill &&  
				 MAX_NUM_OF_CELLS_TO_FILL >= numberOfCellsToFill ) {
				
				/* is_valid_input = true; */	
				return numberOfCellsToFill;
			} else {
				is_valid_input = FALSE;	
			}
		} else {
			printf("Exiting...\n");
			return -1;
		}
			
		if (TRUE != is_valid_input)
		{
			printf("Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		}
	}	while (TRUE != is_valid_input);

	/* should not reach here */
	return 0;
}




void printCommand( Command* cmd ) {
	if ( NULL == cmd ) {
		printf("printCommand(): command* arg is null.\n");
		return;
	}
	printf("commandType: %d | x: %d, y: %d, z: %d \n", cmd->commandType, cmd->argX, cmd->argY, cmd->argZ);
}

int parseCommandArg(char* argStr) {
	if ( NULL == argStr ) {
		return -1;
	} else {
		return (int) strtol(argStr, NULL, 10);
	}
}

void getCommandFromUser(Command* command) {
	char str[MAX_INPUT_LENGTH];
	/*Command* command = NULL;*/

	/* ignore first new line characters*/
	do 
	{
		fgets(str, (int)sizeof(str), stdin);
	} while( NULL == str || '\n' == str[0] );

	parseCommand(command, str);

	/* printCommand( command ); */

	/*return command;*/
}

void parseCommand(Command* command, char* str) {
	char* cmdType;
	char* currWord;

	if (NULL == command) {
		printf("Error: malloc has failed\n");
		exit(0);
	}

	/* get the command parameters */
   	cmdType = strtok(str, COMMAND_DELIM);
	if ( NULL == cmdType ) {
		command->commandType = COMMAND_INVALID;	
		return;	
	}

	currWord = strtok(NULL, COMMAND_DELIM);
	command->argX = parseCommandArg(currWord);

	currWord = strtok(NULL, COMMAND_DELIM);
	command->argY = parseCommandArg(currWord);

	currWord = strtok(NULL, COMMAND_DELIM);
	command->argZ = parseCommandArg(currWord);

	/* validate command */
	if ( STRINGS_EQUAL == strcmp(cmdType, COMMAND_SET_STR) ) {
		if ( 1 > command->argX || 9 < command->argX ||
			 1 > command->argY || 9 < command->argY ||
			 0 > command->argZ || 9 < command->argZ ) {

			command->commandType = COMMAND_INVALID;		
		} else {
			command->commandType = COMMAND_SET;
		}
	} else if ( STRINGS_EQUAL == strcmp(cmdType, COMMAND_HINT_STR) ) {
		if ( 1 > command->argX || 9 < command->argX ||
			 1 > command->argY || 9 < command->argY) {

			command->commandType = COMMAND_INVALID;		
		} else {
			command->commandType = COMMAND_HINT;
		}

	} else if ( STRINGS_EQUAL == strcmp(cmdType, COMMAND_VALIDATE_STR) ) {
		command->commandType = COMMAND_VALIDATE;

	} else if ( STRINGS_EQUAL == strcmp(cmdType, COMMAND_RESTART_STR) ) {
		command->commandType = COMMAND_RESTART;

	} else if ( STRINGS_EQUAL == strcmp(cmdType, COMMAND_EXIT_STR) ) {
		command->commandType = COMMAND_EXIT;
		
	} else {
		command->commandType = COMMAND_INVALID;
	}
}


void testCommandsParser() {
	Command cmd;
	char str1[] = "set 4 4 4";
	char str2[] = "st 4 4 4";
	char str3[] = "set 4 4";
	
	char str4[] = "set 0 3 4";
	char str5[] = "set 1 0 4";
	char str6[] = "set 1 3 0 3 5 77777656";
	
	char str7[] = "set 10 3 4";
	char str8[] = "set 1 10 4";
	char str9[] = "set 1 3 10";

	char str10[] = "";
	

	char str20[] = "hint 1 3 10 safsdf";
	char str21[] = "hint 9 9";
	char str22[] = "hint 1 1";
	char str23[] = "hint 0 1";
	char str24[] = "hint 1 0";
	char str25[] = "hint 1";

	char str40[] = "validate 1 33 3 3 3 3 3 ";
	char str41[] = "      restart asdfas";
	char str42[] = "	exit 1";

	printf("start testCommandsParser...\n");


	parseCommand(&cmd, str1);
	if ( !(COMMAND_SET == cmd.commandType && 
		 4 == cmd.argX && 
		 4 == cmd.argY && 
		 4 == cmd.argZ) ) {

		printf("testCommandsParser: failed test 1 \n");
	}
	parseCommand(&cmd, str2);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 2 \n");
	}
	parseCommand(&cmd, str3);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 3 \n");
	}

	parseCommand(&cmd, str4);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 4 \n");
	}
	parseCommand(&cmd, str5);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 5 \n");
	}
	parseCommand(&cmd, str6);
	if ( !(COMMAND_SET == cmd.commandType && 
		 1 == cmd.argX && 
		 3 == cmd.argY && 
		 0 == cmd.argZ) ) {

		printf("testCommandsParser: failed test 6 \n");
	}
	
	parseCommand(&cmd, str7);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 7 \n");
	}
	parseCommand(&cmd, str8);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 8 \n");
	}
	parseCommand(&cmd, str9);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 9 \n");
	}

	parseCommand(&cmd, str10);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 10 \n");
	}

	parseCommand(&cmd, str20);
	if (COMMAND_INVALID == cmd.commandType ) {

		printf("aaa0 \n");
	}
	if ( !(COMMAND_HINT == cmd.commandType && 
		 1 == cmd.argX && 
		 3 == cmd.argY) ) {

		printf("testCommandsParser: failed test 20 \n");
	}
	parseCommand(&cmd, str21);
	if ( !(COMMAND_HINT == cmd.commandType && 
		9 == cmd.argX && 
		9 == cmd.argY) ) {

		printf("testCommandsParser: failed test 21 \n");
	}
	parseCommand(&cmd, str22);
	if ( !(COMMAND_HINT == cmd.commandType && 
		1 == cmd.argX && 
		1 == cmd.argY) ) {

		printf("testCommandsParser: failed test 22 \n");
	}
	parseCommand(&cmd, str23);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 23 \n");
	}
	parseCommand(&cmd, str24);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 24 \n");
	}
	parseCommand(&cmd, str25);
	if ( !(COMMAND_INVALID == cmd.commandType) ) {
		printf("testCommandsParser: failed test 25 \n");
	}


	parseCommand(&cmd, str40);
	if ( !(COMMAND_VALIDATE == cmd.commandType) ) {

		printf("testCommandsParser: failed test 40 \n");
	}	
	parseCommand(&cmd, str41);
	if ( !(COMMAND_RESTART == cmd.commandType) ) {

		printf("testCommandsParser: failed test 41 \n");
	}	
	parseCommand(&cmd, str42);
	if ( !(COMMAND_EXIT == cmd.commandType) ) {

		printf("testCommandsParser: failed test 42 \n");
	}

	printf("Done! \n");
}

