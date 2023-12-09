#include "fml_lib.h"
#include "fml_test_utils.h"

void fmlTest_01()
{
    TEST_ASSERT(fmlTest("a", "a"), 1);
}

void fmlTest_02()
{
    TEST_ASSERT(fmlTest("a", "b"), 0);
}

void fmlTest_03()
{
    TEST_ASSERT(fmlTest("a*", "aaaaaaaa"), 1);
}

void fmlTest_04()
{
    TEST_ASSERT(fmlTest("a|b", "a"), 1);
}

void fmlTest_05()
{
    TEST_ASSERT(fmlTest("a|b", "b"), 1);
}

void fmlTest_06()
{
    TEST_ASSERT(fmlTest("a|b", "c"), 0);
}

void fmlTest_07()
{
    TEST_ASSERT(fmlTest("abc", "abc"), 1);
}

void fmlTest_08()
{
    TEST_ASSERT(fmlTest("abc", "abd"), 0);
}

int main()
{
    RUN_TEST(fmlTest_01);
    RUN_TEST(fmlTest_02);
    RUN_TEST(fmlTest_03);
    RUN_TEST(fmlTest_04);
    RUN_TEST(fmlTest_05);
    RUN_TEST(fmlTest_06);
    RUN_TEST(fmlTest_07);
    RUN_TEST(fmlTest_08);
    return 0;
}
