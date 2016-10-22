/*
 *  C Source File
 *
 *  Author: Davide Di Carlo
 *  Date:   October 10, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include "traits/traits.h"

/*
 * Logging
 */
static FILE *__gStream = NULL;

void stream(FILE *s) {
    __gStream = s;
}

#define STREAM      ((NULL != __gStream) ? __gStream : stdout)

#define INSPECT(_Format, _Type)     "%" _Format " (" str(_Type) ")"

#define DUMP(_Logger, _File, _Line, _Message, ...)   do {                                   \
        log_error(_Logger, "%s:%d\n  " _Message "\n", _File, _Line, __VA_ARGS__); \
    } while(0)


/*
 *
 */
static int __gRun = 0;
static int __gFailed = 0;
static int __gSkipped = 0;
static int __gState = EXIT_SUCCESS;

static void __launch(const char *name, test_t test) {
    __gRun += 1;
    __gState = EXIT_SUCCESS;
    logger_t *stream_logger = stream_logger_new("Test", LOG_LEVEL_DEBUG, STREAM);
    if (NULL != test) {
        log_notice(stream_logger, "Running '%s'\n", name);
        test();
        if (__gState <= 0) {
            log_info(stream_logger, "Success '%s'\n", name);
        } else {
            log_fatal(stream_logger, "Failed '%s'\n", name);
            __gFailed += 1;
        }
    } else {
        log_warning(stream_logger, "Skipping '%s'\n", name);
        __gSkipped += 1;
    }
    logger_delete(&stream_logger);
}

void _run(const char *name, test_t test) {
    __launch(name, test);
}

void _skip(const char *name, test_t _) {
    __launch(name, NULL);
}

