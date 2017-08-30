/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   August 30, 2017 
 */

#include <string.h>
#include <iso646.h>
#include <stdbool.h>

#ifndef __TRAITS_H__
#define __TRAITS_H__

#define TRAITS_VERSION "2.0.0"

#if defined(__GNUC__) || defined(__clang__)
#   define TRAITS_FORMAT_ATTRIBUTE(x, y)  __attribute__((__format__(__printf__, x, y)))
#else
#   define TRAITS_FORMAT_ATTRIBUTE(x, y)
#endif

/*
 * Assertions framework
 */
extern void ___traits_assert(
        size_t line, const char *file, const char *assertion, bool status, bool hasMessage, const char *message, ...
) TRAITS_FORMAT_ATTRIBUTE(6, 0);

#define __traits_assert(a, m, ...)              ___traits_assert(__LINE__, __FILE__, #a, a, m != NULL, __VA_ARGS__)
#define _traits_assert(a, ...)                  __traits_assert(a, #__VA_ARGS__, __VA_ARGS__)
#define traits_assert(...)                      _traits_assert(__VA_ARGS__, NULL)

/*
 * Helpers
 */
#define eq(e, a)                                ((e) == (a))
#define ne(e, a)                                ((e) != (a))
#define gt(e, a)                                ((e)  > (a))
#define ge(e, a)                                ((e) >= (a))
#define lt(e, a)                                ((e)  < (a))
#define le(e, a)                                ((e) <= (a))

#define eq_as(T, e, a)                          ((T)(e) == (T)(a))
#define ne_as(T, e, a)                          ((T)(e) != (T)(a))
#define gt_as(T, e, a)                          ((T)(e)  > (T)(a))
#define ge_as(T, e, a)                          ((T)(e) >= (T)(a))
#define lt_as(T, e, a)                          ((T)(e)  < (T)(a))
#define le_as(T, e, a)                          ((T)(e) <= (T)(a))

/*
 * Boolean
 */
#define assert_true(x)                          traits_assert(eq_as(bool, true, x), "Expected to be true.")
#define assert_false(x)                         traits_assert(eq_as(bool, false, x), "Expected to be false.")

/*
 * Numerical
 */
#define __assert_equal(e, a, m, ...)            traits_assert(eq(e, a), m, __VA_ARGS__)
#define _assert_equal(e, a, ...)                __assert_equal(e, a, __VA_ARGS__, NULL);
#define assert_equal(x, ...)                    _assert_equal(x, __VA_ARGS__, "Expected to be equal.")

#define __assert_not_equal(e, a, m, ...)        traits_assert(ne(e, a), m, __VA_ARGS__)
#define _assert_not_equal(e, a, ...)            __assert_not_equal(e, a, __VA_ARGS__, NULL);
#define assert_not_equal(x, ...)                _assert_not_equal(x, __VA_ARGS__, "Expected to not be equal.")

#define __assert_greater(e, a, m, ...)          traits_assert(gt(e, a), m, __VA_ARGS__)
#define _assert_greater(e, a, ...)              __assert_greater(e, a, __VA_ARGS__, NULL);
#define assert_greater(x, ...)                  _assert_greater(x, __VA_ARGS__, "Expected to be greater.")

#define __assert_greater_equal(e, a, m, ...)    traits_assert(ge(e, a), m, __VA_ARGS__)
#define _assert_greater_equal(e, a, ...)        __assert_greater_equal(e, a, __VA_ARGS__, NULL);
#define assert_greater_equal(x, ...)            _assert_greater_equal(x, __VA_ARGS__, "Expected to be greater or equal.")

#define __assert_less(e, a, m, ...)             traits_assert(lt(e, a), m, __VA_ARGS__)
#define _assert_less(e, a, ...)                 __assert_less(e, a, __VA_ARGS__, NULL);
#define assert_less(x, ...)                     _assert_less(x, __VA_ARGS__, "Expected to be less.")

#define __assert_less_equal(e, a, m, ...)       traits_assert(le(e, a), m, __VA_ARGS__)
#define _assert_less_equal(e, a, ...)           __assert_less_equal(e, a, __VA_ARGS__, NULL);
#define assert_less_equal(x, ...)               _assert_less_equal(x, __VA_ARGS__, "Expected to be less or equal.")

/*
 * Pointer
 */
#define assert_null(a)                          do { const void *const a1 = (a); traits_assert(eq(NULL, a1), "Expected to be NULL."); } while (false)
#define assert_not_null(a)                      do { const void *const a1 = (a); traits_assert(ne(NULL, a1), "Expected to not be NULL."); } while (false)

/*
 * String
 */
#define assert_string_equal(e, a)               do { const char *const e1 = (e), *a1 = (a); traits_assert(eq(0, strcmp(e1, a1)), "Expected `%s` to be equal to `%s`.", a1, e1); } while (false)
#define assert_string_not_equal(e, a)           do { const char *const e1 = (e), *a1 = (a); traits_assert(ne(0, strcmp(e1, a1)), "Expected `%s` to not be equal to `%s`.", a1, e1); } while (false)

/*
 * Test Framework
 */
extern void traits_setup(void);                 /* Must be implemented by the user */
extern void traits_teardown(void);              /* Must be implemented by the user */

#define TRAITS(_Case)                                               \
    void test_##_Case(void)

#define traits_run(_Case)                                           \
    do {                                                            \
        printf("Running: " traits_stringify(_Case) "... ");         \
        traits_setup();                                             \
        test_##_Case();                                             \
        traits_teardown();                                          \
        puts("done");                                               \
    } while (false)

#define traits_skip(_Case)                                          \
    do {                                                            \
        puts("Skipping: " traits_stringify(_Case) "... done");      \
    } while (false)

#endif /* __TRAITS_H__ */
