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

void printStack(stack_t* stack);

#define STACK_VALID(stack) \
    do { \
        error_info_t valid_res_777 = validateStack(stack); \
        if (valid_res_777.err_code != SUCCESS) { \
            SAFE_CALL(stackDump(stack, __FILE__, __LINE__, __func__, valid_res_777)); \
            return valid_res_777;\
        } \
    } while(0)

#endif //STACK_STACK_H