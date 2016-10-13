/*
 *  C Header File
 *
 *  Author: Davide Di Carlo
 *  Date:   October 10, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>


#ifndef __TRAITS_H__
#define __TRAITS_H__

/*
 * Check system support
 */
#define SUPPORT_64BIT       UINTPTR_MAX == 0xffffffffffffffff

/*
 * Floating sensibility
 */
#ifndef FLOAT_PRECISION
#define FLOAT_PRECISION     0.00001f
#endif

#ifndef DOUBLE_PRECISION
#define DOUBLE_PRECISION    0.0000001f
#endif

/*
 * Useful macros
 */
#define str(x)          #x
#define bool2str(x)     ((x == 0) ? "false" : "true")

/*
 * Logging
 */
extern void stream(FILE *s);
extern void notify(const char *format, ...);

/*
 * Test
 */
typedef void (*test_t)(void);

#define TEST(_case)     void test_##_case()

extern void _run(const char *name, test_t test);
#define run(_case)      _run(str(_case), test_##_case)

extern void _skip(const char *name, test_t _);
#define skip(_case)     _skip(str(_case), test_##_case)

extern int report(void);

/*
 * boolean
 */
extern void _ASSERT(const bool condition, const char *file, int line);
#define ASSERT(condition)   _ASSERT((condition), __FILE__, __LINE__)

extern void _ASSERT_TRUE(const bool got, const char *file, int line);
#define ASSERT_TRUE(got)    _ASSERT_TRUE((got), __FILE__, __LINE__)

extern void _ASSERT_FALSE(const bool got, const char *file, int line);
#define ASSERT_FALSE(got)   _ASSERT_FALSE((got), __FILE__, __LINE__)

/*
 * pointer
 */
extern void _ASSERT_PTR_EQUAL(const void * expected, const void * got, const char *file, int line);
#define ASSERT_PTR_EQUAL(expected, got)     _ASSERT_PTR_EQUAL((expected), (got), __FILE__, __LINE__)

extern void _ASSERT_PTR_NOT_EQUAL(const void * expected, const void * got, const char *file, int line);
#define ASSERT_PTR_NOT_EQUAL(expected, got) _ASSERT_PTR_NOT_EQUAL((expected), (got), __FILE__, __LINE__)

extern void _ASSERT_PTR_NULL(const void * got, const char *file, int line);
#define ASSERT_PTR_NULL(pointer)            _ASSERT_PTR_NULL((pointer), __FILE__, __LINE__)

extern void _ASSERT_PTR_NOT_NULL(const void * got, const char *file, int line);
#define ASSERT_PTR_NOT_NULL(pointer)        _ASSERT_PTR_NOT_NULL((pointer), __FILE__, __LINE__)

/*
 * integer
 */
#define OP_DECLARE(_Type, _Identifier, _Operator)   \
    extern void _ASSERT_##_Identifier##_##_Operator(const _Type expected, const _Type got, const char *file, int line);

#define OP_COMPOUND_DECLARE(_Type, _Identifier, _Operator)   \
    extern void _ASSERT_##_Identifier##_##_Operator(const _Type delta, const _Type expected, const _Type got, const char *file, int line);

#define DECLARE(_Type, _Identifier)                 \
    OP_DECLARE(_Type, _Identifier, EQUAL)           \
    OP_DECLARE(_Type, _Identifier, NOT_EQUAL)       \
    OP_DECLARE(_Type, _Identifier, GREATER_EQUAL)   \
    OP_DECLARE(_Type, _Identifier, GREATER)         \
    OP_DECLARE(_Type, _Identifier, LESS_EQUAL)      \
    OP_DECLARE(_Type, _Identifier, LESS)            \
    OP_COMPOUND_DECLARE(_Type, _Identifier, WITHIN) \

/*
 * Integer ops
 */