int report(void) {
    logger_t *stream_logger = stream_logger_new("Report", LOG_LEVEL_DEBUG, STREAM);
    if (__gFailed > 0) {
        log_fatal(stream_logger, "%s: %d, %s: %d, %s: %d, %s: %d\n", "Tests", __gRun, "Succeeded",
                 __gRun - (__gFailed + __gSkipped), "Failed", __gFailed, "Skipped", __gSkipped);
    } else if (__gSkipped > 0 ) {
        log_warning(stream_logger, "%s: %d, %s: %d, %s: %d, %s: %d\n", "Tests", __gRun, "Succeeded",
                   __gRun - (__gFailed + __gSkipped), "Failed", __gFailed, "Skipped", __gSkipped);
    } else {
        log_info(stream_logger, "%s: %d, %s: %d, %s: %d, %s: %d\n", "Tests", __gRun, "Succeeded",
                __gRun - (__gFailed + __gSkipped), "Failed", __gFailed, "Skipped", __gSkipped);
    }
    logger_delete(&stream_logger);
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

static const char * __operator2string(__operator_t operator) {
    switch(operator) {
        case OPERATOR_EQUAL:
            return "equal to";
        case OPERATOR_NOT_EQUAL:
            return "not equal to";
        case OPERATOR_GREATER_EQUAL:
            return "greater equal than";
        case OPERATOR_GREATER:
            return "greater than";
        case OPERATOR_LESS_EQUAL:
            return "less equal than";
        case OPERATOR_LESS:
            return "less than";
        case OPERATOR_WITHIN:
            return "to be in range";
        default:
            abort();
    }
}

#define EXPR_EQUAL(_e, _g)                ((_g) == (_e))
#define EXPR_NOT_EQUAL(_e, _g)            ((_g) != (_e))
#define EXPR_GREATER_EQUAL(_e, _g)        ((_g) >= (_e))
#define EXPR_GREATER(_e, _g)              ((_g) >  (_e))
#define EXPR_LESS_EQUAL(_e, _g)           ((_g) <= (_e))
#define EXPR_LESS(_e, _g)                 ((_g) <  (_e))
#define EXPR_WITHIN(_d, _e, _g)           (((_g) >= ((_e) - (_d))) && ((_g) <= ((_e) + (_d))))

#define __HANDLE_BASIC_OPERATOR(_Logger, _Operator, _Expr, _Format, _Type, _Expected, _Got)                                                                  \
case _Operator:                                                                                                                                              \
    if ( ! _Expr ) {                                                                                                                                         \
        __gState += 1;                                                                                                                                       \
        DUMP(_Logger, file, line, "expected %s: " INSPECT(_Format, _Type) ", got: " INSPECT(_Format, _Type), __operator2string(_Operator), _Expected, _Got); \
    }                                                                                                                                                        \
    break

#define __HANDLE_DELTA_OPERATOR(_Logger, _Operator, _Expr, _Format, _Type, _Expected, _Got, _Delta)                                                          \
case _Operator:                                                                                                                                              \
    if ( ! _Expr ) {                                                                                                                                         \
        __gState += 1;                                                                                                                                       \
            DUMP(_Logger, file, line, "expected %s: [" INSPECT(_Format, _Type) ", " INSPECT(_Format, _Type) "], got: " INSPECT(_Format, _Type),              \
                __operator2string(_Operator), _Expected - _Delta, _Expected + _Delta, _Got);                                                                 \
    }                                                                                                                                                        \
    break

#define __HANDLE_WRONG_OPERATOR(_Type) \
default:                               \
    abort()

/*
 * boolean
 */
static void __traits_bool(__operator_t op, const bool expected, const bool got, const char *file, int line) {
    logger_t *stream_logger = stream_logger_new("Assertion", LOG_LEVEL_DEBUG, STREAM);
    switch (op) {
        __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_EQUAL, EXPR_EQUAL(expected, got), "s", bool, bool2str(expected), bool2str(got));
        __HANDLE_WRONG_OPERATOR(bool);
    }
    logger_delete(&stream_logger);
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
static void __traits_ptr(__operator_t op, const void * expected, const void * got, const char *file, int line) {
    logger_t *stream_logger = stream_logger_new("Assertion", LOG_LEVEL_DEBUG, STREAM);
    switch (op) {
        __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_EQUAL, EXPR_EQUAL(expected, got), "p", void *, expected, got);
        __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_NOT_EQUAL, EXPR_NOT_EQUAL(expected, got), "p", void *, expected, got);
        __HANDLE_WRONG_OPERATOR(void *);
    }
    logger_delete(&stream_logger);
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
static void __traits_str(__operator_t op, const char *expected, const char *got, const char *file, int line) {
    logger_t *stream_logger = stream_logger_new("Assertion", LOG_LEVEL_DEBUG, STREAM);
    switch (op) {
        __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_EQUAL, EXPR_EQUAL(0, strcmp(expected, got)), "s", char *, expected, got);
        __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_NOT_EQUAL, EXPR_NOT_EQUAL(0, strcmp(expected, got)), "s", char *, expected, got);
        __HANDLE_WRONG_OPERATOR(char *);
    }
    logger_delete(&stream_logger);
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
#define INTEGER_BASIC_DEFINE(_Type, _Identifier, _Operator)                                                                                   \
    void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line) {                             \
        __traits_##_Type(OPERATOR_##_Operator, 0, expected, got, file, line);                                                                 \
    }

#define INTEGER_DELTA_DEFINE(_Type, _Identifier, _Operator)                                                                                   \
    void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line) {          \
        __traits_##_Type(OPERATOR_##_Operator, delta, expected, got, file, line);                                                             \
    }

#define INTEGER_DEFINE(_Type, _Identifier, _Format)                                                                                           \
    static void __traits_##_Type(__operator_t op, const _Type delta, const _Type expected, const _Type got, const char *file, int line) {     \
        logger_t *stream_logger = stream_logger_new("Assertion", LOG_LEVEL_DEBUG, STREAM);                                                    \
        switch (op) {                                                                                                                         \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_EQUAL, EXPR_EQUAL(expected, got), _Format, _Type, expected, got);                 \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_NOT_EQUAL, EXPR_NOT_EQUAL(expected, got), _Format, _Type, expected, got);         \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_GREATER_EQUAL, EXPR_GREATER_EQUAL(expected, got), _Format, _Type, expected, got); \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_GREATER, EXPR_GREATER(expected, got), _Format, _Type, expected, got);             \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_LESS_EQUAL, EXPR_LESS_EQUAL(expected, got), _Format, _Type, expected, got);       \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_LESS, EXPR_LESS(expected, got), _Format, _Type, expected, got);                   \
            __HANDLE_DELTA_OPERATOR(stream_logger, OPERATOR_WITHIN, EXPR_WITHIN(delta, expected, got), _Format, _Type, expected, got, delta); \
            __HANDLE_WRONG_OPERATOR(_Type);                                                                                                   \
        }                                                                                                                                     \
        logger_delete(&stream_logger);                                                                                                        \
    }                                                                                                                                         \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, EQUAL)                                                                                           \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, NOT_EQUAL)                                                                                       \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, GREATER_EQUAL)                                                                                   \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, GREATER)                                                                                         \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, LESS_EQUAL)                                                                                      \
    INTEGER_BASIC_DEFINE(_Type, _Identifier, LESS)                                                                                            \
    INTEGER_DELTA_DEFINE(_Type, _Identifier, WITHIN)

