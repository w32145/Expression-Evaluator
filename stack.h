#ifndef STACK_H
#define STACK_H

typedef struct
{
    void** block;
    int count;
    int max;
} STACK;

STACK* initStack(int max);
int push (STACK* stack, void* in);
int pop(STACK* stack);
int tryPeek(STACK* stack);
int getCount(STACK* stack);
void* peek(STACK* stack);
void destroy (STACK* stack);
#endif