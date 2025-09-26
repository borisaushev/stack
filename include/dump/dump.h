#ifndef STACK_DUMP_H
#define STACK_DUMP_H
#include "common.h"
#include "stack.h"


error_info_t stackDump(const stack_t *stack, const char *file, int line, const char *function, error_info_t validation);

#endif //STACK_DUMP_H