#include <stdio.h>
#include <assert.h>

#include "parser.h"



/*
 * unit test for the parsing module
 */
/*
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
    char str42[] = "    exit 1";

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
*/

/*int main(int argc, char* argv[])*/
int main()
{   
    Command cmd;

    while (TRUE) {
        resetCommand(&cmd);

        getCommandFromUser(&cmd);

        printCommand(&cmd);    

        if ( COMMAND_EXIT == cmd.commandType) {
            break;
        }
     }

    return 0;
}
