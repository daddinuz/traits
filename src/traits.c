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
static FILE *__gStream = NULL;

void stream(FILE *s) {
    __gStream = s;
}

#define STREAM ((NULL != __gStream) ? __gStream : stdout)

#ifndef NO_COLOR
#define COLOR_NORMAL    "\x1B[00m"
#define COLOR_RED       "\x1B[31m"
#define COLOR_GREEN     "\x1B[32m"
#define COLOR_YELLOW    "\x1B[33m"
#define COLOR_BLUE      "\x1B[34m"
#else
#define COLOR_NORMAL    ""
#define COLOR_RED       ""
#define COLOR_GREEN     ""
#define COLOR_YELLOW    ""
#define COLOR_BLUE      ""
#endif

#define DUMP(file, line, message, ...)   do {                                                               \
        fprintf(STREAM, COLOR_YELLOW "\t\tFile: %s:%d" COLOR_NORMAL "\n\t\t\t" COLOR_NORMAL, file, line);   \
        fprintf(STREAM, message, __VA_ARGS__);                                                              \
        fputs("\n", STREAM);                                                                                \
    } while(0)

/*
 *
 */
static int __gRun = 0;
static int __gFailed = 0;
static int __gSkipped = 0;
static int __gState = EXIT_SUCCESS;

void __launch(const char *name, test_t test) {
    __gRun += 1;
    __gState = EXIT_SUCCESS;
    fprintf(STREAM, "Test: " COLOR_BLUE "%s" COLOR_NORMAL "...\n", name);
    if (NULL != test) {
        test();
    }
}

void _run(const char *name, test_t test) {
    __launch(name, test);
    if (__gState <= 0) {
        fprintf(STREAM, COLOR_GREEN "\t[ SUCCESS ]" COLOR_NORMAL "\n");
    } else {
        fprintf(STREAM, COLOR_RED "\t[ FAILURE ]" COLOR_NORMAL "\n");
        __gFailed += 1;
    }
}

void _skip(const char *name) {
    __launch(name, NULL);
    fprintf(STREAM, COLOR_YELLOW "\t[ SKIPPED ]" COLOR_NORMAL "\n");
    __gSkipped += 1;
}

int report(void) {
    fprintf(STREAM, "\n%8s: % 3d\n%8s: % 3d\n%8s: % 3d\n%8s: % 3d\n\n",
            "tests", __gRun, "success", __gRun - (__gFailed + __gSkipped), "failure", __gFailed, "skipped", __gSkipped);
    return __gFailed;
}

/*
 * operators
 */
typedef enum __operator_t {
    OPERATOR_EQUAL = 0,
    OPERATOR_NOT_EQUAL,
    OPERATOR_GREATER_EQUAL,
    OPERATOR_GREATER,
    OPERATOR_LESS_EQUAL,
    OPERATOR_LESS,
} __operator_t;

#define OP_EQUAL           !=
#define OP_NOT_EQUAL       ==
#define OP_GREATER_EQUAL   >
#define OP_GREATER         >=
#define OP_LESS_EQUAL      <
#define OP_LESS            <=

#define __handle_op(expected, op, got, format, ...) \
    if ( expected op got ) {                        \
        __gState += 1;                              \
        DUMP(file, line, format, __VA_ARGS__);      \
    }                                               \
    break

/*
 * boolean
 */
void __traits_bool(__operator_t op, const bool expected, const bool got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            __handle_op(expected, OP_EQUAL, got, "expected: %s, got: %s", bool2str(expected), bool2str(got));
        case OPERATOR_NOT_EQUAL:
            __handle_op(expected, OP_NOT_EQUAL, got, "expected: %s, got: %s", bool2str(expected), bool2str(got));
        default:
            fprintf(stderr, "Unknown bool operator.\n");
            abort();
    }
}

void _ASSERT(const bool condition, const char *file, int line) {
    __traits_bool(OPERATOR_EQUAL, true, condition, file, line);
}

void _ASSERT_TRUE(const bool got, const char *file, int line) {
    __traits_bool(OPERATOR_EQUAL, true, got, file, line);
}

void _ASSERT_FALSE(const bool got, const char *file, int line) {
    __traits_bool(OPERATOR_EQUAL, false, got, file, line);
}

