#include <stdio.h>
#include "LinkedList.h"

void basicTest() {
    DLLNode* head = NULL;
    int boxW = 2, boxH = 2, boardW = boxW*boxH, boardH = boxW*boxH;

    BoardCell*** board1 = allocateBoard(boardW, boardH);
    board1[0][0]->val = 1;

    dllAppend(&head, board1);
    
    dllDeleteFromNode(&head, boardW, boardH);    
}

void test() {
    /* Start with the empty list */
    DLLNode* head = NULL;
    DLLNode* mid = NULL;
    int boxW = 2, boxH = 2, boardW = boxW*boxH, boardH = boxW*boxH;

    BoardCell*** board2 = allocateBoard(boardW, boardH);
    BoardCell*** board3 = allocateBoard(boardW, boardH);
    BoardCell*** board4 = allocateBoard(boardW, boardH);
    BoardCell*** board5 = allocateBoard(boardW, boardH);
    BoardCell*** board6 = allocateBoard(boardW, boardH);
    BoardCell*** board8 = allocateBoard(boardW, boardH);

    board2[0][0]->val = 2;
    board3[0][0]->val = 3;
    board4[0][0]->val = 4;
    board5[0][0]->val = 5;
    board6[0][0]->val = 6;
    board8[0][0]->val = 8;

    /* Insert 6.  So linked list becomes 6->NULL */
    dllAppend(&head, board6);
 
    /* Insert 4 at the end. So linked list becomes 6->4->NULL */
    dllAppend(&head, board4);
 
    /* Insert 8. So linked list becomes 6->4->8->NULL */
    dllAppend(&head, board8);
    
    /* So linked list becomes 6->4->8->2->3->5->NULL */
    dllAppend(&head, board2);
    dllAppend(&head, board3);
    dllAppend(&head, board5);

 
    printf("Created DLL is: \n");
    /*dllPrint(head, boxW, boxH);*/
    printf(" \n \n");
    dllPrintBoardsPtrs(head);

    mid = (((head->next)->next)->next);
    printf("delete from: %d \n", mid->board[0][0]->val);

    dllDeleteFromNode(&mid, boardW, boardH);
    dllPrintBoardsPtrs(head);

    printf(" \n \n");
    /*dllPrint(head, boxW, boxH);*/
    

    dllPrintBoardsPtrs(head);
    dllDeleteFromNode(&head, boardW, boardH);    
    dllPrintBoardsPtrs(head);
}

int main()
{
    test();
    return 0;
}