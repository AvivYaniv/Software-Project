#include "Stack.h"



/* unit test*/
void basic() 
{
    int w = 2, h = 2;
    StackOfBoards* stack = createStack(2, w, h);
    StackNode sn1, sn2, tmpSn;

    printf("is stack empty: %d \n", isEmpty(stack));
    printf("is stack full: %d \n", isFull(stack));


    sn1.v = 1;
    push(stack, sn1);
    printf("%d pushed to stack\n", sn1.v);
    
    sn2.v = 2;
    push(stack, sn2);
    printf("%d pushed to stack\n", sn2.v);

    printf("is stack empty: %d \n", isEmpty(stack));
    printf("is stack full: %d \n", isFull(stack));


    tmpSn = *top(stack);
    printf("%d at the top of the stack\n", tmpSn.v);
    tmpSn = *pop(stack);
    printf("%d popped from stack\n", tmpSn.v);

    tmpSn = *top(stack);
    printf("%d at the top of the stack\n", tmpSn.v);
    tmpSn = *pop(stack);
    printf("%d popped from stack\n", tmpSn.v);

    printf("is stack empty: %d \n", isEmpty(stack));
    printf("is stack full: %d \n", isFull(stack));

    freeStack(stack);


}


void testFreeMem() 
{
    int w = 2, h = 2;
    StackOfBoards* stack = createStack(2, w, h);
    StackNode sn1, sn2;


    printf("is stack empty: %d \n", isEmpty(stack));
    printf("is stack full: %d \n", isFull(stack));

    sn1.v = 1;
    push(stack, sn1);
    printf("%d pushed to stack\n", sn1.v);

    sn2.v = 2;
    push(stack, sn2);
    printf("%d pushed to stack\n", sn2.v);

    printf("is stack empty: %d \n", isEmpty(stack));
    printf("is stack full: %d \n", isFull(stack));

    freeStack(stack);

}


int main()
{
    basic();

    printf("----------------------\n");

    testFreeMem();
 
    return 0;
}
