#ifndef FML_PARSER_H
#define FML_PARSER_H

typedef enum TokenKind {
  TK_LATIN_LETTER,      // a-z
  TK_ASTERISK,          // *
  TK_VERTICAL_BAR,      // |
  TK_LEFT_PARENTHESES,  // (
  TK_RIGHT_PARENTHESES, // )
} TokenKind;

typedef struct {
  TokenKind kind;
  char c;
} Token;

typedef enum NodeKind {
  NODE_CHAR,   // a
  NODE_ALT,    // a|b
  NODE_CONCAT, // ab
  NODE_QTFE,   // a*
} NodeKind;

typedef struct Node Node;

typedef struct CharNode {
  char c;
} CharNode;

typedef struct AltNode {
  Node *left;
  Node *right;
} AltNode;

typedef struct ConcatNode {
  Node *left;
  Node *right;
} ConcatNode;

typedef struct QtfeNode {
  Node *child;
} QtfeNode;

struct Node {
  NodeKind kind;
  union {
    CharNode charNode;
    AltNode altNode;
    ConcatNode concatNode;
    QtfeNode qtfeNode;
  };
};

int parseRegexp(Node *node, char *str);

#endif
