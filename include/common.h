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

#define SAFE_CALL(func) \
    do { \
        error_info_t sf_call_res_777 = (func); \
        if (sf_call_res_777.err_code != SUCCESS) { \
            fprintf(stderr, "ERROR [%s:%d]: %s (code %d)\n", \
            __FILE__, __LINE__, sf_call_res_777.msg, sf_call_res_777.err_code); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define BEGIN do {
#define END   } while (0);

//DEBUG printf with immediate flush
#ifdef DEBUG
#define DPRINTF(...) \
    BEGIN \
        printf(__VA_ARGS__); \
        fflush(stdout); \
    END


#else
    #define DPRINTF(...) ;
#endif //DEBUG

//define for printing in stderr
#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)


#endif //COMMON_H
