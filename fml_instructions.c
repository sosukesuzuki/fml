#include "fml_instructions.h"
#include <stdlib.h>

#define INIT_INSTRUCTIONS_CAP 16

int appendInstruction(Instructions* instructions, Instruction* instruction)
{
    if (instructions->size >= instructions->cap) {
        instructions->cap *= 2;
        instructions->instructions = realloc(instructions->instructions, sizeof(Instruction) * instructions->cap);
    }

    instructions->instructions[instructions->size] = instruction;
    instructions->size++;

    return 0;
}

int initInstructions(Instructions* instructions)
{
    instructions->size = 0;
    instructions->cap = INIT_INSTRUCTIONS_CAP;
    instructions->instructions = malloc(sizeof(Instruction) * instructions->cap);
    return 0;
}
