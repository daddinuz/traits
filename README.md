Traits
======

Traits is an assertion library written in C99.  
It's an header only library so you just have to include
`traits.h` in your code and your ready for bugs hunting. 

## Assertion Summary

Below are listed all the assertion macros in the library.
Every macro is "overloaded" and can be called specifying 
a custom message in the same way as you would do using printf.  

That means that you can write something like this:
```C
/* Just assert without specifying a message */
assert_that(5 == 5);

/* Assert specifying a message */
int x = 5, y = 6;
assert_that(x == y, "Ops! Expected to be %d got %d", x, y);
```

#### Basic

```C
traits_assert(x);
assert_that(x);
```

#### Boolean

```C
assert_true(x);
assert_false(x);
```

#### Numerical

```C
assert_equal(e, a);
assert_not_equal(e, a);
assert_greater(e, a);
assert_greater_equal(e, a);
assert_less(e, a);
assert_less_equal(e, a);
```

#### Pointer

```C
assert_null(x);
assert_not_null(x);
```

#### Memory

```C
assert_memory_equal(s, e, a);
assert_memory_not_equal(s, e, a);
```

#### String

```C
assert_string_equal(e, a);
assert_string_not_equal(e, a);
```

## Helpers

Traits defines also some helpers to make easier and safer your custom assertion:

```C
eq(e, a)        /* ((e) == (a)) */
ne(e, a)        /* ((e) != (a)) */
gt(e, a)        /* ((e)  > (a)) */
ge(e, a)        /* ((e) >= (a)) */
lt(e, a)        /* ((e)  < (a)) */
le(e, a)        /* ((e) <= (a)) */

as(T, x)        /* It's simply a cast: ((T)(x)) */

/* Those are just a combination of the above */
eq_as(T, e, a)  /* eq(as(T, e), as(T, a)) */
ne_as(T, e, a)  /* ne(as(T, e), as(T, a)) */
gt_as(T, e, a)  /* gt(as(T, e), as(T, a)) */
ge_as(T, e, a)  /* ge(as(T, e), as(T, a)) */
lt_as(T, e, a)  /* lt(as(T, e), as(T, a)) */
le_as(T, e, a)  /* le(as(T, e), as(T, a)) */
```
