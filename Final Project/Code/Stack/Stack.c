#include "Stack.h"
  
/* Create a stack of given capacity. 
 * Initializes size of stack to 0.
 */
StackOfBoards* createStack(int capacity, int boardW, int boardH)
{
    /* allocate new stack */
    StackOfBoards* stack = (StackOfBoards*) malloc(sizeof(StackOfBoards));
    if (NULL == stack)
    {
        printf("Stack of boards allocation error\n");
        exit(0);
    }           

    /* set stack 'object' fields */
    stack->capacity = capacity;
    stack->top = -1;
    stack->boardW = boardW;
    stack->boardH = boardH;

    stack->array = (StackNode*) malloc(stack->capacity * sizeof(StackNode));
    if (NULL == stack)
    {
        printf("Stack of boards array allocation error\n");
        exit(0);
    }           

    return stack;
}
 

/* Stack is full when top is equal to the last index */
int isFull(StackOfBoards* stack)
{
   return stack->top == stack->capacity - 1;
}


/* Stack is empty when top is equal to -1 */
int isEmpty(StackOfBoards* stack)
{
   return stack->top == -1;
}

 
/* Add a board pointer to stack. */
void push(StackOfBoards* stack, StackNode stackNode)
{
    if ( isFull(stack) ) {
        return;
    }
    stack->array[++stack->top] = stackNode;
}
 

/* Remove a board from stack. */
StackNode* pop(StackOfBoards* stack)
{
    if ( isEmpty(stack) ) {
        return NULL;
    }
    return &(stack->array[(stack->top)--]);
}


/* Get the top of the stack. */
StackNode* top(StackOfBoards* stack)
{
    if ( isEmpty(stack) ) {
        return NULL;
    }
    return &(stack->array[stack->top]);
}

/* Get the top of the stack. */
int getStackSize(StackOfBoards* stack)
{
    return stack->top;
}

/* free the space allocated by the stack, it's array and the boards*/
void freeStack(StackOfBoards* stack) 
{   
    /* free the boards array */
    free(stack->array);

    /* free the stack */
    free(stack);
}


