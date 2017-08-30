/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   August 30, 2017 
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "traits.h"

void ___traits_assert(
        size_t line, const char *file, const char *assertion, bool status, bool hasMessage, const char *message, ...
) {
    if (!status) {
        fprintf(stderr, "At %s:%zu\nAssertion: `%s` failed.\n", file, line, assertion);
        if (hasMessage) {
            va_list args;
            va_start(args, message);
            vfprintf(stderr, message, args);
            va_end(args);
        }
        exit(1);
    }
}