/*
 * pointer
 */
void __traits_ptr(__operator_t op, const void *const expected, const void *const got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            __handle_op(expected, OP_EQUAL, got, "expected: %p, got: %p", expected, got);
        case OPERATOR_NOT_EQUAL:
            __handle_op(expected, OP_NOT_EQUAL, got, "expected: %p, got: %p", expected, got);
        default:
            fprintf(stderr, "Unknown pointer operator.\n");
            abort();
    }
}

void _ASSERT_PTR_EQUAL(const void *expected, const void *got, const char *file, int line) {
    __traits_ptr(OPERATOR_EQUAL, expected, got, file, line);
}

void _ASSERT_PTR_NOT_EQUAL(const void *expected, const void *got, const char *file, int line) {
    __traits_ptr(OPERATOR_NOT_EQUAL, expected, got, file, line);
}

void _ASSERT_PTR_NULL(const void *got, const char *file, int line) {
    __traits_ptr(OPERATOR_EQUAL, NULL, got, file, line);
}

void _ASSERT_PTR_NOT_NULL(const void *got, const char *file, int line) {
    __traits_ptr(OPERATOR_NOT_EQUAL, NULL, got, file, line);
}

/*
 * integer
 */
#define DEFINE(_lower, _upper, _fmt)                                                                                                \
    void __traits_##_lower(__operator_t op, const _lower expected, const _lower got, const char *file, int line) {                  \
        switch (op) {                                                                                                               \
            case OPERATOR_EQUAL:                                                                                                    \
                __handle_op(expected, OP_EQUAL, got, "expected: %" _fmt ", got: %" _fmt, expected, got);                            \
            case OPERATOR_NOT_EQUAL:                                                                                                \
                __handle_op(expected, OP_NOT_EQUAL, got, "expected not equal: %" _fmt ", got: %" _fmt, expected, got);              \
            case OPERATOR_GREATER_EQUAL:                                                                                            \
                __handle_op(expected, OP_GREATER_EQUAL, got, "expected greater equal than: %" _fmt ", got: %" _fmt, expected, got); \
            case OPERATOR_GREATER:                                                                                                  \
                __handle_op(expected, OP_GREATER, got, "expected greater than: %" _fmt ", got: %" _fmt, expected, got);             \
            case OPERATOR_LESS_EQUAL:                                                                                               \
                __handle_op(expected, OP_LESS_EQUAL, got, "expected less equal than: %" _fmt ", got: %" _fmt, expected, got);       \
            case OPERATOR_LESS:                                                                                                     \
                __handle_op(expected, OP_LESS, got, "expected less than: %" _fmt ", got: %" _fmt, expected, got);                   \
            default:                                                                                                                \
                fprintf(stderr, "Unknown int operator.\n");                                                                         \
                abort();                                                                                                            \
        }                                                                                                                           \
    }

#define OP_DEFINE(_lower, _upper, _operator)                                                                    \
    void _ASSERT_##_upper##_##_operator(const _lower expected, const _lower got, const char *file, int line) {  \
        __traits_##_lower(OPERATOR_##_operator, expected, got, file, line);                                     \
    }

DEFINE(uint8_t, UINT8, PRIu8)
OP_DEFINE(uint8_t, UINT8, EQUAL)
OP_DEFINE(uint8_t, UINT8, NOT_EQUAL)
OP_DEFINE(uint8_t, UINT8, GREATER_EQUAL)
OP_DEFINE(uint8_t, UINT8, GREATER)
OP_DEFINE(uint8_t, UINT8, LESS_EQUAL)
OP_DEFINE(uint8_t, UINT8, LESS)

DEFINE(uint16_t, UINT16, PRIu16)
OP_DEFINE(uint16_t, UINT16, EQUAL)
OP_DEFINE(uint16_t, UINT16, NOT_EQUAL)
OP_DEFINE(uint16_t, UINT16, GREATER_EQUAL)
OP_DEFINE(uint16_t, UINT16, GREATER)
OP_DEFINE(uint16_t, UINT16, LESS_EQUAL)
OP_DEFINE(uint16_t, UINT16, LESS)

