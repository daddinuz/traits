/*
 *  C Header File
 *
 *  Author: Davide Di Carlo
 *  Date:   October 10, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#ifndef __TRAITS_H__
#define __TRAITS_H__

/*
 * Preprocessor helper
 */
#define str(x)      #x
#define bool2str(x) ((x == 0) ? "false" : "true")

/*
 * Logging
 */
extern void stream(FILE *s); 

/*
 * Test
 */
typedef void (*test_case_t)(void);

#define TEST(_case)     void test_##_case()

typedef enum call_t {
    CALL_RUN,
    CALL_SKIP,
} call_t; 

extern void launch(const char* name, test_case_t ptr, call_t call);

#define run(_case)      launch(str(_case), test_##_case, CALL_RUN);
#define skip(_case)     launch(str(_case), test_##_case, CALL_SKIP);

/*
 * operators
 */
typedef enum operator_t {
    OPERATOR_EQUAL = 0,
    OPERATOR_NOT_EQUAL,
    OPERATOR_GREATER_EQUAL,
    OPERATOR_GREATER,
    OPERATOR_LESS_EQUAL,
    OPERATOR_LESS,
} operator_t;

/*
 * boolean
 */
extern void __traits_bool(operator_t op, const bool expected, const bool got, const char *file, int line); 

#define ASSERT(condition)       __traits_bool(OPERATOR_EQUAL, true, (condition), __FILE__, __LINE__)
#define ASSERT_TRUE(condition)  __traits_bool(OPERATOR_EQUAL, true, (condition), __FILE__, __LINE__)
#define ASSERT_FALSE(condition) __traits_bool(OPERATOR_EQUAL, false, (condition), __FILE__, __LINE__)

/*
 * integer
 */
extern void __traits_int(operator_t op, const int expected, const int got, const char *file, int line); 

#define ASSERT_INT_EQUAL(expected, got)         __traits_int(OPERATOR_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_NOT_EQUAL(expected, got)     __traits_int(OPERATOR_NOT_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_GREATER_EQUAL(expected, got) __traits_int(OPERATOR_GREATER_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_GREATER(expected, got)       __traits_int(OPERATOR_GREATER, (expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_LESS_EQUAL(expected, got)    __traits_int(OPERATOR_LESS_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_LESS(expected, got)          __traits_int(OPERATOR_LESS, (expected), (got), __FILE__, __LINE__)

extern void __traits_size_t(operator_t op, const size_t expected, const size_t got, const char *file, int line);

#define ASSERT_SIZE_T_EQUAL(expected, got)         __traits_size_t(OPERATOR_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_T_NOT_EQUAL(expected, got)     __traits_size_t(OPERATOR_NOT_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_T_GREATER_EQUAL(expected, got) __traits_size_t(OPERATOR_GREATER_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_T_GREATER(expected, got)       __traits_size_t(OPERATOR_GREATER, (expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_T_LESS_EQUAL(expected, got)    __traits_size_t(OPERATOR_LESS_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_T_LESS(expected, got)          __traits_size_t(OPERATOR_LESS, (expected), (got), __FILE__, __LINE__)

/*
 * pointer
 */
extern void __traits_pointer(operator_t op, const void *const expected, const void *const got, const char *file, int line);

#define ASSERT_POINTER_EQUAL(expected, got)     __traits_pointer(OPERATOR_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_POINTER_NOT_EQUAL(expected, got) __traits_pointer(OPERATOR_NOT_EQUAL, (expected), (got), __FILE__, __LINE__)
#define ASSERT_POINTER_NULL(pointer)            __traits_pointer(OPERATOR_EQUAL, NULL, (pointer), __FILE__, __LINE__)
#define ASSERT_POINTER_NOT_NULL(pointer)        __traits_pointer(OPERATOR_NOT_EQUAL, NULL, (pointer), __FILE__, __LINE__)

#endif /** __TRAITS_H__ **/
