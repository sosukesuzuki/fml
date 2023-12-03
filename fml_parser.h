#ifndef FML_PARSER_H
#define FML_PARSER_H

typedef enum TokenKind {
    TK_LATIN_LETTER, // a-z
    TK_ASTERISK, // *
    TK_VERTICAL_BAR, // |
    TK_LEFT_PARENTHESES, // (
    TK_RIGHT_PARENTHESES, // )
    TK_END_OF_STRING, // \0
} TokenKind;

typedef struct {
    TokenKind kind;
    char c;
} Token;

typedef enum NodeKind {
    NODE_CHAR, // a
    NODE_ALT, // a|b
    NODE_CONCAT, // ab
    NODE_QTFR, // a*
} NodeKind;

typedef struct Node Node;

typedef struct CharNode {
    char c;
} CharNode;

typedef struct AltNode {
    Node* left;
    Node* right;
} AltNode;

typedef struct ConcatNode {
    Node* left;
    Node* right;
} ConcatNode;

typedef struct QtfrNode {
    Node* child;
} QtfrNode;

struct Node {
    NodeKind kind;
    union {
        CharNode charNode;
        AltNode altNode;
        ConcatNode concatNode;
        QtfrNode qtfrNode;
    } u;
};

int parseRegexp(Node* node, char* str);

#endif
