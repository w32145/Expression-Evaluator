#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "stack.h"
#include "macros.h"

int getPrec(char c)
{
    if (c == '(' || c == ')' || c == '^')
    {
        return 3;
    }
    if (c == '*' || c == '/')
    {
        return 2;
    }
    if (c == '+' || c == '-')
    {
        return 1;
    }

    return -1;
}

int isLeft(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

char** postfix(char** tokens, int len, int* postLen) {

    char** rpn = malloc(sizeof(char*) * len);
    STACK* stack = initStack(STACK_SIZE);
    char top;

    for (int i = 0; i < len; i++) {

        char* token = tokens[i];
        int tokenLen = strlen(token);

        char op = token[0];

        if (tryPeek(stack)) {
            top = ((char*) peek(stack))[0];
        }
        else {
            top = ' '; // returns precedence of -1
        }

        if (isOp(op) && tokenLen == 1) {

            if (op == ')') {

                while (top != '(' && tryPeek(stack)) {

                    char* toString = malloc(2);
                    toString[0] = top;
                    toString[1] = '\0';

                    rpn[(*postLen)] = toString;
                    (*postLen)++;

                    pop(stack);
                    top = ((char*) peek(stack))[0];
                }

                pop(stack);
                continue;
            }
            else if (isLeft(op)) {
                
                while (getPrec(top) >= getPrec(op) && isLeft(top)) {
                    char* toString = malloc(2);
                    toString[0] = top;
                    toString[1] = '\0';
                    rpn[(*postLen)] = toString;

                    pop(stack);
                    (*postLen)++;

                    if (tryPeek(stack) == 1) {
                        top = ((char*) peek(stack))[0];
                    }
                    else {
                        top = ' ';
                    }
                }
            }
            push(stack, tokens[i]);
        }

        else {
            char* dest = malloc(tokenLen);
            memcpy(dest, token, tokenLen);
            rpn[(*postLen)] = dest;
            (*postLen)++;
        }
    }

    while (tryPeek(stack)) {
        char top = ((char*) peek(stack))[0];
        char* toString = malloc(2);
        toString[0] = top;
        toString[1] = '\0';
        rpn[(*postLen)] = toString;
        pop(stack);
        (*postLen)++;
    }
    
    destroy(stack);
    return rpn;
}