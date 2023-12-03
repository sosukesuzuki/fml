#include "fml_compiler.h"
#include "fml_test_utils.h"

void compile_01()
{
    Node node;
    char* s = "a";
    parseRegexp(&node, s);

    Instructions instructions;
    initInstructions(&instructions);

    int r = compile(&node, &instructions);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(instructions.size, 2);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[0]->u.iChar.c, 'a');
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_MATCH);
}

int main()
{
    RUN_TEST(compile_01);
    return 0;
}
