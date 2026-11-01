#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "methods.h"
#include "macros.h"
#include "stack.h"

double solve(char** rpn, int len) {

    STACK* stack = initStack(STACK_SIZE);

    for (int i = 0; i < len; i++) {

        double left = 0;
        double right = 0;

        char op = rpn[i][0];

        if (isOp(op) && !isNumber(rpn[i])) {

            if (getCount(stack) >= 2) {
                right = *(double*)(peek(stack));
                pop(stack);
                left = *(double*)(peek(stack));
                pop(stack);
            }
            else if (getCount(stack) == 1) {
                right = *(double*)(peek(stack));
                pop(stack);
            }
            else {
                perror("An operator was encountered but there were no operands\n");
            }

            double x = 0;

            switch (op) {
                case '+':
                x = left + right;
                break;

                case '-':
                x = left - right;
                break;

                case '*':
                x = left * right;
                break;

                case '/':
                if (right == 0) {
                    return -1;
                }
                x = left / right;
                break;

                case '^':
                x = pow(left, right);
            }

            push(stack, &x);
        }
        else {
            double number = strtod(rpn[i], NULL);
            push(stack, &number);
        }

    }

    double result;

    if (tryPeek(stack)) {
        result = *(double*)(peek(stack));
    }
    else {
        result = 0.00;
    }
    
    destroy(stack);
    return result;
}