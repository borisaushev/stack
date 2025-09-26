#ifndef COMMON_H
#define COMMON_H

typedef enum errors {
    SUCCESS = 0,
    NULL_PTR,
    INVALID_CAPACITY,
    INVALID_INDEX,
    INVALID_EL_SIZE,
    INVALID_TYPE,
    INVALID_PTR
} error_code_t;

typedef struct error_info {
    error_code_t err_code;
    const char *msg;
} error_info_t;

#define SAFE_CALL(func) \
    do { \
        error_info_t result = (func); \
        if (result.err_code != SUCCESS) { \
            fprintf(stderr, "ERROR [%s:%d]: %s (code %d)\n", \
            __FILE__, __LINE__, result.msg, result.err_code); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

//DEBUG printf with immediate flush
#ifdef DEBUG
#define DPRINTF(...) \
    do { \
        printf(__VA_ARGS__); \
        fflush(stdout); \
    } while(0)
#else
    #define DPRINTF(...) ;
#endif //DEBUG

//define for printing in stderr
#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)


#endif //COMMON_H
