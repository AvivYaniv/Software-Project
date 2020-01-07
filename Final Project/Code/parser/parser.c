#include "parser.h"




/*
 * is given char 'c' a whitespace
 */
int isCharWhitespace(char c) {
	return ( (' ' == c) || ('\n' == c) || ('\t' == c) || ('\r' == c) || 
			 ('\f' == c) || ('\v' == c) || (EOF == c) );
}


/*
 * is given string made only of whitespaces
 */
int isStringOnlyWhitespaces(char* str) {
	int i;
	for ( i = 0 ; i < (int)strlen(str) ; i++ ) {
		if ( !isCharWhitespace(str[i]) ) {
			return FALSE;
		}
	}
	return TRUE;
}


/*
 * request characters from input until a whitespace
 */
void consumeInputUntilWhitespace() {
	char c;
	while ( FALSE == isCharWhitespace( c = getchar() ) );
	/*
	while ( FALSE == isCharWhitespace( c = getchar() ) ) {printf("[%d]\n", c);}
	*/
}


/*
 * asking the user to enter the number of cells to fill, and returning it
 */ 
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
			printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		}
	}	while (TRUE != is_valid_input);

	/* should not reach here */
	return 0;
}

/* get informative name for the command type (enum)*/
char* commandTypeToStr(int cmdT) {
	if ( COMMAND_SOLVE == cmdT ) {
		return COMMAND_SOLVE_STR;
	} else if (COMMAND_EDIT == cmdT ) { 
		return COMMAND_EDIT_STR;
	} else if (COMMAND_MARK_ERRORS == cmdT ) { 
		return COMMAND_MARK_ERRORS_STR;
	} else if (COMMAND_PRINT_BOARD == cmdT ) { 
		return COMMAND_PRINT_BOARD_STR;
	} else if (COMMAND_SET == cmdT ) { 
		return COMMAND_SET_STR;
	} else if (COMMAND_VALIDATE == cmdT ) { 
		return COMMAND_VALIDATE_STR;
	} else if (COMMAND_GENERATE == cmdT ) { 
		return COMMAND_GENERATE_STR;
	} else if (COMMAND_UNDO == cmdT ) { 
		return COMMAND_UNDO_STR;
	} else if (COMMAND_REDO == cmdT ) { 
		return COMMAND_REDO_STR;
	} else if (COMMAND_SAVE == cmdT ) { 
		return COMMAND_SAVE_STR;
	} else if (COMMAND_HINT == cmdT ) { 
		return COMMAND_HINT_STR;
	} else if (COMMAND_NUM_SOLUTIONS == cmdT ) { 
		return COMMAND_NUM_SOLUTIONS_STR;
	} else if (COMMAND_AUTOFILL == cmdT ) { 
		return COMMAND_AUTOFILL_STR;
	} else if (COMMAND_RESET == cmdT ) { 
		return COMMAND_RESET_STR;
	} else if (COMMAND_EXIT == cmdT ) { 
		return COMMAND_EXIT_STR;
	} else {
		return "invalid";
	}
}

/* print the given command (for testing purposes) */
void printCommand( Command* cmd ) {
	if ( NULL == cmd ) {
		printf("printCommand(): command* arg is null.\n");
		return;
	}

	printf("commandType: %s | tokens: %d | x: %d, y: %d, z: %d , str: '%s' \n", 
			commandTypeToStr(cmd->commandType), cmd->numOfTokens, cmd->argX, cmd->argY, cmd->argZ, 
			cmd->str);
	/*printf("commandType: %d | x: %d, y: %d, z: %d , str: %s \n", cmd->commandType, cmd->argX, cmd->argY, cmd->argZ, cmd->str);*/
}



char* strSkipPrependingZeros(char* str) {
	int i = 0, len;

	if (NULL == str) {
		return str;
	}

	len = strlen(str);
	for ( i = 0 ; i < len-1 ; i++ ) {
		if ( '0' != str[i] ) {
			break;
		}
	}
	return str + i;
}


