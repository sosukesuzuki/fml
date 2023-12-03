#include "fml_test_utils.h"
#include "fml_vm_stack.h"

void pushStack_01()
{
    VMStack stack;
    initVMStack(&stack);

    Thread thread = { 0, 0 };
    pushVMStack(&stack, &thread);

    TEST_ASSERT(stack.top, 0);
    TEST_ASSERT(stack.cap, 32);
    TEST_ASSERT(stack.threads[0]->pc, 0);
    TEST_ASSERT(stack.threads[0]->sp, 0);
}

int main()
{
    RUN_TEST(pushStack_01);
    return 0;
}
