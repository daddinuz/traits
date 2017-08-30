/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   August 27, 2017 
 */

#include "traits.h"

/*
 *
 */
int main() {
    /* Boolean */
    assert_true(true);
    assert_false(false);

    /* Numerical */
    assert_equal(5, 5);
    assert_not_equal(5, 6);
    assert_greater(6, 5);
    assert_greater_equal(5, 5);
    assert_greater_equal(6, 5);
    assert_less(4, 5);
    assert_less_equal(5, 5);
    assert_less_equal(4, 5);

    /* Pointer */
    assert_null(NULL);
    {
        int tmp = 0;
        assert_not_null(&tmp);
    }

    /* String */
    {
        char *tmp = "Hello, World!";
        assert_string_equal(tmp, tmp);
    }
    assert_string_not_equal("Hello World", "Hello, World!");
    return 0;
}
