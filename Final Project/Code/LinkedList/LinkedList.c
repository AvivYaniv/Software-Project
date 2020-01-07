#include "LinkedList.h"
 

/* appends a new node at the end  */
DLLNode* dllAppend(DLLNode** ppHead, BoardCell*** board)
{
    DLLNode* last = *ppHead; /* used in step 5*/

    DLLNode* newNode = (DLLNode*)malloc(sizeof(DLLNode));
    if (NULL == newNode) {
        printf("dllAppend node allocation error\n");
        exit(0);
    }           


    /* put in the board  */
    newNode->board = board;
 
    /* this new node is going to be the last node, so make next of it as NULL*/
    newNode->next = NULL;
 
    /* if the linked list is empty, then make the new node it's head */
    if (*ppHead == NULL) {
        newNode->prev = NULL;
        *ppHead = newNode;
        return newNode;
    }
 
    /* otherwise, move until the last node */
    while (last->next != NULL)
        last = last->next;
 
    /* change the next of last node */
    last->next = newNode;
 
    /* make last node as previous of new node */
    newNode->prev = last;
 
    return newNode;
}
 
/* print content of linked list starting from a given node*/
void dllPrint(DLLNode* node, int boxW, int boxH)
{
    while (node != NULL) {
        printBoard(node->board[0], boxW, boxH, FALSE, FALSE);
        /*printf(" %d ", node->board);*/
        node = node->next;
    }
    printf(" \n");
}

/* print pointers to nodes of linked list starting from a given node*/
void dllPrintNodesPtrs(DLLNode* node)
{
    while (node != NULL) {
        /* check consistency */
        if (node->prev != NULL ) {
            if (node->prev->next != node) {
                printf("\n warning: not consistent. \n");
            }
        }

        printf("%p->", (void*)node);
        node = node->next;
    }
    printf("NULL");
    printf(" \n");
}

/* print pointers to boards in nodes starting from a given node*/
void dllPrintBoardsPtrs(DLLNode* node)
{
    while (node != NULL) {
        printf("%p->", (void*)(node->board));
        node = node->next;
    }
    printf("NULL\n");
}


/* delete all nodes starting from the given node and forward */
void dllDeleteFromNode(DLLNode** nodep, int boardW, int boardH) 
{
    DLLNode* next;
    DLLNode* nodepPrev;

    /* is list empty */
    if (NULL == nodep || NULL == *nodep) {
        return;
    }

    nodepPrev = (*nodep)->prev;

    /*printf("deleting %p (prev: %p) ...\n", (void*) (*nodep), (void*)nodepPrev);*/

    /* start deleting forward */
    while ((*nodep) != NULL) {
        next = (*nodep)->next;
        /*printf("free board: %p\n", (void*)((*nodep)->board));*/
        freeBoard((*nodep)->board, boardW, boardH);
        /*free(node->board);*/
        free((*nodep));
        (*nodep) = next;
    }

    /* remove reference to node from previous one */
    if (nodepPrev != NULL) {
         nodepPrev->next = NULL;
    } 
    
    *nodep = NULL;
}


/* create a copy of given board, push the board to the back of the list and update 
 * the cursor to point to this board in the list */
void addBoardCopyToHistoryList(DLLNode** pHistoryList, DLLNode** pHistoryListCursor, BoardCell*** board, int boardWidth, int boardHeight) {
    /* create a copy of board */
    BoardCell*** tmpBoard = allocateBoard(boardWidth, boardHeight);
    copyBoard(tmpBoard, board, boardWidth, boardHeight);
    
    /* update history corsur to current board and add to list */
    *pHistoryListCursor = dllAppend(pHistoryList, tmpBoard);
}
