#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <algorithm>

typedef enum elementType {
    STRING = 0, LONG, INT, DOUBLE, CHAR,
} elementType_t;

typedef struct stack {
    void* array;
    size_t capacity;
    size_t elementCount;
    size_t elementSize;
    elementType_t elementType;
} stack_t;

void initStack(stack_t* stack, size_t capacity, elementType_t elementType);

void* stackPop(stack_t* stack);

void* stackPush(stack_t* stack, void* element);

void printStack(stack_t* stack);

void DPrintElement(void* element, elementType_t elementType);

void* getElement(const stack_t* stack, size_t index);

void printElementI(const stack_t* stack, size_t index);

void printElement(void* element, elementType_t elementType);

#endif //STACK_STACK_H