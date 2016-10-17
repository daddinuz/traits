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

const char * severity2color(severity_t severity) {
    switch(severity) {
        case SEVERITY_INFO:
            return COLOR_GREEN;
        case SEVERITY_WARN:
            return COLOR_YELLOW;
        case SEVERITY_ALERT:
            return COLOR_RED;
        default:
            return COLOR_NORMAL;
    }
}

void notify(severity_t severity, const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(STREAM, "\n===> %s", severity2color(severity));
    vfprintf(STREAM, format, args);
    va_end(args);
    fprintf(STREAM, COLOR_NORMAL);
}

#define DUMP(file, line, message, ...)   do {                                                   \
        fprintf(STREAM, "\t%sFile: %s:%d%s\n\t\t", COLOR_YELLOW, file, line, COLOR_NORMAL);     \
        fprintf(STREAM, message, __VA_ARGS__);                                                  \
        fputs("\n", STREAM);                                                                    \
    } while(0)

#define INSPECT(_Format, _Type) "%" _Format " (" str(_Type) ")"

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
    fprintf(STREAM, "Test: %s%s%s...\n", COLOR_BLUE, name, COLOR_NORMAL);
    if (NULL != test) {
        test();
    }
}

void _run(const char *name, test_t test) {
    __launch(name, test);
    if (__gState <= 0) {
        fprintf(STREAM, "%s\t[ SUCCESS ]%s\n", COLOR_GREEN, COLOR_NORMAL);
    } else {
        fprintf(STREAM, "%s\t[ FAILURE ]%s\n", COLOR_RED, COLOR_NORMAL);
        __gFailed += 1;
    }
}

void _skip(const char *name, test_t _) {
    __launch(name, NULL);
    fprintf(STREAM, "%s\t[ SKIPPED ]%s\n", COLOR_YELLOW, COLOR_NORMAL);
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
            __handle_op(OP_EQUAL(expected, got),
                        "expected: " INSPECT("s", bool) ", got: " INSPECT("s", bool), bool2str(expected), bool2str(got));
        case OPERATOR_NOT_EQUAL:
            __handle_op(OP_NOT_EQUAL(expected, got),
                        "expected not equal: " INSPECT("s", bool) ", got: " INSPECT("s", bool), bool2str(expected), bool2str(got));
        default:
            fprintf(stderr, "%s\tFile: %s:%d%s\n\t\t", COLOR_RED, file, line, COLOR_NORMAL);
            fprintf(stderr, "Unknown operator for (" str(bool) ").\n");
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
            __handle_op(OP_EQUAL(expected, got),
                        "expected: " INSPECT("p", void *) ", got: " INSPECT("p", void *), expected, got);
        case OPERATOR_NOT_EQUAL:
            __handle_op(OP_NOT_EQUAL(expected, got),
                        "expected not equal: " INSPECT("p", void *) ", got: " INSPECT("p", void *), expected, got);
        default:
            fprintf(stderr, "%s\tFile: %s:%d%s\n\t\t", COLOR_RED, file, line, COLOR_NORMAL);
            fprintf(stderr, "Unknown operator for (" str(void *) ").\n");
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
 * string
 */
void __traits_str(__operator_t op, const char *expected, const char *got, const char *file, int line) {
    switch (op) {
        case OPERATOR_EQUAL:
            __handle_op(OP_EQUAL(0, strcmp(expected, got)),
                        "expected: \"" INSPECT("s\"", char *) ", got: \"" INSPECT("s\"", char *), expected, got);
        case OPERATOR_NOT_EQUAL:
            __handle_op(OP_NOT_EQUAL(0, strcmp(expected, got)),
                        "expected not equal: \"" INSPECT("s\"", char *) ", got: \"" INSPECT("s\"", char *), expected, got);
        default:
            fprintf(stderr, "%s\tFile: %s:%d%s\n\t\t", COLOR_RED, file, line, COLOR_NORMAL);
            fprintf(stderr, "Unknown operator for (" str(char *) ").\n");
            abort();
    }
}

void _ASSERT_STR_EQUAL(const char *expected, const char *got, const char *file, int line) {
    __traits_str(OPERATOR_EQUAL, expected, got, file, line);
}

void _ASSERT_STR_NOT_EQUAL(const char *expected, const char *got, const char *file, int line) {
    __traits_str(OPERATOR_NOT_EQUAL, expected, got, file, line);
}

/*
 * integer
 */
#define INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, _Operator)                                                      \
    void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line) {   \
        __traits_##_Type(OPERATOR_##_Operator, 0, expected, got, file, line);                                       \
    }

