#include <stdio.h>

#include "fml_parser.h"

#define BUFFER_SIZE 256

int main()
{
    char s[BUFFER_SIZE];
    scanf("%s", s);

    Node node;
    parseRegexp(&node, s);

    return 0;
}
