#include <string.h>
#include <stdlib.h>
#include "stack.h"

STACK *initStack(int max)
{
    STACK *stack = malloc(sizeof(STACK *));
    stack->block = malloc(sizeof(void *) * max);
    stack->max = max;
    stack->count = 0;
    return stack;
}

int push(STACK *stack, void *in)
{

    if (stack->count == stack->max)
    return 0;

    void *dest = malloc(sizeof(void*));
    memcpy(dest, in, sizeof(void*));
    stack->block[(stack->count++)] = dest;

    return 1;
}

int pop(STACK *stack)
{

    if (stack->count > 0)
    {
        stack->count--;
        return 1;
    }

    // perror("Error: underflow!");
    return 0;
}

int tryPeek(STACK *stack)
{
    if (stack->count > 0)
    {
        return 1;
    }
    return 0;
}

int getCount(STACK *stack)
{
    return stack->count;
}

void *peek(STACK *stack)
{
    if (stack->count > 0)
    {
        return stack->block[stack->count - 1];
    }
    return NULL;
}

void destroy(STACK *stack)
{
    free(stack->block);
    stack->block = NULL;
    free(stack);
    stack = NULL;
}