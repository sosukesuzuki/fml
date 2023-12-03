#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fml_parser.h"

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

void parseRegexp_01()
{
    Node node;
    char* s = "a";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_CHAR);
    TEST_ASSERT(node.u.charNode.c, 'a');
}

void parseRegexp_02()
{
    Node node;
    char* s = "ab";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_CONCAT);
    TEST_ASSERT(node.u.concatNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.concatNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.concatNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.concatNode.right->u.charNode.c, 'b');
}

int main()
{
    RUN_TEST(parseRegexp_01);
    RUN_TEST(parseRegexp_02);

    return 0;
}