/*
old: not used because if strings contains letters, 0 is returned and causes unexcpected behavior
int getIntFromCommandArg(char* argStr) {
	printf("getIntFromCommandArg: %s\n", argStr);
	if ( NULL == argStr ) {
		return -1;
	} else {
		return (int) strtol(argStr, NULL, 10);
	}
}
*/


/* return a copy of 'str' without padding whitespace */
char* trimStr(char* str) {
    int strLen = strlen(str);
    int trimmedStrLen;
    int start = 0, end = 0;
    char* trimmedStr;
    
    /* find first non-whitespace character */
    while (start < strLen) {
        if (!isCharWhitespace(str[start])) {
            break;
        }
        start++;
    }
    
    end = start;
    
    /* find first whitespace character */
    while (end < strLen) {
        if (isCharWhitespace(str[end])) {
            break;
        }
        end++;
    }
    
    trimmedStrLen = end-start;
    trimmedStr = (char*)malloc((trimmedStrLen+1)*sizeof(char));
    
    memcpy(trimmedStr, &(str[start]), sizeof(char)*trimmedStrLen);    
    trimmedStr[trimmedStrLen] = '\0';
    
    return trimmedStr;
}

/*
 * given string 'strArg', try to convert it to int 'res', return TRUE on success
 * 
 * strArg - string argument
 * res - pointer to the result - converted int argument
 * 
 * @ret: TRUE <-> argument converted successfully
 */
int getIntFromCommandArg(char* strArg, int* res) {
	int isSuccess = FALSE, number;
    char numberAsString[MAX_INPUT_LENGTH], *trimmedStr, *endptr = NULL; /* pointer to additional chars  */

    /* initial value */
	*res = -1;
	if ( NULL == strArg ) {
		return isSuccess;
	} 

	/* trim the arg */
	trimmedStr = trimStr(strArg);
	number = (int) strtol(trimmedStr, &endptr, 10);
    /*printf ("string : '%s' len=%d  |  trimmed: '%s' len=%d  |  number=%d errno=%d \n", strArg, (int)strlen(strArg), trimmedStr, (int)strlen(trimmedStr), number, errno);*/

    /* test return to number and errno values */
    if (trimmedStr == endptr) {
        /* printf (" number : %d  invalid  (no digits found, 0 returned)\n", number);*/
		*res = -1;
		isSuccess = FALSE;
    } else if (errno == ERANGE && number == INT_MIN) {
        /* printf (" number : %d  invalid  (underflow occurred)\n", number);*/
		*res = -2;
		isSuccess = FALSE;
    } else if (errno == ERANGE && number == INT_MAX) {
        /* printf (" number : %d  invalid  (overflow occurred)\n", number);*/
		*res = -3;
		isSuccess = FALSE;
    } else if (errno == EINVAL) {
    	/* not in all c99 implementations - gcc OK */
        /* printf (" number : %d  invalid  (base contains unsupported value)\n", number);*/
		*res = -4;
		isSuccess = FALSE;
    /*} else if (errno != 0 && number == 0) {
        //printf (" number : %d  invalid  (unspecified error occurred)\n", number);
		*res = -5;
		isSuccess = FALSE;
    }*/
    } else if (errno == 0 && trimmedStr && *endptr != 0) {
        /* printf (" number : %d    valid  (but additional characters remain)\n", number);*/
        /*printf (" number : %d    valid  (but additional characters remain)\n", number);*/
		*res = -6;
		isSuccess = FALSE;
    } else if (errno == 0 && trimmedStr && !*endptr) {
        /* printf (" number : %d    valid  (and represents all characters read)\n", number);*/
		*res = number;
		isSuccess = TRUE;
    } else {

	    sprintf(numberAsString, "%d", number);
    	/*printf("numberAsString: %d | trimmedStr: %d \n", (int)strlen(numberAsString), (int)strlen(trimmedStr));*/
    	if ( strlen(numberAsString) == strlen(trimmedStr) ) {
			*res = number;		
			isSuccess = TRUE;
    	} else {
			isSuccess = FALSE;
    	}
    }

	free(trimmedStr);
    return isSuccess;
}


