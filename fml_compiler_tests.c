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

void compile_02()
{
    Node node;
    char* s = "ab";
    parseRegexp(&node, s);

    Instructions instructions;
    initInstructions(&instructions);

    int r = compile(&node, &instructions);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(instructions.size, 3);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[0]->u.iChar.c, 'a');
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[1]->u.iChar.c, 'b');
    TEST_ASSERT(instructions.instructions[2]->kind, INSTRUCTION_MATCH);
}

void compile_03()
{
    Node node;
    char* s = "a*";
    parseRegexp(&node, s);

    Instructions instructions;
    initInstructions(&instructions);

    int r = compile(&node, &instructions);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(instructions.size, 4);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_SPLIT);
    TEST_ASSERT(instructions.instructions[0]->u.iSplit.pos1, 1);
    TEST_ASSERT(instructions.instructions[0]->u.iSplit.pos2, 3);
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[1]->u.iChar.c, 'a');
    TEST_ASSERT(instructions.instructions[2]->kind, INSTRUCTION_JMP);
    TEST_ASSERT(instructions.instructions[2]->u.iJmp.pos, 0);
    TEST_ASSERT(instructions.instructions[3]->kind, INSTRUCTION_MATCH);
}

void compile_04()
{
    Node node;
    char* s = "a|b";
    parseRegexp(&node, s);

    Instructions instructions;
    initInstructions(&instructions);

    int r = compile(&node, &instructions);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(instructions.size, 5);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_SPLIT);
    TEST_ASSERT(instructions.instructions[0]->u.iSplit.pos1, 1);
    TEST_ASSERT(instructions.instructions[0]->u.iSplit.pos2, 3);
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[1]->u.iChar.c, 'a');
    TEST_ASSERT(instructions.instructions[2]->kind, INSTRUCTION_JMP);
    TEST_ASSERT(instructions.instructions[2]->u.iJmp.pos, 4);
    TEST_ASSERT(instructions.instructions[3]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[3]->u.iChar.c, 'b');
    TEST_ASSERT(instructions.instructions[4]->kind, INSTRUCTION_MATCH);
}

void compile_05()
{
    Node node;
    char* s = "abc";
    parseRegexp(&node, s);

    Instructions instructions;
    initInstructions(&instructions);

    int r = compile(&node, &instructions);

    TEST_ASSERT(r, 0);
    TEST_ASSERT(instructions.size, 4);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[0]->u.iChar.c, 'a');
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[1]->u.iChar.c, 'b');
    TEST_ASSERT(instructions.instructions[2]->kind, INSTRUCTION_CHAR);
    TEST_ASSERT(instructions.instructions[2]->u.iChar.c, 'c');
    TEST_ASSERT(instructions.instructions[3]->kind, INSTRUCTION_MATCH);
}

int main()
{
    RUN_TEST(compile_01);
    RUN_TEST(compile_02);
    RUN_TEST(compile_03);
    RUN_TEST(compile_04);
    RUN_TEST(compile_05);
    return 0;
}
