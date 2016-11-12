Traits
======

An Unit Test Framework written in ANSI C.

## Installation

Traits uses cmake as its default building system, so **cmake 3.0 or higher is required** in order to build.  
When the requirements are satisfied follow the following steps:

```bash
git clone https://github.com/daddinuz/Traits.git
cd ./Traits/build
cmake ..
make
```

this will build the Traits static library under lib/ folder and the tests under the test/ folder.

By default Traits is built with colors support.
If you want to turn off this feature just run cmake as below:

```bash
cmake -DDISABLE_COLORS=true ..
```

this will just set the definition: `NCOLOR=1` at compile time.

## API Overview

### Adding a Test Case

To define a test:

```C
Test(TestCase) {
    /** your code here **/
}
```

`TestCase` must be a valid C identifier.

### Running tests

Traits does not register tests automatically, so each Test is run using the macro `run` in your `main` function.  
This macro performs necessary setup before the test is called and handles cleanup and result tabulation afterwards.

So suppose you have declare a test named '*foo*':

```C
#include "traits.h"

Test(foo) {
    /** your test logic here **/
}

int main(void) {
    run(foo);
    return 0;
}
```

Sometimes you may want to skip a test because of code refactoring or for some other reason.  
At these times, `skip` can be called instead of `run`, control will immediately be returned
to the caller of the test, and no failures will be returned.

### Reportage

In order to print out the test report, return from your `main` the `report` function
which will take care of printing out the test report and returns the appropriate exit code.

```C
#include "traits.h"

Test(foo) {
    /** your test logic here **/
}

int main(void) {
    run(foo);
    return report();
}
```

### Assertion Summary

#### Boolean

```C
ASSERT_TRUE(condition)
ASSERT_FALSE(condition)
ASSERT(condition)
```

#### Integers

```C
ASSERT_INT_EQUAL(expected, got)
ASSERT_INT_NOT_EQUAL(expected, got)
ASSERT_INT_GREATER_EQUAL(expected, got)
ASSERT_INT_GREATER(expected, got)
ASSERT_INT_LESS_EQUAL(expected, got)
ASSERT_INT_LESS(expected, got)
ASSERT_INT_WITHIN(delta, expected, got)
```

Compare two signed integers type and display errors as signed integers.
In order to avoid casts when you need to specify the exact size, you can
use the specific size version appending the size after the type as in the following example:

```C
ASSERT_INT16_EQUAL(expected, got)
```

So the meta-signature is:

```C
ASSERT_INT<s>_EQUAL(expected, got)
ASSERT_INT<s>_NOT_EQUAL(expected, got)
ASSERT_INT<s>_GREATER_EQUAL(expected, got)
ASSERT_INT<s>_GREATER(expected, got)
ASSERT_INT<s>_LESS_EQUAL(expected, got)
ASSERT_INT<s>_LESS(expected, got)
ASSERT_INT<s>_WITHIN(delta, expected, got)
```

Where \<s\> must be:

* Not specified - default size is the same of `sizeof(int)`
* 8
* 16
* 32
* 64 **(if supported by your architecture**)

For unsigned types just prepend an 'U' before 'INT':

```C
ASSERT_UINT<s>_EQUAL(expected, got)
ASSERT_UINT<s>_NOT_EQUAL(expected, got)
ASSERT_UINT<s>_GREATER_EQUAL(expected, got)
ASSERT_UINT<s>_GREATER(expected, got)
ASSERT_UINT<s>_LESS_EQUAL(expected, got)
ASSERT_UINT<s>_LESS(expected, got)
ASSERT_UINT<s>_WITHIN(delta, expected, got)
```

There is a special unsigned assertion type that is basically an alias for
the unsigned type matching `sizeof(size_t)`

```C
ASSERT_SIZE_EQUAL(expected, got)
ASSERT_SIZE_NOT_EQUAL(expected, got)
ASSERT_SIZE_GREATER_EQUAL(expected, got)
ASSERT_SIZE_GREATER(expected, got)
ASSERT_SIZE_LESS_EQUAL(expected, got)
ASSERT_SIZE_LESS(expected, got)
ASSERT_SIZE_WITHIN(delta, expected, got)
```

#### Floating

Floating assertions follows don't have size specifier and don't support
the unsigned version, the signature is:

```C
ASSERT_FLOAT_EQUAL(expected, got)
ASSERT_FLOAT_NOT_EQUAL(expected, got)
ASSERT_FLOAT_GREATER_EQUAL(expected, got)
ASSERT_FLOAT_GREATER(expected, got)
ASSERT_FLOAT_LESS_EQUAL(expected, got)
ASSERT_FLOAT_LESS(expected, got)
ASSERT_FLOAT_WITHIN(delta, expected, got)
```

```C
ASSERT_DOUBLE_EQUAL(expected, got)
ASSERT_DOUBLE_NOT_EQUAL(expected, got)
ASSERT_DOUBLE_GREATER_EQUAL(expected, got)
ASSERT_DOUBLE_GREATER(expected, got)
ASSERT_DOUBLE_LESS_EQUAL(expected, got)
ASSERT_DOUBLE_LESS(expected, got)
ASSERT_DOUBLE_WITHIN(delta, expected, got)
```

#### Strings

```C
ASSERT_STR_EQUAL(expected, got)
ASSERT_STR_NOT_EQUAL(expected, got)
```

#### Pointers

```C
ASSERT_PTR_EQUAL(expected, got)
ASSERT_PTR_NOT_EQUAL(expected, got)
ASSERT_PTR_NULL(pointer)
ASSERT_PTR_NOT_NULL(pointer)
```
