#include "../../include/dump/dump.h"

#include "common.h"
#include "stack.h"
#include "verifier/verifier.h"


static void dumpData(const stack_t *stack) {
    if (stack->array == NULL) {
        DPRINTF("\t\t\t[NULL DATA POINTER!]\n");
    } else if (stack->elementCount <= 0) {
        DPRINTF("\t\t\t[empty]\n");
    } else {
        // Show out-of-bounds elements if index exceeds capacity
        if ((size_t) stack->elementCount > stack->capacity) {
            DPRINTF("\t\t\t--- MEMORY CORRUPTION DETECTED ---\n");
            size_t max = stack->elementCount > MAX_REASONABLE_CAPACITY ? 10 : stack->elementCount;
            for (size_t i = 0; i < max; i++) {
                DPRINTF("\t\t\t**el[%llu]: " REG "\n", i, stack->array[i]);
            }
        }
        else {
            for (size_t i = 0; i < stack->elementCount; i++) {
                DPRINTF("\t\t\tel[%llu]: " REG "\n", i, stack->array[i]);
            }
            for (size_t i = stack->elementCount; i < stack->capacity; i++) {
                DPRINTF("\t\t\t*el[%llu]: " REG "\n", i, stack->array[i]);
            }
        }
    }
}

error_info_t stackDump(const stack_t *stack,
                       const char *file,
                       int line,
                       const char *function,
                       error_info_t validation) {
    DPRINTF("StackDump() {\n");

    if (stack == NULL) {
        DPRINTF("\tStack [NULL] { ERROR! NULL POINTER\n");
        DPRINTF("\t}\n");
        DPRINTF("}\n");
        return {NULL_PTR, "null pointer in dump"};
    }

    const char *status = (validation.err_code == SUCCESS) ? "" : "  ERROR! ";
    const char *error_msg = (validation.err_code != SUCCESS) ? validation.msg : "";

    DPRINTF("\t%s  [%p] {%s%s  from %s() at \n\t\t\t%s:%d\n",
            "stack", stack, status, error_msg,
            function, file, line);

    // Print size with validation
    DPRINTF("\t\telements count = %llu", stack->elementCount);
    if (stack->elementCount > stack->capacity) {
        DPRINTF(" (SIZE EXCEEDS CAPACITY!)");
    }
    if (stack->elementCount > MAX_REASONABLE_CAPACITY) {
        DPRINTF(" (SIZE EXCEEDS REASONABLE MEASURE!)");
    }
    DPRINTF(";\n");

    // Print capacity
    DPRINTF("\t\tcapacity = %llu", stack->capacity);
    if (stack->capacity > MAX_REASONABLE_CAPACITY) {
        DPRINTF(" (BAD CAPACITY! EXCEEDS REASONABLE MEASURE!)");
    }
    DPRINTF(";\n");

    // Print data array
    DPRINTF("\t\tdata[%p] {\n", stack->array);

    dumpData(stack);

    DPRINTF("\t\t}\n");
    DPRINTF("\t}\n");
    DPRINTF("}\n");

    return {SUCCESS};
}
