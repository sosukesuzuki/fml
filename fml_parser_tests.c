#include "fml_parser.h"
#include "fml_test_utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void parseRegexp_03()
{
    Node node;
    char* s = "a*";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_QTFR);
    TEST_ASSERT(node.u.qtfrNode.child->kind, NODE_CHAR);
    TEST_ASSERT(node.u.qtfrNode.child->u.charNode.c, 'a');
}

void parseRegexp_04()
{
    Node node;
    char* s = "a|b";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.altNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.charNode.c, 'b');
}

void parseRegexp_05()
{
    Node node;
    char* s = "a|b*";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.altNode.right->kind, NODE_QTFR);
    TEST_ASSERT(node.u.altNode.right->u.qtfrNode.child->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.qtfrNode.child->u.charNode.c, 'b');
}

void parseRegexp_06()
{
    Node node;
    char* s = "(a|b)*";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_QTFR);
    TEST_ASSERT(node.u.qtfrNode.child->kind, NODE_ALT);
    TEST_ASSERT(node.u.qtfrNode.child->u.altNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.qtfrNode.child->u.altNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.qtfrNode.child->u.altNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.qtfrNode.child->u.altNode.right->u.charNode.c, 'b');
}

void parseRegexp_07()
{
    Node node;
    char* s = "ab|c";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->kind, NODE_CONCAT);
    TEST_ASSERT(node.u.altNode.left->u.concatNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.concatNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.altNode.left->u.concatNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.concatNode.right->u.charNode.c, 'b');
    TEST_ASSERT(node.u.altNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.charNode.c, 'c');
}

void parseRegexp_08()
{
    Node node;
    char* s = "a|bc";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.altNode.right->kind, NODE_CONCAT);
    TEST_ASSERT(node.u.altNode.right->u.concatNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.concatNode.left->u.charNode.c, 'b');
    TEST_ASSERT(node.u.altNode.right->u.concatNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.concatNode.right->u.charNode.c, 'c');
}

void parseRegexp_09()
{
    Node node;
    char* s = "a|b|c";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->kind, NODE_ALT);
    TEST_ASSERT(node.u.altNode.left->u.altNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.altNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.altNode.left->u.altNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.left->u.altNode.right->u.charNode.c, 'b');
    TEST_ASSERT(node.u.altNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.altNode.right->u.charNode.c, 'c');
}

void parseRegexp_10()
{
    Node node;
    char* s = "abc";
    int r = parseRegexp(&node, s);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(node.kind, NODE_CONCAT);
    TEST_ASSERT(node.u.concatNode.left->kind, NODE_CONCAT);
    TEST_ASSERT(node.u.concatNode.left->u.concatNode.left->kind, NODE_CHAR);
    TEST_ASSERT(node.u.concatNode.left->u.concatNode.left->u.charNode.c, 'a');
    TEST_ASSERT(node.u.concatNode.left->u.concatNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.concatNode.left->u.concatNode.right->u.charNode.c, 'b');
    TEST_ASSERT(node.u.concatNode.right->kind, NODE_CHAR);
    TEST_ASSERT(node.u.concatNode.right->u.charNode.c, 'c');
}

int main()
{
    RUN_TEST(parseRegexp_01);
    RUN_TEST(parseRegexp_02);
    RUN_TEST(parseRegexp_03);
    RUN_TEST(parseRegexp_04);
    RUN_TEST(parseRegexp_05);
    RUN_TEST(parseRegexp_06);
    RUN_TEST(parseRegexp_07);
    RUN_TEST(parseRegexp_08);
    RUN_TEST(parseRegexp_09);
    RUN_TEST(parseRegexp_10);

    return 0;
}
