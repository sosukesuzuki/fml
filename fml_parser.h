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

#endif