/* parse command argument to int.
 * rules:	if the argument is a valid int, it is converted to int.
 *			if the argument is NOT a valid int and NOT empty string, set the command argument to -1 
 *			if the argument is NULL or empty string, set the command type to invalid 
 *
 * command - pointer to the command we need to edit
 * rawArgStr - the raw string that the user entered
 * argInt - pointer to the int argument (probably one of the command arguments) where the result is stored
 */
void parseCommandArg(Command* command, char* rawArgStr, int* argInt ) {
	char *trimmedRawArgStr, *argStr;

	if (NULL == rawArgStr) {
		/* empty, set command as invalid */
		command->commandType = COMMAND_INVALID;				
		return;
	}

	/* remove padding whitespace */
	trimmedRawArgStr = trimStr(rawArgStr);

	/* point to the first non-zero charcter */
	argStr = strSkipPrependingZeros(trimmedRawArgStr);

	/*printf("trimmedRawArgStr: '%s' | argStr: '%s'\n", trimmedRawArgStr, argStr);*/


	/* try to convert the string argument to an int */
	if ( !getIntFromCommandArg(argStr, argInt ) ) {


		/* could not convert arg to number, check if it empty */
		if ( 0 < strlen(argStr) ) {
			/* not empty, set argument as invalid */
			*argInt = -1;
		} else {
			/* empty, set command as invalid */
			command->commandType = COMMAND_INVALID;				
		}
		
		/*printf("COMMAND_GENERATE first arg: %s type: %s  argX: %d \n", rawArgStr, commandTypeToStr(command->commandType), command->argX );*/
	}	
		
	free(trimmedRawArgStr);
}



/* return TRUE if the str contains an EOF character */
int isStrContainEOF(char* str) {
	int i;
	int len = strlen(str);

	if ( NULL == str ) {
		/*printf("isStrContainEOF: str is null \n");*/
		return FALSE;	
	}

	for ( i = 0 ; i < len ; i++ ) {
		if ( EOF == str[i] ) {
			/*printf("isStrContainEOF: str(%s) contains EOF \n", str);*/
			return TRUE;
		}
	}
	
	/*printf("isStrContainEOF: str(%s) does NOT contain EOF \n", str);*/
	return FALSE;
}

/* return TRUE if the last character in 'str' is newline ('\n') - used for testings*/
int isNewLineAtCommandEnd(char* str) {
	int len = strlen(str);
	int isNewLineAtEnd, isEOFAtEnd;


	if ( NULL == str ) {
		/*printf("isNewLineBeforeEOF: str is null \n");*/
		return FALSE;	
	}
	/*printf("****len: %d isLastEof: %d last: %d\n", len, (EOF == str[len]), str[len]);*/

	isEOFAtEnd = (EOF == str[len-1]);
	isNewLineAtEnd = isEOFAtEnd;
	isNewLineAtEnd = ('\n' == str[len-1]);

	/*return (isNewLineAtEnd || isEOFAtEnd);*/
	return (isNewLineAtEnd);
}



