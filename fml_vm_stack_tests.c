#include "fml_test_utils.h"
#include "fml_vm_stack.h"
#include <stdlib.h>

void pushVMStack_01()
{
    int r;
    VMStack stack;
    initVMStack(&stack);

    Thread thread = { 0, 0 };
    r = pushVMStack(&stack, &thread);
    TEST_ASSERT(r, 0);

    TEST_ASSERT(stack.top, 0);
    TEST_ASSERT(stack.cap, 32);
    TEST_ASSERT(stack.threads[0]->pc, 0);
    TEST_ASSERT(stack.threads[0]->sp, 0);
}

void pushVMStack_02()
{
    int r;
    VMStack stack;
    initVMStack(&stack);

    Thread thread1 = { 0, 0 };
    r = pushVMStack(&stack, &thread1);
    TEST_ASSERT(r, 0);

    Thread thread2 = { 1, 1 };
    pushVMStack(&stack, &thread2);
    TEST_ASSERT(r, 0);

    TEST_ASSERT(stack.top, 1);
    TEST_ASSERT(stack.cap, 32);
    TEST_ASSERT(stack.threads[0]->pc, 0);
    TEST_ASSERT(stack.threads[0]->sp, 0);
    TEST_ASSERT(stack.threads[1]->pc, 1);
    TEST_ASSERT(stack.threads[1]->sp, 1);
}

void pushVMStack_03()
{
    int r;
    int cap = 32;

    VMStack stack;
    initVMStack(&stack);

    for (int i = 0; i < cap; i++) {
        Thread thread = { i, i };
        r = pushVMStack(&stack, &thread);
        TEST_ASSERT(r, 0);
    }

    Thread thread = { 0, 0 };
    r = pushVMStack(&stack, &thread);
    TEST_ASSERT(r, -1);
}

void popVMStack_01()
{
    int r;
    VMStack stack;
    initVMStack(&stack);

    Thread thread = { 0, 0 };
    r = pushVMStack(&stack, &thread);
    TEST_ASSERT(r, 0);

    Thread* poppedThread = popVMStack(&stack);
    TEST_ASSERT(poppedThread->pc, 0);
    TEST_ASSERT(poppedThread->sp, 0);

    TEST_ASSERT(stack.top, -1);
    TEST_ASSERT(stack.cap, 32);
}

void popVMStack_02()
{
    VMStack stack;
    initVMStack(&stack);

    Thread* poppedThread = popVMStack(&stack);
    TEST_ASSERT(poppedThread == NULL, 1);

    TEST_ASSERT(stack.top, -1);
    TEST_ASSERT(stack.cap, 32);
}

int main()
{
    RUN_TEST(pushVMStack_01);
    RUN_TEST(pushVMStack_02);
    RUN_TEST(pushVMStack_03);
    RUN_TEST(popVMStack_01);
    RUN_TEST(popVMStack_02);
    return 0;
}
