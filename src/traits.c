/*
 *  C Source File
 *
 *  Author: Davide Di Carlo
 *  Date:   October 10, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdarg.h>
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

void notify(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(STREAM, COLOR_YELLOW "\n===> " COLOR_NORMAL);
    vfprintf(STREAM, format, args);
    va_end(args);
}

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

void _skip(const char *name, test_t _) {
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
    OPERATOR_WITHIN,
} __operator_t;

#define OP_EQUAL(_e, _g)                ((_g) == (_e))
#define OP_NOT_EQUAL(_e, _g)            ((_g) != (_e))
#define OP_GREATER_EQUAL(_e, _g)        ((_g) >= (_e))
#define OP_GREATER(_e, _g)              ((_g) >  (_e))
#define OP_LESS_EQUAL(_e, _g)           ((_g) <= (_e))
#define OP_LESS(_e, _g)                 ((_g) <  (_e))
#define OP_WITHIN(_d, _e, _g)           (((_g) >= ((_e) - (_d))) && ((_g) <= ((_e) + (_d))))

#define __handle_op(op, format, ...)            \
    if ( ! op ) {                               \
        __gState += 1;                          \
        DUMP(file, line, format, __VA_ARGS__);  \
    }                                           \
    break

/*
 * boolean
 */
void __traits_bool(__operator_t op, const bool expected, const bool got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            __handle_op(OP_EQUAL(expected, got), "expected: %s, got: %s", bool2str(expected), bool2str(got));
        case OPERATOR_NOT_EQUAL:
            __handle_op(OP_NOT_EQUAL(expected, got), "expected: %s, got: %s", bool2str(expected), bool2str(got));
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
            __handle_op(OP_EQUAL(expected, got), "expected: %p, got: %p", expected, got);
        case OPERATOR_NOT_EQUAL:
            __handle_op(OP_NOT_EQUAL(expected, got), "expected: %p, got: %p", expected, got);
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

#define OP_DEFINE(_Type, _Identifier, _Operator)                                                                    \
    void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line) {  \
        __traits_##_Type(OPERATOR_##_Operator, 0, expected, got, file, line);                                  \
    }

#define OP_COMPOUND_DEFINE(_Type, _Identifier, _Operator)                                                                               \
    void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line) {  \
        __traits_##_Type(OPERATOR_##_Operator, delta, expected, got, file, line);                                                  \
    }

#define DEFINE(_Type, _Identifier, _fmt)                                                                                                                \
    void __traits_##_Type(__operator_t op, const _Type delta, const _Type expected, const _Type got, const char *file, int line) {              \
        switch (op) {                                                                                                                               \
            case OPERATOR_EQUAL:                                                                                                                    \
                __handle_op(OP_EQUAL(expected, got), "expected: %" _fmt ", got: %" _fmt, expected, got);                                            \
            case OPERATOR_NOT_EQUAL:                                                                                                                \
                __handle_op(OP_NOT_EQUAL(expected, got), "expected not equal: %" _fmt ", got: %" _fmt, expected, got);                              \
            case OPERATOR_GREATER_EQUAL:                                                                                                            \
                __handle_op(OP_GREATER_EQUAL(expected, got), "expected greater equal than: %" _fmt ", got: %" _fmt, expected, got);                 \
            case OPERATOR_GREATER:                                                                                                                  \
                __handle_op(OP_GREATER(expected, got), "expected greater than: %" _fmt ", got: %" _fmt, expected, got);                             \
            case OPERATOR_LESS_EQUAL:                                                                                                               \
                __handle_op(OP_LESS_EQUAL(expected, got), "expected less equal than: %" _fmt ", got: %" _fmt, expected, got);                       \
            case OPERATOR_LESS:                                                                                                                     \
                __handle_op(OP_LESS(expected, got), "expected less than: %" _fmt ", got: %" _fmt, expected, got);                                   \
            case OPERATOR_WITHIN:                                                                                                                   \
                __handle_op(OP_WITHIN(delta, expected, got), "expected %" _fmt " delta: %" _fmt ", got: %" _fmt, expected, delta, got);             \
            default:                                                                                                                                \
                fprintf(stderr, "Unknown int operator.\n");                                                                                         \
                abort();                                                                                                                            \
        }                                                                                                                                           \
    }                                                                                                                                               \
    OP_DEFINE(_Type, _Identifier, EQUAL)                                                                                                                \
    OP_DEFINE(_Type, _Identifier, NOT_EQUAL)                                                                                                            \
    OP_DEFINE(_Type, _Identifier, GREATER_EQUAL)                                                                                                        \
    OP_DEFINE(_Type, _Identifier, GREATER)                                                                                                              \
    OP_DEFINE(_Type, _Identifier, LESS_EQUAL)                                                                                                           \
    OP_DEFINE(_Type, _Identifier, LESS)                                                                                                                 \
    OP_COMPOUND_DEFINE(_Type, _Identifier, WITHIN)

/*
 * Integer
 */
DEFINE(uint8_t, UINT8, PRIu8)
DEFINE(uint16_t, UINT16, PRIu16)
DEFINE(uint32_t, UINT32, PRIu32)
DEFINE(size_t, SIZE, "zu")
DEFINE(unsigned, UINT, "u")

DEFINE(int8_t, INT8, PRId8)
DEFINE(int16_t, INT16, PRId16)
DEFINE(int32_t, INT32, PRId32)
DEFINE(int, INT, "d")

#if SUPPORT_64BIT
DEFINE(uint64_t, UINT64, PRIu64)
DEFINE(int64_t, INT64, PRId64)
#endif

/*
 * Floating
 */
DEFINE(float, FLOAT, "f")
DEFINE(double, DOUBLE, "f")

#undef OP_DEFINE
#undef DEFINE
