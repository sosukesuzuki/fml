#ifndef FML_INSTRUCTIONS_H
#define FML_INSTRUCTIONS_H

typedef struct Instruction Instruction;

typedef enum InstructionKind {
    INSTRUCTION_MATCH,
    INSTRUCTION_CHAR,
    INSTRUCTION_SPLIT,
    INSTRUCTION_JMP,
} InstructionKind;

typedef struct Instruction {
    InstructionKind kind;
    union {
        struct {
            char c;
        } iChar;

        struct {
            int pos1;
            int pos2;
        } iSplit;

        struct {
            int pos;
        } iJmp;
    } u;
} Instruction;

typedef struct {
    Instruction** instructions;
    int size;
    int cap;
} Instructions;

int appendInstruction(Instructions* instructions, Instruction* instruction);
int initInstructions(Instructions* instructions);

#endif
