#include <cstdio>

#include "dump.h"
#include "verifier.h"
#include <common.h>

int main() {
    stack_t stack = {};
    initStack(&stack, 1, INT);

    for (int i = 0; i < 5; i++) {
        stackPush(&stack, &i);
    }
    printStack(&stack);

    stackPop(&stack);

    printStack(&stack);

    stackPop(&stack);

    printStack(&stack);


    const char* file = __FILE__;
    int line = __LINE__;
    const char* func = __func__;
    stackDump(&stack, __FILE__, __LINE__, __FUNCTION__);

    return 0;
}
