#include <cstdio>

#include "common.h"
#include "stack.h"

#include "dump.h"
#include "verifier.h"

error_info_t stackDump(const stack_t *stack, const char *file, int line, const char *function) {
    DPRINTF("StackDump() {\n");

    if (stack == NULL) {
        DPRINTF("    Stack [NULL] { ERROR! NULL POINTER\n");
        DPRINTF("    }\n");
        DPRINTF("}\n");
        return {NULL_PTR, "null pointer in dump"};
    }

    error_info_t validation = validateStack(stack);
    const char *status = (validation.err_code == SUCCESS) ? "" : "  ERROR! ";
    const char *error_msg = (validation.err_code != SUCCESS) ? validation.msg : "";

    DPRINTF("   %s  [%p] {%s%s  from %s() at %s:%d\n",
            "stack", (void*)stack, status, error_msg,
            function, file, line);

    // Print size with validation
    DPRINTF("        size = %zd", stack->elementCount);
    if (stack->elementCount < 0) {
        DPRINTF(" (BAD SIZE! NEGATIVE!)");
    } else if ((size_t) stack->elementCount > stack->capacity) {
        DPRINTF(" (BAD SIZE! EXCEEDS CAPACITY!)");
    }
    DPRINTF(";\n");

    // Print capacity
    DPRINTF("        capacity = %zu", stack->capacity);
    if (stack->capacity == 0) {
        DPRINTF(" (ZERO CAPACITY!)");
    }
    DPRINTF(";\n");

    // Print data array
    DPRINTF("        data[%p] {\n", stack->array);

    if (stack->array == NULL) {
        DPRINTF("            [NULL DATA POINTER!]\n");
    } else if (stack->elementCount <= 0) {
        DPRINTF("            [empty]\n");
    } else {
        for (size_t i = 0; i < stack->elementCount; i++) {
            printElementI(stack, i);
        }

        // Show out-of-bounds elements if index exceeds capacity
        if ((size_t) stack->elementCount > stack->capacity) {
            DPRINTF("            --- MEMORY CORRUPTION DETECTED ---\n");
            for (size_t i = stack->capacity; i <= (size_t) stack->elementCount && i < stack->capacity + 5; i++) {
                DPRINTF("             [%zu] = ", i);
                if (i < stack->capacity * 2) {
                    printElementI(stack, i);
                } else {
                    DPRINTF("<memory out of safe bounds>\n");
                }
            }
        }
    }

    DPRINTF("        }\n");
    DPRINTF("    }\n");
    DPRINTF("}\n");

    return {SUCCESS};
}
