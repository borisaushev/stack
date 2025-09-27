#include "../../include/calc/calc.h"

#include <unistd.h>

#include "stack.h"


static void popTwo(stack_t* stack, int* v1, int* v2) {
    SAFE_CALL(stackPop(stack, v1));
    SAFE_CALL(stackPop(stack, v2));
}

static void greetUser() {
    printf("---------------------------\n");
    printf(" Ts Cacl privetstvuyet vas\n");
    printf("---------------------------\n");
    sleep(1);
    printf("Comandu pishy i tam schitat budet da\n");
}

void add(stack_t* stack) {
    int v1 = POISON, v2 = POISON;
    popTwo(stack, &v1, &v2);

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("ADD: %d\n", v1 + v2);

    SAFE_CALL(stackPush(stack, v1 + v2));
}

void sub(stack_t* stack) {
    int v1 = POISON, v2 = POISON;
    popTwo(stack, &v1, &v2);

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("SUB: %d\n", v2 - v1);

    SAFE_CALL(stackPush(stack, v2 - v1));
}

void mul(stack_t* stack) {
    int v1 = POISON, v2 = POISON;
    popTwo(stack, &v1, &v2);

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("MUL: %d\n", v1 * v2);

    SAFE_CALL(stackPush(stack, v1 * v2));
}

bool div(stack_t* stack) {
    int v1 = POISON, v2 = POISON;
    popTwo(stack, &v1, &v2);
    DPRINTF("stack pop: %d, %d\n", v1, v2);

    if (v1 == 0) {
        return false;
    }
    printf("DIV: %d\n", v2 / v1);

    SAFE_CALL(stackPush(stack, v2 / v1));

    return true;
}

void out(stack_t* stack) {
    int val = POISON;
    SAFE_CALL(stackPop(stack, &val));

    DPRINTF("stack pop: %d\n", val);
    printf("OUT: %d\n", val);
}

void push(stack_t stack, char buf[20]) {
    int val = POISON;
    sscanf(buf, "PUSH %d\n", &val);

    DPRINTF("push: %d\n", val);
    SAFE_CALL(stackPush(&stack, val));
}

void runCalc() {
    stack_t stack = {};
    initStack(&stack, 10);

    greetUser();

    char buf[MAX_INP_LEN] = {};
    fgets(buf, MAX_INP_LEN, stdin);
    int line = 1;
    while (strcmp(buf, "HLT\n") != 0) {
        DPRINTF("read line: '%s'\n", buf);
        if (strcmp(buf, "ADD\n") == 0) {
            add(&stack);
        }
        else if (strcmp(buf, "SUB\n") == 0) {
            sub(&stack);
        }
        else if (strcmp(buf, "MUL\n") == 0) {
            mul(&stack);
        }
        else if (strcmp(buf, "DIV\n") == 0) {
            if (!div(&stack)) {
                PRINTERR("Division by zero at line %d\n", line);
                exit(1);
            }
        }
        else if (strcmp(buf, "OUT\n") == 0) {
            out(&stack);
        }
        else if (strncmp(buf, "PUSH", 4) == 0) {
            push(stack, buf);
        }
        else {
            PRINTERR("invalid input at line %d\n", line);
            exit(0);
        }

        fgets(buf, MAX_INP_LEN, stdin);
        line++;
    }

    printf("\ncalc obeys\n");
}
