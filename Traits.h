/*
 *  C Header File
 *
 *  Author: Davide Di Carlo
 *  Date:   April 2, 2017
 *  email:  daddinuz@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef __TRAITS_H__
#define __TRAITS_H__

#define TRAITS_VERSION "1.0.0"

#define __traits_stringify(x)   #x
#define traits_stringify(x)     __traits_stringify(x)

#define __traits_log(_File, _Line, _Message, ...)                       \
    fprintf(stderr, "At %s:%d\n" _Message "\n", _File, _Line, __VA_ARGS__)

#define __traits_assert(_Expression, _Message, ...)                     \
    do {                                                                \
        const bool actual = (_Expression);                              \
        if (!actual) {                                                  \
            __traits_log(__FILE__, __LINE__, _Message, __VA_ARGS__);    \
           abort();                                                     \
        }                                                               \
    } while (false)

/*
 * Boolean
 */
#define assert(_Expression)                             __traits_assert((_Expression), "expected %s", traits_stringify(_Expression))
#define assert_true(_Expression)                        __traits_assert(true == (_Expression), "expected %s to be true", traits_stringify(_Expression))
#define assert_false(_Expression)                       __traits_assert(false == (_Expression), "expected %s to be false", traits_stringify(_Expression))

/*
 * Numerical
 */
#define assert_equal(_Expected, _Actual)                __traits_assert((_Expected) == (_Actual), "expected %s to be equal to %s", traits_stringify(_Actual), traits_stringify(_Expected))
#define assert_not_equal(_Expected, _Actual)            __traits_assert((_Expected) != (_Actual), "expected %s to not be equal to %s", traits_stringify(_Actual), traits_stringify(_Expected))
#define assert_less_equal(_Expected, _Actual)           __traits_assert((_Expected) <= (_Actual), "expected %s to be less equal than %s", traits_stringify(_Actual), traits_stringify(_Expected))
#define assert_greater_equal(_Expected, _Actual)        __traits_assert((_Expected) >= (_Actual), "expected %s to be greater equal than %s", traits_stringify(_Actual), traits_stringify(_Expected))
#define assert_less(_Expected, _Actual)                 __traits_assert((_Expected) < (_Actual), "expected %s to be less than %s", traits_stringify(_Actual), traits_stringify(_Expected))
#define assert_greater(_Expected, _Actual)              __traits_assert((_Expected) > (_Actual), "expected %s to be greater than %s", traits_stringify(_Actual), traits_stringify(_Expected))

/*
 * Pointer
 */
#define assert_null(_Pointer)                           __traits_assert(NULL == (_Pointer), "expected %s to be NULL", traits_stringify(_Pointer))
#define assert_not_null(_Pointer)                       __traits_assert(NULL != (_Pointer), "expected %s to not be NULL", traits_stringify(_Pointer))

/*
 * String
 */
#define assert_string_equal(_Expected, _Actual)         __traits_assert(0 == strcmp((_Expected), (_Actual)), "expected \"%s\" to be equal to \"%s\"", _Actual, _Expected)
#define assert_string_not_equal(_Expected, _Actual)     __traits_assert(0 != strcmp((_Expected), (_Actual)), "expected \"%s\" to not be equal to \"%s\"", _Actual, _Expected)

#endif /* __TRAITS_H__ */
