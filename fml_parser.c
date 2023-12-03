#include "fml_parser.h"
#include <ctype.h>
#include <stdlib.h>

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

int parseSubexpr(char **s, Node *node, Token *token);
int parseAlt(char **s, Node *node, Token *token);
int parseConcat(char **s, Node *node, Token *token);
int parseQtrf(char **s, Node *node, Token *token);
int parseFactor(char **s, Node *node, Token *token);
int parseChar(char **s, Node *node, Token *token);

int parseSubexpr(char **s, Node *node, Token *token) {
  return parseAlt(s, node, token);
}

int parseAlt(char **s, Node *node, Token *token) {
  int r;
  r = parseConcat(s, node, token);
  if (r < 0)
    return r;
  for (;;) {
    r = fetchToken(token, s);
    if (r < 0)
      return r;
    if (token->kind == TK_VERTICAL_BAR) {
      (*s)++;
      Node *right = malloc(sizeof(Node));
      node->kind = NODE_ALT;
      node->altNode.left = node;
      node->altNode.right = right;
      r = parseConcat(s, right, token);
      if (r < 0)
        return r;
      return 0;
    } else {
      return 0;
    }
  }
}

int parseConcat(char **s, Node *node, Token *token) {
  int r;
  r = parseQtrf(s, node, token);
  for (;;) {
    r = fetchToken(token, s);
    if (r < 0)
      return r;
    if (token->kind == TK_LATIN_LETTER) {
      Node *right = malloc(sizeof(Node));
      node->kind = NODE_CONCAT;
      node->concatNode.left = node;
      node->concatNode.right = right;
      r = parseQtrf(s, right, token);
      if (r < 0)
        return r;
      return 0;
    } else if (token->kind == TK_LEFT_PARENTHESES) {
      Node *right = malloc(sizeof(Node));
      node->kind = NODE_CONCAT;
      node->concatNode.left = node;
      node->concatNode.right = right;
      r = parseConcat(s, right, token);
      if (r < 0)
        return r;
      return 0;
    } else {
      return 0;
    }
  }
}

int parseQtrf(char **s, Node *node, Token *token) {
  int r;
  r = parseFactor(s, node, token);
  if (r < 0)
    return r;
  r = fetchToken(token, s);
  if (r < 0)
    return r;
  if (token->kind == TK_ASTERISK) {
    (*s)++;
    node->kind = NODE_QTFE;
    node->qtfeNode.child = node;
    return 0;
  }
  return 0;
}

int parseFactor(char **s, Node *node, Token *token) {
  int r;
  r = fetchToken(token, s);
  if (r < 0)
    return r;
  if (token->kind == TK_LATIN_LETTER) {
    return parseChar(s, node, token);
  } else if (token->kind == TK_LEFT_PARENTHESES) {
    (*s)++;
    return parseSubexpr(s, node, token);
  }
  return -1;
}

int parseChar(char **s, Node *node, Token *token) {
  int r;
  r = fetchToken(token, s);
  if (r < 0)
    return r;
  if (token->kind != TK_LATIN_LETTER)
    return -1;
  node->kind = NODE_CHAR;
  node->charNode.c = token->c;
  return 0;
}

int parseRegexp(Node *node, char *str) {
  int r;
  char **s = &str;
  Token token;

  r = fetchToken(&token, s);
  if (r < 0) {
    return r;
  }

  r = parseSubexpr(s, node, &token);
  if (r < 0) {
    return r;
  }

  return -1;
}