int getCommandFromUser2(Command* command) {
	char *strStart;
	char lastChar;
	int i = 0, newSize = 0, lastCharIndex = 0;
	int strLen = 0;
	char *str = (char*) malloc(sizeof(char));

	if ( NULL == str ) {
		printf("getCommandFromUser() - Error: Could not allocate memory.\n");
		exit(0);
	}

	/* ignore first new line characters*/
		do {
			/*prevSize = i * MAX_INPUT_LENGTH;*/
			i++;
			newSize = i * MAX_INPUT_LENGTH;
			/*printf("prevSize: %d | newSize: %d | allocate size: %d\n", prevSize, newSize, newSize);*/

			str = (char*) realloc((void*)str, newSize * sizeof(char));

			if ( NULL == str ) {
				printf("getCommandFromUser() - Error: Could not allocate memory.\n");
				exit(0);
			}

			/* start writing from index 0 or from the '\0' when too big */
			if (1 == i) {
				lastCharIndex = 0;
				strStart = str;
			} else {
				lastCharIndex = ((i-1)*MAX_INPUT_LENGTH-(i-1));
				strStart = str + lastCharIndex;
			}

			/*printf("start puting in index: %d\n", lastCharIndex);*/

			fgets(strStart, MAX_INPUT_LENGTH, stdin);

			/*printf("~str(%d): '%s' -\n", (int)strlen(str), str);*/
			
			lastCharIndex = lastCharIndex + MAX_INPUT_LENGTH - 2; 
			/*printf("lastCharIndex: %d\n", lastCharIndex);*/

			lastChar = str[lastCharIndex];
			strLen = strlen(str);

			/* only EOF */
			if (0 == strLen) {
				return FALSE;
			}

			/*printf("i: %d |  lastChar[%d]: '%c' (%d) | strlen: %d\n", i, lastCharIndex, lastChar, ('\0' == lastChar), strLen );*/

		}
		/* repeat as long as there are characters in stdin */ 
		while ( ('\0' != lastChar) && ('\n' != lastChar) && (EOF != lastChar) );

	/*printf("str(%d): '%s' -\n", (int)strlen(str), str);*/

	parseCommand(command, str);
	return TRUE;
}

/* consume all characters in stdin. stop at null terminator, newline or eof.
 * this is needed when the command is too long to fit inside the buffer.
 */
void consumeInputUntilNewLineOrEof() {
	char c[2];
	do {
		/* c = getchar();*/
		if ( (feof(stdin)) || (NULL == fgets(c, 2, stdin)) ){
			return;
		}
	} while ( ('\0' != c[0]) && ('\n' != c[0]) && (EOF != c[0]) );
}


int getCommandFromUser(Command* command) {
	char str[MAX_INPUT_LENGTH];

	/* ignore first new line characters*/
	do 
	{
		if (NULL == fgets(str, (int)sizeof(str), stdin) ) {
			return FALSE;
		}

	} while( ( NULL == str ) && !isStrContainEOF(str));

	/*printf("str(%d): '%s' -\n", (int)strlen(str), str);*/

	/* check if there are still more characters*/
	if ( (MAX_INPUT_LENGTH-1 == strlen(str) ) && ('\n' != str[MAX_INPUT_LENGTH-2]) ) {

		/*printf("%d %d str: '%s'\n", (str[MAX_COMMAND_LENGTH-1]) ,(str[MAX_COMMAND_LENGTH-2]) , str);*/
		/*printf("consume\n");*/
		consumeInputUntilNewLineOrEof();
	}

	parseCommand(command, str);
	return TRUE;
}


void resetCommand(Command* cmd) {
	if ( NULL == cmd ) {
		return;
	}

	cmd->commandType = COMMAND_INVALID;
	cmd->argX = -1;
	cmd->argY = -1;
	cmd->argZ = -1;
	cmd->str[0] = '\0';
}


/* count how many tokens (words) are in a given string
 * each token is padded with whitespace. e.g: ""->0,  "    "->0,  " a ab cc "->3
 */
int countTokens(char* str) {
	int counted = 0, inWord = FALSE;
	char* currStr = str;

	do switch(*currStr) {
		case '\0':
		case ' ': case '\n': case '\t': case '\r': case '\f': case '\v': case EOF:
			if (inWord) {
				inWord = FALSE;
				counted++;
			}
			break;
		default: 
			inWord = TRUE;

	} while(*currStr++);

	return counted;
}


/* return true iff str1 is equal to str2 lexicographically
 * helper functions for nicer syntax 
 */
int isStrEqual(char* str1, char* str2) {
	return (STRINGS_EQUAL == strcmp(str1, str2) );
}


