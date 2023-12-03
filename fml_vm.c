#include "fml_instructions.h"
#include "fml_vm_stack.h"

typedef struct VMContext {
    char *str;
    char **sp;

    Instructions *instructions;
    Instruction *pc;

    VMStack* stack;
} VMContext;

int initVMContext(VMContext* context, char* str)
{
    context->str = str;
    context->sp = &str;

    context->instructions = malloc(sizeof(Instructions));
    initInstructions(context->instructions);

    context->stack = malloc(sizeof(VMStack));
    initVMStack(context->stack);

    return 0;
}