#include "TXLib.h"
#include "stack.h"

int main() {
    stack_t stack = {};
    initStack(&stack, 1);

    for (int i = 0; i < 5; i++) {
        SAFE_CALL(stackPush(&stack, i));
    }
    printStack(&stack);

    for (int i = 10; i >= 0; i--) {
        element_t popRes = POISON;
        SAFE_CALL(stackPop(&stack, &popRes));
        DPRINTF("popRes = " REG "\n", popRes);
    }
    stack.array[stack.capacity + 1] = -1;
    printStack(&stack);
}
