#include "../../include/calc/calc.h"

#include <unistd.h>

#include "stack.h"

#define EXIT_ON_FALSE(func) \
    BEGIN \
    if(!func(&stack)) { \
        PRINTERR("invalid input at line %d\n", line);\
        exit(1); \
    } \
    END

static bool popTwo(stack_t* stack, int* v1, int* v2) {
    SAFE_CALL(stackPop(stack, v1));
    SAFE_CALL(stackPop(stack, v2));
    return *v1 != POISON && *v2 != POISON;
}

static void greetUser() {
    printf("---------------------------\n");
    printf(" Ts Cacl privetstvuyet vas\n");
    printf("---------------------------\n");
    sleep(1);
    printf("Comandu pishy i tam schitat budet da\n");
}

bool add(stack_t *stack) {
    int v1 = POISON, v2 = POISON;
    if (!popTwo(stack, &v1, &v2)) {
        return false;
    }

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("ADD: %d\n", v1 + v2);

    SAFE_CALL(stackPush(stack, v1 + v2));

    return true;
}

bool sub(stack_t *stack) {
    int v1 = POISON, v2 = POISON;
    if (!popTwo(stack, &v1, &v2)) {
        return false;
    }

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("SUB: %d\n", v2 - v1);

    SAFE_CALL(stackPush(stack, v2 - v1));

    return true;
}

bool mul(stack_t *stack) {
    int v1 = POISON, v2 = POISON;
    if (!popTwo(stack, &v1, &v2)) {
        return false;
    }

    DPRINTF("stack pop: %d, %d\n", v1, v2);
    printf("MUL: %d\n", v1 * v2);

    SAFE_CALL(stackPush(stack, v1 * v2));

    return true;
}

bool div_calc(stack_t* stack) {
    int v1 = POISON, v2 = POISON;
    if (!popTwo(stack, &v1, &v2)) {
        return false;
    }
    DPRINTF("stack pop: %d, %d\n", v1, v2);

    if (v1 == 0) {
        return false;
    }
    printf("DIV: %d\n", v2 / v1);

    SAFE_CALL(stackPush(stack, v2 / v1));

    return true;
}

bool out(stack_t *stack) {
    int val = POISON;
    SAFE_CALL(stackPop(stack, &val));
    if (val == POISON) {
        return false;
    }

    DPRINTF("stack pop: %d\n", val);
    printf("OUT: %d\n", val);

    return true;
}

bool push(stack_t* stack, char buf[20]) {
    int val = POISON;
    int res = sscanf(buf, "PUSH %d\n", &val);

    if (res != 1) {
        return false;
    }

    DPRINTF("push: %d\n", val);
    SAFE_CALL(stackPush(stack, val));

    return true;
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
            EXIT_ON_FALSE(add);
        }
        else if (strcmp(buf, "SUB\n") == 0) {
            EXIT_ON_FALSE(sub);
        }
        else if (strcmp(buf, "MUL\n") == 0) {
            EXIT_ON_FALSE(mul);
        }
        else if (strcmp(buf, "DIV\n") == 0) {
            EXIT_ON_FALSE(div_calc);
        }
        else if (strcmp(buf, "OUT\n") == 0) {
            EXIT_ON_FALSE(out);
        }
        else if (strncmp(buf, "PUSH", 4) == 0) {
            if (!push(&stack, buf)) {
                PRINTERR("unparsable input at line %d\n", line);
            }
        }
        else {
            PRINTERR("invalid command at line %d\n", line);
            exit(1);
        }

        fgets(buf, MAX_INP_LEN, stdin);
        line++;
    }

    printf("\ncalc obeys\n");
}
