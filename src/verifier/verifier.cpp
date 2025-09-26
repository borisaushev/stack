
#include "dump.h"
#include "verifier.h"

#include <cstdio>

#include "common.h"

error_info_t validateStack(const stack_t* stack) {
    DPRINTF("=== STACK VALIDATION STARTED ===\n");

    if (stack == NULL) {
        return {NULL_PTR, "null stack"};
    }
    if (stack->array == NULL) {
        return {NULL_PTR, "null array"};
    }

    if (stack->capacity > MAX_REASONABLE_CAPACITY) {
        return {INVALID_CAPACITY, "stack size is too big"};
    }

    // Check element size
    if (stack->elementSize <= 0 || stack->elementSize > MAX_REASONABLE_ELEMENT_SIZE) {
        return {INVALID_EL_SIZE, "element size is invalid"};
    }

    // Check index bounds
    if ((size_t)stack->elementCount > stack->capacity) {
        return {INVALID_INDEX, "index too big"};
    }

    // Check item type validity
    if (stack->elementType < STRING || stack->elementType > CHAR) {
        return {INVALID_TYPE, "element type is invalid"};
    }

    // Validate element size against item type
    size_t expectedSize = 0;
    switch (stack->elementType) {
        case STRING: expectedSize = sizeof(char *);
            break;
        case LONG: expectedSize = sizeof(long);
            break;
        case INT: expectedSize = sizeof(int);
            break;
        case DOUBLE: expectedSize = sizeof(double);
            break;
        case CHAR: expectedSize = sizeof(char);
            break;
        default:
            return {INVALID_TYPE, "element type is invalid"};
    }

    if (stack->elementSize != expectedSize) {
        return {INVALID_EL_SIZE, "element size doesnt match expected"};
    }


    DPRINTF("=== STACK VALIDATION PASSED ===\n");
    return {SUCCESS};
}