DECLARE(uint8_t, UINT8)
#define ASSERT_UINT8_EQUAL(expected, got)           _ASSERT_UINT8_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_NOT_EQUAL(expected, got)       _ASSERT_UINT8_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_GREATER_EQUAL(expected, got)   _ASSERT_UINT8_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_GREATER(expected, got)         _ASSERT_UINT8_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_LESS_EQUAL(expected, got)      _ASSERT_UINT8_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_LESS(expected, got)            _ASSERT_UINT8_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT8_WITHIN(delta, expected, got)   _ASSERT_UINT8_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(uint16_t, UINT16)
#define ASSERT_UINT16_EQUAL(expected, got)          _ASSERT_UINT16_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_NOT_EQUAL(expected, got)      _ASSERT_UINT16_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_GREATER_EQUAL(expected, got)  _ASSERT_UINT16_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_GREATER(expected, got)        _ASSERT_UINT16_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_LESS_EQUAL(expected, got)     _ASSERT_UINT16_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_LESS(expected, got)           _ASSERT_UINT16_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT16_WITHIN(delta, expected, got)  _ASSERT_UINT16_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(uint32_t, UINT32)
#define ASSERT_UINT32_EQUAL(expected, got)          _ASSERT_UINT32_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_NOT_EQUAL(expected, got)      _ASSERT_UINT32_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_GREATER_EQUAL(expected, got)  _ASSERT_UINT32_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_GREATER(expected, got)        _ASSERT_UINT32_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_LESS_EQUAL(expected, got)     _ASSERT_UINT32_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_LESS(expected, got)           _ASSERT_UINT32_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT32_WITHIN(delta, expected, got)  _ASSERT_UINT32_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(size_t, SIZE)
#define ASSERT_SIZE_EQUAL(expected, got)            _ASSERT_SIZE_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_NOT_EQUAL(expected, got)        _ASSERT_SIZE_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_GREATER_EQUAL(expected, got)    _ASSERT_SIZE_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_GREATER(expected, got)          _ASSERT_SIZE_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_LESS_EQUAL(expected, got)       _ASSERT_SIZE_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_LESS(expected, got)             _ASSERT_SIZE_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_SIZE_WITHIN(delta, expected, got)    _ASSERT_SIZE_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(unsigned, UINT)
#define ASSERT_UINT_EQUAL(expected, got)            _ASSERT_UINT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_NOT_EQUAL(expected, got)        _ASSERT_UINT_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_GREATER_EQUAL(expected, got)    _ASSERT_UINT_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_GREATER(expected, got)          _ASSERT_UINT_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_LESS_EQUAL(expected, got)       _ASSERT_UINT_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_LESS(expected, got)             _ASSERT_UINT_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT_WITHIN(delta, expected, got)    _ASSERT_UINT_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(int8_t, INT8)
#define ASSERT_INT8_EQUAL(expected, got)            _ASSERT_INT8_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_NOT_EQUAL(expected, got)        _ASSERT_INT8_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_GREATER_EQUAL(expected, got)    _ASSERT_INT8_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_GREATER(expected, got)          _ASSERT_INT8_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_LESS_EQUAL(expected, got)       _ASSERT_INT8_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_LESS(expected, got)             _ASSERT_INT8_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT8_WITHIN(delta, expected, got)    _ASSERT_INT8_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(int16_t, INT16)
#define ASSERT_INT16_EQUAL(expected, got)           _ASSERT_INT16_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_NOT_EQUAL(expected, got)       _ASSERT_INT16_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_GREATER_EQUAL(expected, got)   _ASSERT_INT16_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_GREATER(expected, got)         _ASSERT_INT16_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_LESS_EQUAL(expected, got)      _ASSERT_INT16_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_LESS(expected, got)            _ASSERT_INT16_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT16_WITHIN(delta, expected, got)   _ASSERT_INT16_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(int32_t, INT32)
#define ASSERT_INT32_EQUAL(expected, got)           _ASSERT_INT32_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_NOT_EQUAL(expected, got)       _ASSERT_INT32_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_GREATER_EQUAL(expected, got)   _ASSERT_INT32_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_GREATER(expected, got)         _ASSERT_INT32_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_LESS_EQUAL(expected, got)      _ASSERT_INT32_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_LESS(expected, got)            _ASSERT_INT32_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT32_WITHIN(delta, expected, got)   _ASSERT_INT32_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(int, INT)
#define ASSERT_INT_EQUAL(expected, got)             _ASSERT_INT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_NOT_EQUAL(expected, got)         _ASSERT_INT_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_GREATER_EQUAL(expected, got)     _ASSERT_INT_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_GREATER(expected, got)           _ASSERT_INT_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_LESS_EQUAL(expected, got)        _ASSERT_INT_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_LESS(expected, got)              _ASSERT_INT_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT_WITHIN(delta, expected, got)     _ASSERT_INT_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

#if SUPPORT_64BIT
DECLARE(uint64_t, UINT64)
#define ASSERT_UINT64_EQUAL(expected, got)          _ASSERT_UINT64_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_NOT_EQUAL(expected, got)      _ASSERT_UINT64_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_GREATER_EQUAL(expected, got)  _ASSERT_UINT64_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_GREATER(expected, got)        _ASSERT_UINT64_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_LESS_EQUAL(expected, got)     _ASSERT_UINT64_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_LESS(expected, got)           _ASSERT_UINT64_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_UINT64_WITHIN(delta, expected, got)  _ASSERT_UINT64_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(int64_t, INT64)
#define ASSERT_INT64_EQUAL(expected, got)           _ASSERT_INT64_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_NOT_EQUAL(expected, got)       _ASSERT_INT64_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_GREATER_EQUAL(expected, got)   _ASSERT_INT64_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_GREATER(expected, got)         _ASSERT_INT64_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_LESS_EQUAL(expected, got)      _ASSERT_INT64_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_LESS(expected, got)            _ASSERT_INT64_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_INT64_WITHIN(delta, expected, got)   _ASSERT_INT64_WITHIN((delta), (expected), (got), __FILE__, __LINE__)
#endif

/*
 * Floating ops
 */
DECLARE(float, FLOAT)
#define ASSERT_FLOAT_EQUAL(expected, got)           _ASSERT_FLOAT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_NOT_EQUAL(expected, got)       _ASSERT_FLOAT_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_GREATER_EQUAL(expected, got)   _ASSERT_FLOAT_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_GREATER(expected, got)         _ASSERT_FLOAT_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_LESS_EQUAL(expected, got)      _ASSERT_FLOAT_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_LESS(expected, got)            _ASSERT_FLOAT_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_FLOAT_WITHIN(delta, expected, got)   _ASSERT_FLOAT_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

DECLARE(double, DOUBLE)
#define ASSERT_DOUBLE_EQUAL(expected, got)           _ASSERT_DOUBLE_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_NOT_EQUAL(expected, got)       _ASSERT_DOUBLE_NOT_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_GREATER_EQUAL(expected, got)   _ASSERT_DOUBLE_GREATER_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_GREATER(expected, got)         _ASSERT_DOUBLE_GREATER((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_LESS_EQUAL(expected, got)      _ASSERT_DOUBLE_LESS_EQUAL((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_LESS(expected, got)            _ASSERT_DOUBLE_LESS((expected), (got), __FILE__, __LINE__)
#define ASSERT_DOUBLE_WITHIN(delta, expected, got)   _ASSERT_DOUBLE_WITHIN((delta), (expected), (got), __FILE__, __LINE__)

#undef OP_COMPOUND_DECLARE
#undef OP_DECLARE
#undef DECLARE

#endif /** __TRAITS_H__ **/
