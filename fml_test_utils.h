#ifndef FML_TEST_UTILS_H
#define FML_TEST_UTILS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_ASSERT(actual, expected)                                               \
    do {                                                                            \
        if ((actual) != (expected)) {                                               \
            fprintf(                                                                \
                stderr,                                                             \
                "Assertion failed: (%s: %d)\nExpected: %s (%d)\nActual: %s (%d)\n", \
                __FILE__, __LINE__, #expected, expected, #actual, actual);          \
            exit(1);                                                                \
        }                                                                           \
    } while (0)

#define RUN_TEST(test_func)                       \
    do {                                          \
        printf("Running test: %s\n", #test_func); \
        test_func();                              \
        printf("Test passed.\n\n");               \
    } while (0)

#endif // FML_TEST_UTILS_H
