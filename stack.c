#include <string.h>
#include <stdlib.h>
#include "stack.h"

void initStack(STACK* stack, int bytes, int max) {
    stack -> block = malloc(bytes * max);
    stack -> bytes = bytes;
    stack -> max = max;
    stack -> count = 0;
}

int push (STACK* stack, void* in) {

    int bt = stack -> bytes;
    int offset = bt * stack -> count;

    if (stack -> count == stack -> max) {
        //perror("Error: overflow!");
        return 0;
    }

    // ensure that memory is contiguous
    void* dest = (char*) stack -> block + offset;

    memcpy(dest, in, bt);
    (stack -> count)++;

    return 1;
}

int pop(STACK* stack) {

    if (stack -> count > 0) {
        stack -> count--;
        return 1;
    }

    //perror("Error: underflow!");
    return 0;
}

int tryPeek(STACK* stack) {
    if (stack -> count > 0) {
        return 1;
    }
    return 0;
}

int getCount(STACK* stack) {
    return stack -> count;
}

void* peek(STACK* stack) {

    if (stack -> count > 0) {
        char* fs = (char*) stack -> block;
        return fs + (stack -> count - 1) * stack -> bytes;
    }

    return NULL;
}

void destroy (STACK* stack) {
    free(stack -> block);
    stack -> block = NULL;
    free(stack);
    stack = NULL;
}