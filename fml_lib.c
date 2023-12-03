#include "fml_parser.h"
#include "fml_compiler.h"
#include "fml_instructions.h"
#include "fml_vm_stack.h"
#include "fml_vm.h"

int fmlTest(char* regexp, char* str)
{
    Node node;
    parseRegexp(&node, regexp);

    Instructions instructions;
    initInstructions(&instructions);
    compile(&node, &instructions);

    VMStack vmStack;
    initVMStack(&vmStack);

    VMContext context;
    initVM(&context, str, &instructions, &vmStack);

    return runVM(&context);
}