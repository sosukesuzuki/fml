#include "fml_lib.h"
#include "fml_test_utils.h"

void fmlTest_01() {
    TEST_ASSERT(fmlTest("a", "a"), 1);
}

void fmlTest_02() {
    TEST_ASSERT(fmlTest("a", "b"), 0);
}

int main() {
    RUN_TEST(fmlTest_01);
    RUN_TEST(fmlTest_02);
    return 0;
}
