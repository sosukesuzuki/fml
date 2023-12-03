#include "fml_parser.h"
#include <ctype.h>

int fetchToken(Token *token, char **s) {
  char *p = *s;

  if (isalpha(*p)) {
    token->kind = TK_LATIN_LETTER;
    token->c = *p;
    return 0;
  } else if (*p == '|') {
    token->kind = TK_VERTICAL_BAR;
    token->c = '\0';
    return 0;
  } else if (*p == '*') {
    token->kind = TK_ASTERISK;
    token->c = '\0';
    return 0;
  } else if (*p == '(') {
    token->kind = TK_LEFT_PARENTHESES;
    token->c = '\0';
    return 0;
  } else if (*p == ')') {
    token->kind = TK_RIGHT_PARENTHESES;
    token->c = '\0';
    return 0;
  }

  return -1;
}

int parseRegexp(char *str) {
  int r;
  char **s = &str;
  Token token;

  while (**s != '\0') {
    r = fetchToken(&token, s);
    if (r < 0) {
      return r;
    }
    (*s)++;
  }

  return -1;
}
