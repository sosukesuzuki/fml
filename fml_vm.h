#ifndef FML_VM_H
#define FML_VM_H

#include "fml_instructions.h"
#include "fml_vm_stack.h"

typedef struct VMContext {
    char* str;
    char** sp;

    Instructions* instructions;
    int pc;

    VMStack* stack;
} VMContext;

int initVM(VMContext* context, char** str, Instructions* instrcution, VMStack* vmStack);
int runVM(VMContext* context);

#endif
