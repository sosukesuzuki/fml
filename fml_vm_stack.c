#include "fml_vm_stack.h"
#include <stdlib.h>

#define VM_STACK_CAP 32

void initVMStack(VMStack* stack)
{
    stack->top = -1;
    stack->cap = VM_STACK_CAP;
    stack->threads = malloc(sizeof(Thread) * stack->cap);
}

int isVMStackFull(VMStack* stack)
{
    return stack->top >= stack->cap - 1;
}

int pushVMStack(VMStack* stack, Thread* thread)
{
    if (isVMStackFull(stack)) {
        return -1;
    }
    stack->top++;
    stack->threads[stack->top] = thread;
    return 0;
}

int isVMStackEmpty(VMStack* stack)
{
    return stack->top < 0;
}

Thread* popVMStack(VMStack* stack)
{
    if (isVMStackEmpty(stack)) {
        return NULL;
    }
    Thread* thread = stack->threads[stack->top];
    stack->top--;
    return thread;
}
