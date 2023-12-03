#include "fml_instructions.h"
#include "fml_test_utils.h"

void appendInstruction_01()
{
    Instructions instructions;
    initInstructions(&instructions);

    Instruction instruction;
    instruction.kind = INSTRUCTION_MATCH;
    appendInstruction(&instructions, &instruction);

    TEST_ASSERT(instructions.size, 1);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_MATCH);
}

void appendInstruction_02()
{
    Instructions instructions;
    initInstructions(&instructions);

    Instruction instruction1;
    instruction1.kind = INSTRUCTION_MATCH;
    appendInstruction(&instructions, &instruction1);

    Instruction instruction2;
    instruction2.kind = INSTRUCTION_CHAR;
    instruction2.u.iChar.c = 'a';
    appendInstruction(&instructions, &instruction2);

    TEST_ASSERT(instructions.size, 2);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0]->kind, INSTRUCTION_MATCH);
    TEST_ASSERT(instructions.instructions[1]->kind, INSTRUCTION_CHAR);
}

void appendInstruction_03()
{
    Instructions instructions;
    initInstructions(&instructions);

    int cap = 16;

    for (int i = 0; i < cap + 1; i++) {
        Instruction instruction;
        instruction.kind = INSTRUCTION_MATCH;
        appendInstruction(&instructions, &instruction);
    }

    TEST_ASSERT(instructions.size, 17);
    TEST_ASSERT(instructions.cap, cap * 2);
}

int main()
{
    RUN_TEST(appendInstruction_01);
    RUN_TEST(appendInstruction_02);
    RUN_TEST(appendInstruction_03);
    return 0;
}
