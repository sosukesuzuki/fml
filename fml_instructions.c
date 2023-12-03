#include "fml_instructions.h";
#include "fml_parser.h";

int appendInstruction(Instructions* instructions, Instruction instruction)
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
    instructions->cap = 16;
    instructions->instructions = malloc(sizeof(Instruction) * instructions->cap);
    return 0;
}
