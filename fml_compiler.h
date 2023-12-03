#ifndef FML_COMPILER_H
#define FML_COMPILER_H

#include "fml_instructions.h"
#include "fml_parser.h"

int compile(Node* node, Instructions* instructions);

#endif
