#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef int element_t;
# define REG "%d"
const int POISON = 777;
const int CANARRAY = 0xAB0BA;

typedef enum errors {
    SUCCESS = 0,
    NULL_PTR,
    INVALID_CAPACITY,
    INVALID_INDEX,
    INVALID_PTR,
    CONTENTS_MODIFIED,
} error_code_t;

typedef struct error_info {
    error_code_t err_code;
    const char *msg;
} error_info_t;

#define BEGIN do {
#define END   } while (0);

//DEBUG printf with immediate flush
#ifdef DEBUG
#define DPRINTF(...) \
    BEGIN \
        printf("\033[33m"); \
        printf(__VA_ARGS__); \
        printf("\033[0m"); \
        fflush(stdout); \
    END
#else
    #define DPRINTF(...) ;
#endif //DEBUG

//define for printing in stderr
#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)

#define SAFE_CALL(func) \
    BEGIN \
        error_info_t sf_call ## __LINE__ = (func); \
        if (sf_call ## __LINE__.err_code != SUCCESS) { \
            PRINTERR("ERROR [%s:%d]: %s (code %d)\n", \
            __FILE__, __LINE__, sf_call ## __LINE__.msg, sf_call ## __LINE__.err_code); \
            exit(EXIT_FAILURE); \
        } \
    END

#define STACK_VALID(stack) \
    BEGIN \
        error_info_t valid ## __LINE__ = validateStack(stack); \
        if (valid ## __LINE__.err_code != SUCCESS) { \
            SAFE_CALL(stackDump(stack, __FILE__, __LINE__, __func__, valid ## __LINE__)); \
            return valid ## __LINE__;\
        } \
    END


#endif //COMMON_H
