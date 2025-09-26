#include "stack.h"

#include <cstdio>
#include <cstring>

#include "common.h"

size_t getSize(elementType_t type) {
    static size_t arr[] = {sizeof(STRING), sizeof(LONG), sizeof(INT), sizeof(DOUBLE), sizeof(CHAR)};

    return arr[type];
}

void initStack(stack_t* stack, size_t capacity, elementType_t elementType) {
    stack->array = calloc(capacity, getSize(elementType));
    stack->elementCount = 0;
    stack->capacity = capacity;
    stack->elementSize = getSize(elementType);
    stack->elementType = elementType;
}

void* stackPop(stack_t* stack) {
    size_t index = (stack->elementCount-1);
    auto element = getElement(stack, index);

    DPRINTF("pop from index %lld: ", index);
    DPrintElement(element, stack->elementType);
    printf("\n");

    stack->elementCount--;

    return element;
}

void* stackPush(stack_t* stack, void* element) {
    size_t index = (stack->elementCount - 1);
    DPRINTF("push el-");
    DPrintElement(element, stack->elementType);
    DPRINTF(" to index %lld: \n", index + 1);
    if (stack->elementCount >= stack->capacity) {
        DPRINTF("--- elements count is-%lld and capacity is-%lld reallocating\n", stack->elementCount, stack->capacity);
        stack->capacity *= 2;
        stack->array = realloc(stack->array, stack-> capacity * stack->elementSize);
    }

    void* target = getElement(stack, stack->elementCount);
    memcpy(target, element, stack->elementSize);
    stack->elementCount++;

    DPRINTF("after push elements Count-%lld capacity-%lld\n", stack->elementCount, stack->capacity);

    return element;
}

void printElementI(const stack_t* stack, size_t index) {
    printElement(getElement(stack, index), stack-> elementType);
}

void printElement(void* element, elementType_t elementType) {
    switch (elementType) {
        case STRING:
            printf("%s", (char*) element);
            break;
        case LONG:
            printf("%ld", *(long*)element);
            break;
        case DOUBLE:
            printf("%f", *(double*)element);
            break;
        case CHAR:
            printf("%c", *(char*)element);
            break;
        case INT:
            printf("%d", *(int*)element);
            break;
        default:
            exit(1);
    }
}

void DPrintElement(void* element, elementType_t elementType) {
    switch (elementType) {
        case STRING:
            DPRINTF("%s", (char*) element);
            break;
        case LONG:
            DPRINTF("%ld", *(long*)element);
            break;
        case DOUBLE:
            DPRINTF("%f", *(double*)element);
            break;
        case CHAR:
            DPRINTF("%c", *(char*)element);
            break;
        case INT:
            DPRINTF("%d", *(int*)element);
            break;
        default:
            exit(1);
    }
}

void* getElement(const stack_t* stack, size_t index) {
     return (char*) stack->array + index * stack->elementSize;
}

void printStack(stack_t* stack) {
    size_t index = (stack->elementCount - 1);
    DPRINTF("printing stack with size-%lld:\n", stack->elementCount+1);
    for (size_t i = index; i > 0; i--) {
        void* element = getElement(stack, i);
        printf("el-%llu: ", i);
        printElement(element, stack->elementType);
        printf("\n");
    }

    printf("el-%ld: ", 0L);
    printElement(stack->array, stack->elementType);
    printf("\n");
}