#define INTEGER_OP_DELTA_DEFINE(_Type, _Identifier, _Operator)                                                                          \
    void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line) {    \
        __traits_##_Type(OPERATOR_##_Operator, delta, expected, got, file, line);                                                       \
    }

#define INTEGER_DEFINE(_Type, _Identifier, _Format)                                                                                                 \
    void __traits_##_Type(__operator_t op, const _Type delta, const _Type expected, const _Type got, const char *file, int line) {                  \
        switch (op) {                                                                                                                               \
            case OPERATOR_EQUAL:                                                                                                                    \
                __handle_op(OP_EQUAL(expected, got),                                                                                                \
                            "expected: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                                 \
            case OPERATOR_NOT_EQUAL:                                                                                                                \
                __handle_op(OP_NOT_EQUAL(expected, got),                                                                                            \
                            "expected not equal: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                       \
            case OPERATOR_GREATER_EQUAL:                                                                                                            \
                __handle_op(OP_GREATER_EQUAL(expected, got),                                                                                        \
                            "expected greater equal than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);              \
            case OPERATOR_GREATER:                                                                                                                  \
                __handle_op(OP_GREATER(expected, got),                                                                                              \
                            "expected greater than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                    \
            case OPERATOR_LESS_EQUAL:                                                                                                               \
                __handle_op(OP_LESS_EQUAL(expected, got),                                                                                           \
                            "expected less equal than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                 \
            case OPERATOR_LESS:                                                                                                                     \
                __handle_op(OP_LESS(expected, got),                                                                                                 \
                            "expected less than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                       \
            case OPERATOR_WITHIN:                                                                                                                   \
                __handle_op(OP_WITHIN(delta, expected, got),                                                                                        \
                            "expected to be in range [" INSPECT(_Format, _Type) ", " INSPECT(_Format, _Type) "], got: " INSPECT(_Format, _Type),    \
                            expected - delta, expected + delta, got);                                                                               \
            default:                                                                                                                                \
                fprintf(stderr, "%s\tFile: %s:%d%s\n\t\t", COLOR_RED, file, line, COLOR_NORMAL);                                                    \
                fprintf(stderr, "Unknown operator for (" str(_Type) ").\n");                                                                        \
                abort();                                                                                                                            \
        }                                                                                                                                           \
    }                                                                                                                                               \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, EQUAL)                                                                                              \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, NOT_EQUAL)                                                                                          \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, GREATER_EQUAL)                                                                                      \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, GREATER)                                                                                            \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, LESS_EQUAL)                                                                                         \
    INTEGER_OP_BASIC_DEFINE(_Type, _Identifier, LESS)                                                                                               \
    INTEGER_OP_DELTA_DEFINE(_Type, _Identifier, WITHIN)

INTEGER_DEFINE(uint8_t, UINT8, PRIu8)
INTEGER_DEFINE(uint16_t, UINT16, PRIu16)
INTEGER_DEFINE(uint32_t, UINT32, PRIu32)
INTEGER_DEFINE(size_t, SIZE, "zu")
INTEGER_DEFINE(unsigned, UINT, "u")