void parseCommand(Command* command, char* str) {
	char *cmdType;

	if (NULL == command) {
		printf("Error: command is null.\n");
		exit(0);
	}

	/* reset command */
	command->commandType = COMMAND_INVALID;	
	command->numOfTokens = -1;

	/* check if command is too long ( take the '\n' and '\0' into account) */
	if ( MAX_COMMAND_LENGTH - 2 < strlen(str) ) {
		return;			
	}

	/* is it an empty command? (line consists of whitespaces only) */
	if ( isStringOnlyWhitespaces(str) ) {
		command->commandType = COMMAND_BLANK;	
		command->numOfTokens = 0;	
		return;	
	}

	/* count tokens in command */
	command->numOfTokens = countTokens(str);	

	/* get the command type */
   	cmdType = strtok(str, COMMAND_DELIM);
	if ( NULL == cmdType ) {
		command->commandType = COMMAND_INVALID;	
		return;	
	}

	/*command->str[0] = '\0';*/

	/* get additional command parameters */
	assignArgumentsToCommand(command, cmdType);
}

void assignArgumentsToCommand(Command *command, char *cmdType) {
	char *currWord;

	if ( isStrEqual( COMMAND_SOLVE_STR, cmdType) ) {
		command->commandType = COMMAND_SOLVE;	
		currWord = strtok(NULL, COMMAND_DELIM);
		if (currWord) {
			strcpy(command->str, currWord);
		}

	} else if ( isStrEqual( COMMAND_EDIT_STR, cmdType) ) {
		command->commandType = COMMAND_EDIT;	
		currWord = strtok(NULL, COMMAND_DELIM);
		if (currWord) {
			strcpy(command->str, currWord);
		}

	} else if ( isStrEqual( COMMAND_MARK_ERRORS_STR, cmdType) ) {
		command->commandType = COMMAND_MARK_ERRORS;	

		currWord = strtok(NULL, COMMAND_DELIM);
		if (currWord) {
			currWord = trimStr(currWord);
			strcpy(command->str, currWord);
			free(currWord); /* 'trimStr()' returned a copy, so it need to be freed */
		}

	} else if ( isStrEqual( COMMAND_PRINT_BOARD_STR, cmdType) ) {
		command->commandType = COMMAND_PRINT_BOARD;	

	} else if ( isStrEqual( COMMAND_SET_STR, cmdType) ) {
		command->commandType = COMMAND_SET;

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argX) );

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argY) );

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argZ) );


	} else if ( isStrEqual( COMMAND_VALIDATE_STR, cmdType) ) {
		command->commandType = COMMAND_VALIDATE;	

	} else if ( isStrEqual( COMMAND_GENERATE_STR, cmdType) ) {
		command->commandType = COMMAND_GENERATE;

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argX) );

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argY) );


	} else if ( isStrEqual( COMMAND_UNDO_STR, cmdType) ) {
		command->commandType = COMMAND_UNDO;

	} else if ( isStrEqual( COMMAND_REDO_STR, cmdType) ) {
		command->commandType = COMMAND_REDO;
		
	} else if ( isStrEqual( COMMAND_SAVE_STR, cmdType) ) {
		command->commandType = COMMAND_SAVE;

		currWord = strtok(NULL, COMMAND_DELIM);
		if (currWord) {
			strcpy(command->str, currWord);
		}

	} else if ( isStrEqual( COMMAND_HINT_STR, cmdType) ) {
		command->commandType = COMMAND_HINT;

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argX) );

		currWord = strtok(NULL, COMMAND_DELIM);
		parseCommandArg(command, currWord, &(command->argY) );

	} else if ( isStrEqual( COMMAND_NUM_SOLUTIONS_STR, cmdType) ) {
		command->commandType = COMMAND_NUM_SOLUTIONS;

	} else if ( isStrEqual( COMMAND_AUTOFILL_STR, cmdType) ) {
		command->commandType = COMMAND_AUTOFILL;
		
	} else if ( isStrEqual( COMMAND_RESET_STR, cmdType) ) {
		command->commandType = COMMAND_RESET;

	} else if ( isStrEqual( COMMAND_EXIT_STR, cmdType) ) {
		command->commandType = COMMAND_EXIT;
	}
}	


