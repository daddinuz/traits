#include "traits.h"


TEST(BOOL) {
    ASSERT(0 != 1);
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

TEST(PTR) {
    ASSERT_PTR_EQUAL(NULL, NULL);
    ASSERT_PTR_NOT_EQUAL(NULL, (void *) 1);
    ASSERT_PTR_NULL(NULL);
    ASSERT_PTR_NOT_NULL((void *) 1);
}

#define INTEGER(_lower, _upper)                 \
    TEST(_upper) {                              \
        ASSERT_##_upper##_EQUAL(0, 0);          \
        ASSERT_##_upper##_NOT_EQUAL(1, 0);      \
        ASSERT_##_upper##_GREATER_EQUAL(1, 1);  \
        ASSERT_##_upper##_GREATER(0, 1);        \
        ASSERT_##_upper##_LESS_EQUAL(0, 0);     \
        ASSERT_##_upper##_LESS(1, 0);           \
        ASSERT_##_upper##_WITHIN(5, 10, 5);     \
        ASSERT_##_upper##_WITHIN(5, 10, 10);    \
        ASSERT_##_upper##_WITHIN(5, 10, 15);    \
    }

INTEGER(uint8_t , UINT8)
INTEGER(uint16_t, UINT16)
INTEGER(uint32_t, UINT32)
INTEGER(size_t, SIZE)
INTEGER(unsigned, UINT)
INTEGER(int8_t , INT8)
INTEGER(int16_t, INT16)
INTEGER(int32_t, INT32)
INTEGER(int, INT)

#ifdef SUPPORT_64BIT
    INTEGER(uint64_t, UINT64)
    INTEGER(int64_t, INT64)
#endif

/*
 *
 */
int main() {
    stream(stdout);

    run(BOOL);
    run(PTR);
    run(UINT8);
    run(UINT16);
    run(UINT32);
    run(SIZE);
    run(UINT);
    run(INT8);
    run(INT16);
    run(INT32);
    run(INT);

#ifdef SUPPORT_64BIT
    run(UINT64);
    run(INT64);
    skip(UINT64);
    skip(INT64);
#endif

    skip(BOOL);
    skip(PTR);
    skip(UINT8);
    skip(UINT16);
    skip(UINT32);
    skip(SIZE);
    skip(UINT);
    skip(INT8);
    skip(INT16);
    skip(INT32);
    skip(INT);

    return report();
}
