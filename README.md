Traits
======

Generic assertions macros written in ISO C.

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
