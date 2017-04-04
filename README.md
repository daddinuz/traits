Traits
======

A light-weight unit test framework written in ISO C (C99).

## Framework Overview

In order to define a test:

```C
TRAITS(_Case) {
    /* Your assertions here */
}
```

where `_Case` is the test name and must be a valid C identifier.  
In order to register tests, write your main function like this:

```C
int main() {
    traits_run(_Case);
    traits_skip(_Case);
    /* ... */
    return 0;
}
```

where `_Case` must match a test case previously declared using `TRAITS`.

***Notice***:
- before every test `traits_run` will call a function (that must be implemented by the user) which signature is: `void traits_setup(void);`
- after every test `traits_run` will call a function (that must be implemented by the user) which signature is: `void traits_teardown(void);`

## Assertion Summary

#### Boolean

```C
assert(_Expression)
assert_true(_Expression)
assert_false(_Expression)
```

#### Numerical

```C
assert_equal(_Expected, _Actual)
assert_not_equal(_Expected, _Actual)
assert_less_equal(_Expected, _Actual)
assert_greater_equal(_Expected, _Actual)
assert_less(_Expected, _Actual)
assert_greater(_Expected, _Actual)
```

#### Pointer

```C
assert_null(_Pointer)
assert_not_null(_Pointer)
```

#### String

```C
assert_string_equal(_Expected, _Actual)
assert_string_not_equal(_Expected, _Actual)
```
