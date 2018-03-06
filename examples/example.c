/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "traits.h"


#define min(a, b) ((a) < (b) ? (a) : (b))

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

    /* Memory */
    {
        const char e[] = "Hel\0lo!", a[] = "Hel\0lo";
        assert_memory_equal(min(sizeof(e), sizeof(a)) - 1, e, a);
        assert_memory_equal(min(sizeof(e), sizeof(a)) - 1, e, a, "My amazing %s assertion message%c", "formatted", '!');
    }
    {
        const char e[] = "Hel\0lo!", a[] = "hel\0lo";
        assert_memory_not_equal(min(sizeof(e), sizeof(a)) - 1, e, a);
        assert_memory_not_equal(min(sizeof(e), sizeof(a)) - 1, e, a, "My amazing %s assertion message%c", "formatted", '!');
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