INTEGER_DEFINE(unsigned, UINT, "u")
INTEGER_DEFINE(uint8_t, UINT8, PRIu8)
INTEGER_DEFINE(uint16_t, UINT16, PRIu16)
INTEGER_DEFINE(uint32_t, UINT32, PRIu32)
INTEGER_DEFINE(size_t, SIZE, "zu")

INTEGER_DEFINE(int, INT, "d")
INTEGER_DEFINE(int8_t, INT8, PRId8)
INTEGER_DEFINE(int16_t, INT16, PRId16)
INTEGER_DEFINE(int32_t, INT32, PRId32)

#if SUPPORT_64BIT
INTEGER_DEFINE(uint64_t, UINT64, PRIu64)
INTEGER_DEFINE(int64_t, INT64, PRId64)
#endif

#undef INTEGER_BASIC_DEFINE
#undef INTEGER_DELTA_DEFINE
#undef INTEGER_DEFINE

/*
 * floating
 */
#define PRECISION(_StrType)   ((0 == strcmp("float", _StrType)) ? FLOAT_PRECISION : DOUBLE_PRECISION)

#define FLOATING_BASIC_DEFINE(_Type, _Identifier, _Operator)                                                                                               \
    void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line) {                                          \
        __traits_##_Type(OPERATOR_##_Operator, 0, expected, got, file, line);                                                                              \
    }

#define FLOATING_DELTA_DEFINE(_Type, _Identifier, _Operator)                                                                                               \
    void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line) {                       \
        __traits_##_Type(OPERATOR_##_Operator, delta, expected, got, file, line);                                                                          \
    }

#define FLOATING_DEFINE(_Type, _Identifier, _Format)                                                                                                       \
    static void __traits_##_Type(__operator_t op, const _Type delta, const _Type expected, const _Type got, const char *file, int line) {                  \
        logger_t *stream_logger = stream_logger_new("Assertion", LOG_LEVEL_DEBUG, STREAM);                                                                 \
        switch (op) {                                                                                                                                      \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_EQUAL, EXPR_WITHIN(PRECISION(str(_Type)), expected, got), _Format, _Type, expected, got);      \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_NOT_EQUAL, !EXPR_WITHIN(PRECISION(str(_Type)), expected, got), _Format, _Type, expected, got); \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_GREATER_EQUAL, EXPR_GREATER_EQUAL(expected, got), _Format, _Type, expected, got);              \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_GREATER, EXPR_GREATER(expected, got), _Format, _Type, expected, got);                          \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_LESS_EQUAL, EXPR_LESS_EQUAL(expected, got), _Format, _Type, expected, got);                    \
            __HANDLE_BASIC_OPERATOR(stream_logger, OPERATOR_LESS, EXPR_LESS(expected, got), _Format, _Type, expected, got);                                \
            __HANDLE_DELTA_OPERATOR(stream_logger, OPERATOR_WITHIN, EXPR_WITHIN(delta, expected, got), _Format, _Type, expected, got, delta);              \
            __HANDLE_WRONG_OPERATOR(_Type);                                                                                                                \
        }                                                                                                                                                  \
        logger_delete(&stream_logger);                                                                                                                     \
    }                                                                                                                                                      \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, EQUAL)                                                                                                       \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, NOT_EQUAL)                                                                                                   \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, GREATER_EQUAL)                                                                                               \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, GREATER)                                                                                                     \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, LESS_EQUAL)                                                                                                  \
    FLOATING_BASIC_DEFINE(_Type, _Identifier, LESS)                                                                                                        \
    FLOATING_DELTA_DEFINE(_Type, _Identifier, WITHIN)

FLOATING_DEFINE(float, FLOAT, "f")
FLOATING_DEFINE(double, DOUBLE, "f")

#undef FLOATING_BASIC_DEFINE
#undef FLOATING_DELTA_DEFINE
#undef FLOATING_DEFINE
