#ifndef STACK_VERIFIER_H
#define STACK_VERIFIER_H

#include "common.h"
#include "stack.h"

const size_t MAX_REASONABLE_CAPACITY = 1024 * 1024 * 1024;

error_info_t validateStack(const stack_t* stack);

#endif //STACK_VERIFIER_H