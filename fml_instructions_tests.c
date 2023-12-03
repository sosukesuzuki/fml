#include "fml_instructions.h"
#include "fml_test_utils.h"

void appendInstruction_01() {
    Instructions instructions;
    initInstructions(&instructions);

    Instruction instruction;
    instruction.kind = INSTRUCTION_MATCH;
    appendInstruction(&instructions, instruction);

    TEST_ASSERT(instructions.size, 1);
    TEST_ASSERT(instructions.cap, 16);
    TEST_ASSERT(instructions.instructions[0].kind, INSTRUCTION_MATCH);
}

int main() {
    RUN_TEST(appendInstruction_01);
    return 0;
}
