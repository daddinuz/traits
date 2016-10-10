#include "traits.h"


TEST(bool) {
    ASSERT(0 != 1);
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

TEST(ptr) {
    ASSERT_PTR_EQUAL(NULL, NULL);
    ASSERT_PTR_NOT_EQUAL(NULL, (void *) 1);
    ASSERT_PTR_NULL(NULL);
    ASSERT_PTR_NOT_NULL((void *) 1);
}

#define INTEGER(_lower, _upper)                 \
    TEST(_lower) {                              \
        ASSERT_##_upper##_EQUAL(0, 0);          \
        ASSERT_##_upper##_NOT_EQUAL(1, 0);      \
        ASSERT_##_upper##_GREATER_EQUAL(1, 1);  \
        ASSERT_##_upper##_GREATER(0, 1);        \
        ASSERT_##_upper##_LESS_EQUAL(0, 0);     \
        ASSERT_##_upper##_LESS(1, 0);           \
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

    run(bool);
    run(ptr);
    run(uint8_t);
    run(uint16_t);
    run(uint32_t);
    run(size_t);
    run(unsigned);
    run(int8_t);
    run(int16_t);
    run(int32_t);
    run(int);

#ifdef SUPPORT_64BIT
    run(uint64_t);
    run(int64_t);
    skip(uint64_t);
    skip(int64_t);
#endif

    skip(bool);
    skip(ptr);
    skip(uint8_t);
    skip(uint16_t);
    skip(uint32_t);
    skip(size_t);
    skip(unsigned);
    skip(int8_t);
    skip(int16_t);
    skip(int32_t);
    skip(int);

    return report();
}
