#include "fml_vm.h"
#include "fml_instructions.h"
#include "fml_vm_stack.h"
#include <stdlib.h>

int initVM(VMContext* context, char** str, Instructions* instrcution, VMStack* vmStack)
{
    context->str = *str;
    context->sp = str;

    context->instructions = instrcution;
    context->pc = 0;

    context->stack = vmStack;

    return 0;
}

Instruction* pcInstruction(VMContext* context)
{
    return context->instructions->instructions[context->pc];
}

int instructionChar(VMContext* context, Instruction* instruction)
{
    if (**context->sp == instruction->u.iChar.c) {
        (*context->sp)++;
        context->pc++;

        return 1;
    }
    return 0;
}

int instructionJmp(VMContext* context, Instruction* instruction)
{
    context->pc = instruction->u.iJmp.pos;
    return 1;
}

int instructionSplit(VMContext* context, Instruction* instruction)
{
    Thread* thread = malloc(sizeof(Thread));

    thread->pc = instruction->u.iSplit.pos1;
    thread->sp = context->sp;

    pushVMStack(context->stack, thread);

    context->pc = instruction->u.iSplit.pos2;
    return 1;
}

int runVM(VMContext* context)
{
    while (1) {
        int result = 0;
        switch (pcInstruction(context)->kind) {
        case INSTRUCTION_MATCH:
            return 1;
        case INSTRUCTION_CHAR:
            result = instructionChar(context, pcInstruction(context));
            break;
        case INSTRUCTION_JMP:
            result = instructionJmp(context, pcInstruction(context));
            break;
        case INSTRUCTION_SPLIT:
            result = instructionSplit(context, pcInstruction(context));
            break;
        }

        if (!result) {
            Thread* thread = popVMStack(context->stack);
            if (thread == NULL) {
                return 0;
            }
            context->pc = thread->pc;
            context->sp = thread->sp;
        }
    }
    return 1;
}
