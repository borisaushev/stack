#include "TXLib.h"
#include "stack.h"

int main() {
    stack_t stack = {};
    initStack(&stack, 1);

    char buf[20] = {};
    fgets(buf, 20, stdin);
    while (strcmp(buf, "HLT\n") != 0) {
        DPRINTF("read line: '%s'\n", buf);
        if (strcmp(buf, "ADD\n") == 0) {
            int v1 = 0, v2 = 0;
            SAFE_CALL(stackPop(&stack, &v1));
            SAFE_CALL(stackPop(&stack, &v2));

            DPRINTF("stack pop: %d, %d\n", v1, v2);
            printf("ADD: %d\n", v1 + v2);

            SAFE_CALL(stackPush(&stack, v1 + v2));
        }
        else if (strcmp(buf, "SUB\n") == 0) {
            int v1 = 0, v2 = 0;
            SAFE_CALL(stackPop(&stack, &v1));
            SAFE_CALL(stackPop(&stack, &v2));

            DPRINTF("stack pop: %d, %d\n", v1, v2);
            printf("SUB: %d\n", v2 - v1);

            SAFE_CALL(stackPush(&stack, v2 - v1));
        }
        else if (strcmp(buf, "MUL\n") == 0) {
            int v1 = 0, v2 = 0;
            SAFE_CALL(stackPop(&stack, &v1));
            SAFE_CALL(stackPop(&stack, &v2));

            DPRINTF("stack pop: %d, %d\n", v1, v2);
            printf("MUL: %d\n", v1 * v2);

            SAFE_CALL(stackPush(&stack, v1 * v2));
        }
        else if (strcmp(buf, "DIV\n") == 0) {
            int v1 = 0, v2 = 0;
            SAFE_CALL(stackPop(&stack, &v1));
            SAFE_CALL(stackPop(&stack, &v2));

            DPRINTF("stack pop: %d, %d\n", v1, v2);
            printf("DIV: %d\n", v2 / v1);

            SAFE_CALL(stackPush(&stack, v2 / v1));
        }
        else if (strcmp(buf, "OUT\n") == 0) {
            int v1 = 0;
            SAFE_CALL(stackPop(&stack, &v1));

            DPRINTF("stack pop: %d\n", v1);
            printf("OUT: %d\n", v1);
        }
        else if (strncmp(buf, "PUSH", 4) == 0) {
            int val = POISON;
            sscanf(buf, "PUSH %d\n", &val);

            printf("push: %d\n", val);
            SAFE_CALL(stackPush(&stack, val));
        }

        fgets(buf, 20, stdin);
    }
}

