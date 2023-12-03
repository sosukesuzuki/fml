#include "fml_compiler.h"

// a
void compileChar(Node* node, Instructions* instructions)
{
    Instruction* instruction = malloc(sizeof(Instruction));
    instruction->kind = INSTRUCTION_CHAR;
    instruction->u.iChar.c = node->u.charNode.c;
    appendInstruction(instructions, instruction);
}

// ab
void compileConcat(Node* node, Instructions* instructions)
{
    compileNode(node->u.concatNode.left, instructions);
    compileNode(node->u.concatNode.right, instructions);
}

// a*
void compileQtfr(Node* node, Instructions* instructions)
{
    // L1: split L2, L3
    // L2: compileNode(value.expression)
    //     jmp L1
    // L3:
    int l1 = instructions->size;
    Instruction* instruction1 = malloc(sizeof(Instruction));
    instruction1->kind = INSTRUCTION_SPLIT;
    instruction1->u.iSplit.offset1 = instructions->size + 1;
    appendInstruction(instructions, instruction1);

    int l2 = instructions->size;
    compileNode(node->u.qtfeNode.child, instructions);

    Instruction* instructionJmp = malloc(sizeof(Instruction));
    instructionJmp->kind = INSTRUCTION_JMP;
    instructionJmp->u.iJmp.offset = l1;
    appendInstruction(instructions, instructionJmp);

    instruction1->u.iSplit.offset2 = instructions->size;
}

// a|b
void compileAlt(Node* node, Instructions* instructions)
{
    // split L1, L2
    // L1: compileNode(value.left)
    //     jmp L3
    // L2: compileNode(value.right)
    // L3:
    Instruction* instructionSplit = malloc(sizeof(Instruction));
    instructionSplit->kind = INSTRUCTION_SPLIT;
    instructionSplit->u.iSplit.offset1 = instructions->size + 1;
    appendInstruction(instructions, instructionSplit);

    compileNode(node->u.altNode.left, instructions);
    Instruction* instructionJmp = malloc(sizeof(Instruction));
    instructionJmp->kind = INSTRUCTION_JMP;
    appendInstruction(instructions, instructionJmp);

    instructionSplit->u.iSplit.offset2 = instructions->size;

    compileNode(node->u.altNode.right, instructions);

    instructionJmp->u.iJmp.offset = instructions->size;
}

void compileNode(Node* node, Instructions* instructions)
{
    switch (node->kind) {
    case NODE_CHAR:
        compileChar(node, instructions);
        break;
    case NODE_CONCAT:
        compileConcat(node, instructions);
        break;
    case NODE_ALT:
        compileAlt(node, instructions);
        break;
    case NODE_QTFE:
        compileQtfr(node, instructions);
        break;
    }
}

int compile(Node* node, Instructions* instructions)
{
    compileNode(node, instructions);
    Instruction* instruction = malloc(sizeof(Instruction));
    instruction->kind = INSTRUCTION_MATCH;
    appendInstruction(instructions, instruction);
    return 0;
}
