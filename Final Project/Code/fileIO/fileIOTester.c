#include <stdio.h>
#include <assert.h>
#include "fileIO.h"




int main(int argc, char* argv[])
{
    /*char* inputPath = "board4_4.in";*/
    int bw, bh;
    BoardCell*** board = NULL;

    assert(argc > 1);
    assert(NULL != argv[1]);
    

    if ( loadBoardFromFile(argv[1], &board, &bw, &bh) )
    {
        printf("board successfully loaded!\n");
    } else {
        printf("errors while loading board!\n");
    }

    printBoard( *board, bw*bh, bw, bh);

    
    if ( saveBoardToFile("boards/out.txt", board, bw, bh) )
    {
        printf("board successfully saved!\n");
    } else {
        printf("errors while saving board!\n");
    }


    freeBoard(board, bw*bh, bw*bh);

    return 0;
}