INTEGER_DEFINE(int8_t, INT8, PRId8)
INTEGER_DEFINE(int16_t, INT16, PRId16)
INTEGER_DEFINE(int32_t, INT32, PRId32)
INTEGER_DEFINE(int, INT, "d")

#if SUPPORT_64BIT
INTEGER_DEFINE(uint64_t, UINT64, PRIu64)
INTEGER_DEFINE(int64_t, INT64, PRId64)
#endif

#undef INTEGER_OP_BASIC_DEFINE
#undef INTEGER_OP_DELTA_DEFINE
#undef INTEGER_DEFINE

/*
 * floating
 */
#define PRECISION(_String)   ((0 == strcmp("float", _String)) ? FLOAT_PRECISION : DOUBLE_PRECISION)

#define FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, _Operator)                                                     \
    void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line) {   \
        __traits_##_Type(OPERATOR_##_Operator, 0, expected, got, file, line);                                       \
    }

#define FLOATING_OP_DELTA_DEFINE(_Type, _Identifier, _Operator)                                                                         \
    void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line) {    \
        __traits_##_Type(OPERATOR_##_Operator, delta, expected, got, file, line);                                                       \
    }

#define FLOATING_DEFINE(_Type, _Identifier, _Format)                                                                                                \
    void __traits_##_Type(__operator_t op, const _Type delta, const _Type expected, const _Type got, const char *file, int line) {                  \
        switch (op) {                                                                                                                               \
            case OPERATOR_EQUAL:                                                                                                                    \
                __handle_op(OP_WITHIN(PRECISION(str(_Type)), expected, got),                                                                        \
                            "expected: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                                 \
            case OPERATOR_NOT_EQUAL:                                                                                                                \
                __handle_op(!OP_WITHIN(PRECISION(str(_Type)), expected, got),                                                                       \
                            "expected not equal: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                       \
            case OPERATOR_GREATER_EQUAL:                                                                                                            \
                __handle_op(OP_GREATER_EQUAL(expected, got),                                                                                        \
                            "expected greater equal than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);              \
            case OPERATOR_GREATER:                                                                                                                  \
                __handle_op(OP_GREATER(expected, got),                                                                                              \
                            "expected greater than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                    \
            case OPERATOR_LESS_EQUAL:                                                                                                               \
                __handle_op(OP_LESS_EQUAL(expected, got),                                                                                           \
                            "expected less equal than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                 \
            case OPERATOR_LESS:                                                                                                                     \
                __handle_op(OP_LESS(expected, got),                                                                                                 \
                            "expected less than: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), expected, got);                       \
            case OPERATOR_WITHIN:                                                                                                                   \
                __handle_op(OP_WITHIN(delta, expected, got),                                                                                        \
                            "expected to be in range [" INSPECT(_Format, _Type) ", " INSPECT(_Format, _Type) "], got: " INSPECT(_Format, _Type),    \
                            expected - delta, expected + delta, got);                                                                               \
            default:                                                                                                                                \
                fprintf(stderr, "%s\tFile: %s:%d%s\n\t\t", COLOR_RED, file, line, COLOR_NORMAL);                                                    \
                fprintf(stderr, "Unknown operator for (" str(_Type) ").\n");                                                                        \
                abort();                                                                                                                            \
        }                                                                                                                                           \
    }                                                                                                                                               \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, EQUAL)                                                                                             \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, NOT_EQUAL)                                                                                         \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, GREATER_EQUAL)                                                                                     \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, GREATER)                                                                                           \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, LESS_EQUAL)                                                                                        \
    FLOATING_OP_BASIC_DEFINE(_Type, _Identifier, LESS)                                                                                              \
    FLOATING_OP_DELTA_DEFINE(_Type, _Identifier, WITHIN)

FLOATING_DEFINE(float, FLOAT, "f")
FLOATING_DEFINE(double, DOUBLE, "f")

#undef FLOATING_OP_BASIC_DEFINE
#undef FLOATING_OP_DELTA_DEFINE
#undef FLOATING_DEFINE
