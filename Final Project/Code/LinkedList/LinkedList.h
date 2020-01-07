#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#include "../boardUtils/boardUtils.h"
#include "../boardUtils/boardEntities.h"


/*
	Doubly Linked List Module

		This module implements a doubly linked list data structre used in the undo/redo history list.
		Each list node has pointers to the next and previous nodes, and stores a pointer to board as data. 

*/


/* A linked list node*/
typedef struct t_node{
    BoardCell*** board;
    struct t_node* next;
    struct t_node* prev;
} DLLNode;

 
/* appends a new node at the end of the list
 *
 * ppHead - pointer to the list head (pointer to pointer because we may need to alter the head itself)
 * board - the board to be saved in the list
 */
DLLNode* dllAppend(DLLNode** ppHead, BoardCell*** board);

/* print pointers to nodes of linked list starting from a given node (mainly for testing)
 *
 * node - node to print pointers from
 */
void dllPrintNodesPtrs(DLLNode* node);


/* print pointers to boards in nodes starting from a given node (mainly for testing)
 *
 * node - node to print boards pointers from
 */
void dllPrintBoardsPtrs(DLLNode* node);


/* print content of linked list starting from a given node (mainly for testing)
 *
 * node - node to print boards from
 * boxW, boxH - dimensions of the board's box
 */
void dllPrint(DLLNode* node, int boxW, int boxH);


/* delete (also free the allocated memory) all nodes starting from the given node and forward 
 *
 * node - node to print boards from
 * boardW, boardH - dimensions of the board
 */
void dllDeleteFromNode(DLLNode** nodep, int boardW, int boardH);


/* create a copy of given board, push the board to the back of the list and update 
 * the cursor to point to this board in the list 
 *
 * pHistoryList - pointer to a doubly linked list (history list)
 * pHistoryListCursor - pointer to the current position in the doubly linked list (history list)
 * board - board copy to be added to the end of the list (after the node pointed by 'pHistoryListCursor')
 * boardWidth, boardHeight - dimensions of the board
 */
void addBoardCopyToHistoryList(	DLLNode** pHistoryList, DLLNode** pHistoryListCursor, 
								BoardCell*** board, int boardWidth, int boardHeight);

#endif /*_LINKED_LIST_H_*/
