/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 02, 2017
 */

#include "traits.h"

/*
 *
 */
int main() {
    /* Basic */
    traits_assert(true);
    traits_assert(true, "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(eq_as(size_t, 1U, 1.35f));
    traits_assert(eq_as(size_t, 1U, 1.35f), "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(ne_as(
                          double, 1L, 1.35f));
    traits_assert(ne_as(
                          double, 1L, 1.35f), "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(gt_as(
                          char, 99, 'a'));
    traits_assert(gt_as(
                          char, 99, 'a'), "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(ge_as(
                          unsigned int, 1, 0));
    traits_assert(ge_as(
                          unsigned int, 1, 0), "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(lt_as(
                          long int, -1, 1U));
    traits_assert(lt_as(
                          long int, -1, 1U), "My amazing %s assertion message%c", "formatted", '!');

    traits_assert(le_as(
                          long double, -1.5f, 0x10));
    traits_assert(le_as(
                          long double, -1.5f, 0x10), "My amazing %s assertion message%c", "formatted", '!');

    /* Boolean */
    assert_true(true);
    assert_true(true, "My amazing %s assertion message%c", "formatted", '!');

    assert_false(false);
    assert_false(false, "My amazing %s assertion message%c", "formatted", '!');

    /* Numerical */
    assert_equal(5, 5);
    assert_equal(5, 5, "My amazing %s assertion message%c", "formatted", '!');

    assert_not_equal(5, 6);
    assert_not_equal(5, 6, "My amazing %s assertion message%c", "formatted", '!');

    assert_greater(6, 5);
    assert_greater(6, 5, "My amazing %s assertion message%c", "formatted", '!');

    assert_greater_equal(5, 5);
    assert_greater_equal(6, 5);
    assert_greater_equal(5, 5, "My amazing %s assertion message%c", "formatted", '!');

    assert_less(5, 6);
    assert_less(5, 6, "My amazing %s assertion message%c", "formatted", '!');

    assert_less_equal(5, 5);
    assert_less_equal(5, 6);
    assert_less_equal(5, 5, "My amazing %s assertion message%c", "formatted", '!');

    /* Pointer */
    assert_null(NULL);
    assert_null(NULL, "My amazing %s assertion message%c", "formatted", '!');
    {
        int tmp = 0;
        assert_not_null(&tmp);
        assert_not_null(&tmp, "My amazing %s assertion message%c", "formatted", '!');
    }

    /* String */
    {
        const char *const e = "Hello", *const a = "Hello";
        assert_string_equal(e, a);
        assert_string_equal(e, a, "My amazing %s assertion message%c", "formatted", '!');
    }
    {
        const char *const e = "Hello!", *const a = "hell0!";
        assert_string_not_equal(e, a);
        assert_string_not_equal(e, a, "My amazing %s assertion message%c", "formatted", '!');
    }

    return 0;
}
