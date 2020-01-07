#ifndef _STACK_OF_BOARDS_H_
#define _STACK_OF_BOARDS_H_


#include <stdio.h>
#include <stdlib.h>


/*
	Stack Module 
 		A data structure to represent a stack of changes to the sudoku boards:
		"value of cell (x+1,y+1) was set to v". 
		The "top of the stack" is the array last element.

		The implementation of the stack uses arrays (not linked list logic) with the size of the maximal
		stack depth which depends on the 'capacity' field.
*/ 


/* stack's node
 * 
 * x,y - cell position 
 * v - cell value 
 */
typedef struct _stackNode 
{
    int x, y, v;
} StackNode;


/* stack data structure
 * 
 * top - index of the top element
 * boardW, boardH - board's dimensions 
 * capacity - stack capacity (max size of stack)
 * array - the array used to implement the stack
 */
typedef struct _stackOfBoards 
{
    int top, boardW, boardH;
    int capacity;
    StackNode* array;
} StackOfBoards;




/* Create a stack of given capacity. 
 * Initializes size of stack to 0.
 * 
 * capacity - stack maximal size
 * boardW, boardH - board's dimensions 
 *
 * @ret: stack for board changes
 */
StackOfBoards* createStack(int capacity, int boardW, int boardH);


/* Stack is full when top is equal to the last index 
 *
 * stack - the stack we would like to check if full.
 *
 * @ret: TRUE <-> stack is full
 */
int isFull(StackOfBoards* stack);


/* Stack is empty when top is equal to -1 
 * 
 * stack - the stack we would like to check if empty.
 * 
 * @ret: TRUE <-> stack is empty 
 */
int isEmpty(StackOfBoards* stack);


/* Add a board pointer to stack. 
 * 
 * stack - the stack we would like to edit.
 * stackNode - the node we would like to push
 */
void push(StackOfBoards* stack, StackNode stackNode);


/* Remove a board from stack. 
 * 
 * stack - the stack we would like to pop from.
 * 
 * @ret: pointer to the node that was poped 
 */
StackNode* pop(StackOfBoards* stack);


/* Get the size of the stack. (for testing)
 * 
 * stack - the stack we would like to check size.
 * 
 * @ret: number of nodes in the stack 
 */
int getStackSize(StackOfBoards* stack);


/* Get the top of the stack. 
 * 
 * stack - the stack we would like to peek in.
 * 
 * @ret: pointer to the node that is in the top of the stack 
 */
StackNode* top(StackOfBoards* stack);

/* 
 * Free the space allocated by the stack, it's array
 * 
 * stack - the stack we would like to free.
 */
void freeStack(StackOfBoards* stack);


#endif /*_STACK_OF_BOARDS_H_*/
