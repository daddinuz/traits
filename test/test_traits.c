#include "traits.h"


Test(Bool) {
    ASSERT(0 != 1);
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

Test(Pointer) {
    ASSERT_PTR_EQUAL(NULL, NULL);
    ASSERT_PTR_NOT_EQUAL(NULL, (void *) 1);
    ASSERT_PTR_NULL(NULL);
    ASSERT_PTR_NOT_NULL((void *) 1);
}

Test(String) {
    ASSERT_STR_EQUAL("Hello", "Hello");
    ASSERT_STR_NOT_EQUAL("Hello", "World");
}

#define NUMERICAL(_TestCase, _Type, _Identifier)                                      \
    Test(_TestCase) {                                                                 \
        ASSERT_##_Identifier##_EQUAL            ((_Type) 0, (_Type) 0);               \
        ASSERT_##_Identifier##_NOT_EQUAL        ((_Type) 1, (_Type) 0);               \
        ASSERT_##_Identifier##_GREATER_EQUAL    ((_Type) 1, (_Type) 1);               \
        ASSERT_##_Identifier##_GREATER          ((_Type) 0, (_Type) 1);               \
        ASSERT_##_Identifier##_LESS_EQUAL       ((_Type) 0, (_Type) 0);               \
        ASSERT_##_Identifier##_LESS             ((_Type) 1, (_Type) 0);               \
        ASSERT_##_Identifier##_WITHIN           ((_Type) 5, (_Type) 10, (_Type) 5);   \
        ASSERT_##_Identifier##_WITHIN           ((_Type) 5, (_Type) 10, (_Type) 10);  \
        ASSERT_##_Identifier##_WITHIN           ((_Type) 5, (_Type) 10, (_Type) 15);  \
    }

/*
 * Integer
 */
NUMERICAL(UInt, unsigned, UINT)
NUMERICAL(UInt8, uint8_t, UINT8)
NUMERICAL(UInt16, uint16_t, UINT16)
NUMERICAL(UInt32, uint32_t, UINT32)
NUMERICAL(SizeT, size_t, SIZE)
NUMERICAL(Int, int, INT)
NUMERICAL(Int8, int8_t, INT8)
NUMERICAL(Int16, int16_t, INT16)
NUMERICAL(Int32, int32_t, INT32)

#ifdef SUPPORT_64BIT
NUMERICAL(UInt64, uint64_t, UINT64)
NUMERICAL(Int64, int64_t, INT64)
#endif

/*
 * Floating
 */
NUMERICAL(Float, float, FLOAT)
NUMERICAL(Double, double, DOUBLE)

/*
 *
 */
int main() {
    /* Boolean  */
    run(Bool);

    /* Pointers */
    run(Pointer);

    /* String   */
    run(String);

    /* Integers */
    run(UInt);
    run(UInt8);
    run(UInt16);
    run(UInt32);
    run(SizeT);
    run(Int);
    run(Int8);
    run(Int16);
    run(Int32);

    (SUPPORT_64BIT) ? ({
        run(UInt64);
        run(Int64);
    }) : ({
        skip(UInt64);
        skip(Int64);
    });

    run(Float);
    run(Double);

    return report();
}
