#include "stack.h"

#include <cassert>

#include "dump.h"
#include "verifier.h"


void initStack(stack_t* stack, size_t capacity) {
    assert(stack);
    DPRINTF("initializing stack\n");
    stack->capacity = capacity;
    stack->elementCount = 0;
    stack->array = (element_t*) calloc(capacity + 2, sizeof(element_t)); //защита канарейкой

    for (size_t i = 1; i < capacity + 1; i++) {
        stack->array[i] = POISON;
    }
    stack->array[0] = CANARRAY;
    stack->array[capacity + 1] = CANARRAY;

    DPRINTF("stack init with poison values and canarrays\n");
}

error_info_t stackPop(stack_t* stack, element_t* value) {
    assert(stack);
    DPRINTF("---\nbefore pop: elcount: %llu; capacity: %llu\n", stack->elementCount, stack->capacity);

    STACK_VALID(stack);

    if (stack->elementCount == 0) {
        *value = POISON;
        return {SUCCESS};
    }

    element_t result = stack->array[stack->elementCount - 1 + 1]; //защита канарейкой
    stack->array[stack->elementCount - 1 + 1] = POISON; // тут тоже
    stack->elementCount--;

    STACK_VALID(stack);

    DPRINTF("after pop: elcount: %llu; capacity: %llu\n", stack->elementCount, stack->capacity);
    *value = result;

    return {SUCCESS};
}

error_info_t stackPush(stack_t *stack, element_t element) {
    assert(stack);
    DPRINTF("---\nbefore push: elcount: %llu; capacity: %llu\n", stack->elementCount, stack->capacity);

    STACK_VALID(stack);

    if (stack->elementCount >= stack->capacity) {
        stack->array[stack->capacity + 1] = POISON;

        size_t newCapacity = stack->capacity * 2 + 3; //защита канарейкой
        DPRINTF("stack full, reallocating to size: %llu\n", newCapacity);
        stack->array = (element_t*) realloc(stack->array, (newCapacity + 2) * sizeof(element_t)); //защита канарейкой
        stack->capacity = newCapacity;

        stack->array[stack->capacity + 1] = CANARRAY;
    }

    stack->array[stack->elementCount + 1] = element; //защита канарейкой
    stack->elementCount++;

    STACK_VALID(stack);

    DPRINTF("after push: elcount: %llu; capacity: %llu\n", stack->elementCount, stack->capacity);

    return {SUCCESS};
}

error_info_t printStack(stack_t* stack) {
    assert(stack);

    STACK_VALID(stack);

    DPRINTF("---\n" "printing stack {\n");
    for (size_t i = 1; i < stack->elementCount + 1; i++) { //защита канарейкой
        printf("\tel[%llu] = ", i);
        printf(REG, stack->array[i]);
        printf("\n");
    }
    DPRINTF("}\n");

    return {SUCCESS};
}


