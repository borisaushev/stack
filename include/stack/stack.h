#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <algorithm>

#include "common.h"

typedef struct stack {
    element_t* array;
    size_t capacity;
    size_t elementCount;
} stack_t;

void initStack(stack_t* stack, size_t capacity);

error_info_t stackPop(stack_t* stack, element_t* value);

error_info_t stackPush(stack_t *stack, element_t element);

error_info_t printStack(stack_t* stack);

#endif //STACK_STACK_H