DEFINE(uint32_t, UINT32, PRIu32)
OP_DEFINE(uint32_t, UINT32, EQUAL)
OP_DEFINE(uint32_t, UINT32, NOT_EQUAL)
OP_DEFINE(uint32_t, UINT32, GREATER_EQUAL)
OP_DEFINE(uint32_t, UINT32, GREATER)
OP_DEFINE(uint32_t, UINT32, LESS_EQUAL)
OP_DEFINE(uint32_t, UINT32, LESS)

DEFINE(size_t, SIZE, "zu")
OP_DEFINE(size_t, SIZE, EQUAL)
OP_DEFINE(size_t, SIZE, NOT_EQUAL)
OP_DEFINE(size_t, SIZE, GREATER_EQUAL)
OP_DEFINE(size_t, SIZE, GREATER)
OP_DEFINE(size_t, SIZE, LESS_EQUAL)
OP_DEFINE(size_t, SIZE, LESS)

DEFINE(unsigned, UINT, "u")
OP_DEFINE(unsigned, UINT, EQUAL)
OP_DEFINE(unsigned, UINT, NOT_EQUAL)
OP_DEFINE(unsigned, UINT, GREATER_EQUAL)
OP_DEFINE(unsigned, UINT, GREATER)
OP_DEFINE(unsigned, UINT, LESS_EQUAL)
OP_DEFINE(unsigned, UINT, LESS)

DEFINE(int8_t, INT8, PRId8)
OP_DEFINE(int8_t, INT8, EQUAL)
OP_DEFINE(int8_t, INT8, NOT_EQUAL)
OP_DEFINE(int8_t, INT8, GREATER_EQUAL)
OP_DEFINE(int8_t, INT8, GREATER)
OP_DEFINE(int8_t, INT8, LESS_EQUAL)
OP_DEFINE(int8_t, INT8, LESS)

DEFINE(int16_t, INT16, PRId16)
OP_DEFINE(int16_t, INT16, EQUAL)
OP_DEFINE(int16_t, INT16, NOT_EQUAL)
OP_DEFINE(int16_t, INT16, GREATER_EQUAL)
OP_DEFINE(int16_t, INT16, GREATER)
OP_DEFINE(int16_t, INT16, LESS_EQUAL)
OP_DEFINE(int16_t, INT16, LESS)

DEFINE(int32_t, INT32, PRId32)
OP_DEFINE(int32_t, INT32, EQUAL)
OP_DEFINE(int32_t, INT32, NOT_EQUAL)
OP_DEFINE(int32_t, INT32, GREATER_EQUAL)
OP_DEFINE(int32_t, INT32, GREATER)
OP_DEFINE(int32_t, INT32, LESS_EQUAL)
OP_DEFINE(int32_t, INT32, LESS)

DEFINE(int, INT, "d")
OP_DEFINE(int, INT, EQUAL)
OP_DEFINE(int, INT, NOT_EQUAL)
OP_DEFINE(int, INT, GREATER_EQUAL)
OP_DEFINE(int, INT, GREATER)
OP_DEFINE(int, INT, LESS_EQUAL)
OP_DEFINE(int, INT, LESS)

#if SUPPORT_64BIT
DEFINE(uint64_t, UINT64, PRIu64)
OP_DEFINE(uint64_t, UINT64, EQUAL)
OP_DEFINE(uint64_t, UINT64, NOT_EQUAL)
OP_DEFINE(uint64_t, UINT64, GREATER_EQUAL)
OP_DEFINE(uint64_t, UINT64, GREATER)
OP_DEFINE(uint64_t, UINT64, LESS_EQUAL)
OP_DEFINE(uint64_t, UINT64, LESS)

DEFINE(int64_t, INT64, PRId64)
OP_DEFINE(int64_t, INT64, EQUAL)
OP_DEFINE(int64_t, INT64, NOT_EQUAL)
OP_DEFINE(int64_t, INT64, GREATER_EQUAL)
OP_DEFINE(int64_t, INT64, GREATER)
OP_DEFINE(int64_t, INT64, LESS_EQUAL)
OP_DEFINE(int64_t, INT64, LESS)
#endif

#undef OP_DEFINE
#undef DEFINE
