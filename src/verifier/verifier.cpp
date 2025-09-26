#include "verifier.h"

#include <cstdio>

#include "common.h"
#include "stack.h"

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

    // Check index bounds
    if ((size_t)stack->elementCount > stack->capacity || stack->elementCount > MAX_REASONABLE_CAPACITY) {
        return {INVALID_INDEX, "index too big"};
    }


    DPRINTF("=== STACK VALIDATION PASSED ===\n");
    return {SUCCESS};
}
