/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Davide Di Carlo
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

#include <assert.h>
#include <traits.h>

int main() {
    {
        int i = 0;

        traits_assert(i++ == 0);
        assert(i == 1);

        traits_assert(++i == 2);
        assert(i == 2);

        traits_assert((i = 6) == 6);
        assert(i == 6);
    }
    {
        int i = 0;

        assert_that(i++ == 0);
        assert(i == 1);

        assert_that(++i == 2);
        assert(i == 2);

        assert_that((i = 6) == 6);
        assert(i == 6);
    }
    {
        bool x = true;

        assert_true(x);
        assert_true(true == x);
        assert_true(false != x);
        assert_true(!(x = false));

        assert(!x);
    }
    {
        bool x = false;

        assert_false(x);
        assert_false(false != x);
        assert_false(true == x);
        assert_false(!(x = true));

        assert(x);
    }
    {
        int a = 0, b = 0;
        assert_equal(a++, b++);
        assert(a == 1);
        assert(b == 1);

        assert_equal(a = 6, b = 6);
        assert(a == 6);
        assert(b == 6);
    }
    {
        int a = 1, b = 0;
        assert_not_equal(a--, b++);
        assert(a == 0);
        assert(b == 1);

        assert_not_equal(a = 5, b = 6);
        assert(a == 5);
        assert(b == 6);
    }
    {
        int a = 1, b = 0;
        assert_greater(a++, b++);
        assert(a == 2);
        assert(b == 1);

        assert_greater(a = 6, b = 5);
        assert(a == 6);
        assert(b == 5);
    }
    {
        int a = 0, b = 0;
        assert_greater_equal(a += 2, ++b);
        assert(a == 2);
        assert(b == 1);

        assert_greater_equal(a = 5, b = 5);
        assert(a == 5);
        assert(b == 5);
    }
    {
        int a = 2, b = 1;
        assert_less_equal(a -= 2, --b);
        assert(a == 0);
        assert(b == 0);

        assert_less_equal(a = 5, b = 5);
        assert(a == 5);
        assert(b == 5);
    }
    {
        int a = 0, b = 1;
        assert_less(a++, b++);
        assert(a == 1);
        assert(b == 2);

        assert_less(a = 5, b = 6);
        assert(a == 5);
        assert(b == 6);
    }
    {
        int *ptr = NULL;
        assert_null(ptr);
        assert_null(ptr = ptr);
        assert_not_null(&ptr);
    }
    {
        const char a[7] = "Hel\0lo!", b[7] = "Hel\0lo?";
        size_t s = sizeof(a) / sizeof(a[0]) - 1;

        assert_memory_equal(a + 1, b + 1, s -= 1);
        assert(6);

        assert_memory_not_equal(a + 1, b + 1, s += 1);
        assert(7);
    }
    {
        const char a[] = "?Hello", b[] = "!Hello";
        assert_string_equal(a + 1, b + 1);
        assert_string_not_equal(a, b);
    }
    return 0;
}
