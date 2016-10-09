/*
 *  C Source File
 *
 *  Author: Davide Di Carlo
 *  Date:   October 10, 2016
 *  email:  daddinuz@gmail.com
 */

#include "traits.h"

/*
 * Logging
 */
static FILE *_gStream = NULL;

void stream(FILE *s) {
    _gStream = s;
}

#define STREAM ((NULL != _gStream) ? _gStream : stdout)

#define COLOR_NORMAL    "\x1B[00m"
#define COLOR_RED       "\x1B[31m"
#define COLOR_GREEN     "\x1B[32m"
#define COLOR_YELLOW    "\x1B[33m"
#define COLOR_BLUE      "\x1B[34m"
#define COLOR_MAGENTA   "\x1B[35m"
#define COLOR_CYAN      "\x1B[36m"
#define COLOR_WHITE     "\x1B[37m"

#define dump(file, line, message, ...)   do {                                                               \
        fprintf(STREAM, COLOR_YELLOW "\t\tFile: %s:%d" COLOR_NORMAL "\n\t\t\t" COLOR_NORMAL, file, line);   \
        fprintf(STREAM, message, __VA_ARGS__);                                                              \
        fputs("\n", STREAM);                                                                                \
    } while(0)

/*
 * Test cases definition
 */
static int _gGlobalState = EXIT_SUCCESS;
static int _gCurrentState = EXIT_SUCCESS;

void launch(const char* test_case, test_case_t ptr, call_t call) {
    _gCurrentState = EXIT_SUCCESS;
    fprintf(STREAM, "Test case: " COLOR_BLUE "%s" COLOR_NORMAL "...\n", test_case);
    ptr();
    switch (call) {
        case CALL_RUN:
            if (_gCurrentState <= 0) { 
                fprintf(STREAM, COLOR_GREEN "\t[ SUCCESS ]" COLOR_NORMAL "\n");
            } else {
                fprintf(STREAM, COLOR_RED "\t[ FAILURE ]" COLOR_NORMAL "\n");
                _gGlobalState = EXIT_FAILURE;
            }
            break;
        case CALL_SKIP:
            fprintf(STREAM, COLOR_YELLOW "\t[ SKIPPED ]" COLOR_NORMAL "\n");
            break;
        default:
            fprintf(stderr, "Unknown test mode.\n");
            abort();
    }
}

/*
 * operators
 */
#define OP_EQUAL           !=
#define OP_NOT_EQUAL       ==
#define OP_GREATER_EQUAL   >
#define OP_GREATER         >=
#define OP_LESS_EQUAL      <
#define OP_LESS            <=

#define _handle_op(expected, op, got, format, ...)  \
    if ( expected op got ) {                        \
        _gCurrentState += 1;                        \
        dump(file, line, format, ##__VA_ARGS__);    \
    }

/*
 * boolean
 */
void __traits_bool(operator_t op, const bool expected, const bool got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            _handle_op(expected, OP_EQUAL, got, "expected: %s, got: %s", bool2str(expected), bool2str(got));
            break;
        case OPERATOR_NOT_EQUAL:
            _handle_op(expected, OP_NOT_EQUAL, got, "expected: %s, got: %s", bool2str(expected), bool2str(got));
            break;
        default:
            fprintf(stderr, "Unknown bool operator.\n");
            abort();
    }
}

/*
 * integer
 */
void __traits_int(operator_t op, const int expected, const int got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            _handle_op(expected, OP_EQUAL, got, "expected: %d, got: %d", expected, got);
            break;
        case OPERATOR_NOT_EQUAL:
            _handle_op(expected, OP_NOT_EQUAL, got, "expected not equal: %d, got: %d", expected, got);
            break;
        case OPERATOR_GREATER_EQUAL:
            _handle_op(expected, OP_GREATER_EQUAL, got, "expected greater equal than: %d, got: %d", expected, got);
            break;
        case OPERATOR_GREATER:
            _handle_op(expected, OP_GREATER, got, "expected greater than: %d, got: %d", expected, got);
            break;
        case OPERATOR_LESS_EQUAL:
            _handle_op(expected, OP_LESS_EQUAL, got, "expected less equal than: %d, got: %d", expected, got);
            break;
        case OPERATOR_LESS:
            _handle_op(expected, OP_LESS, got, "expected less than: %d, got: %d", expected, got);
            break;
        default:
            fprintf(stderr, "Unknown int operator.\n");
            abort();
    }
}

void __traits_size_t(operator_t op, const size_t expected, const size_t got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            _handle_op(expected, OP_EQUAL, got, "expected: %zu, got: %zu", expected, got);
            break;
        case OPERATOR_NOT_EQUAL:
            _handle_op(expected, OP_NOT_EQUAL, got, "expected not equal: %zu, got: %zu", expected, got);
            break;
        case OPERATOR_GREATER_EQUAL:
            _handle_op(expected, OP_GREATER_EQUAL, got, "expected greater equal than: %zu, got: %zu", expected, got);
            break;
        case OPERATOR_GREATER:
            _handle_op(expected, OP_GREATER, got, "expected greater than: %zu, got: %zu", expected, got);
            break;
        case OPERATOR_LESS_EQUAL:
            _handle_op(expected, OP_LESS_EQUAL, got, "expected less equal than: %zu, got: %zu", expected, got);
            break;
        case OPERATOR_LESS:
            _handle_op(expected, OP_LESS, got, "expected less than: %zu, got: %zu", expected, got);
            break;
        default:
            fprintf(stderr, "Unknown size_t operator.\n");
            abort();
    }
}

/*
 * pointer
 */
void __traits_pointer(operator_t op, const void *const expected, const void *const got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            _handle_op(expected, OP_EQUAL, got, "expected: %p, got: %p", expected, got);
            break;
        case OPERATOR_NOT_EQUAL:
            _handle_op(expected, OP_NOT_EQUAL, got, "expected: %p, got: %p", expected, got);
            break;
        default:
            fprintf(stderr, "Unknown pointer operator.\n");
            abort();
    }
}
