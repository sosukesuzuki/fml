#include "fml_parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fetchToken(Token* token, char** s)
{
    char* p = *s;

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
    } else if (*p == '\0') {
        token->kind = TK_END_OF_STRING;
        token->c = '\0';
        return 0;
    }

    return -1;
}

int parseSubexpr(char** s, Node* node, Token* token);
int parseAlt(char** s, Node* node, Token* token);
int parseConcat(char** s, Node* node, Token* token);
int parseQtrf(char** s, Node* node, Token* token);
int parseFactor(char** s, Node* node, Token* token);
int parseChar(char** s, Node* node, Token* token);

int parseSubexpr(char** s, Node* node, Token* token)
{
    return parseAlt(s, node, token);
}

int parseAlt(char** s, Node* node, Token* token)
{
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
            Node* left = malloc(sizeof(Node));
            memcpy(left, node, sizeof(Node));

            Node* right = malloc(sizeof(Node));
            r = parseConcat(s, right, token);
            if (r < 0)
                return r;

            node->kind = NODE_ALT;
            node->u.altNode.left = left;
            node->u.altNode.right = right;
        } else {
            return 0;
        }
    }
}

int parseConcat(char** s, Node* node, Token* token)
{
    int r;
    r = parseQtrf(s, node, token);
    if (r < 0)
        return r;
    for (;;) {
        r = fetchToken(token, s);
        if (r < 0)
            return r;
        if (token->kind == TK_LATIN_LETTER) {
            Node* right = malloc(sizeof(Node));
            Node* left = malloc(sizeof(Node));
            memcpy(left, node, sizeof(Node));

            node->kind = NODE_CONCAT;
            node->u.concatNode.left = left;
            node->u.concatNode.right = right;
            r = parseQtrf(s, right, token);
            if (r < 0)
                return r;
        } else if (token->kind == TK_LEFT_PARENTHESES) {
            Node* right = malloc(sizeof(Node));
            Node* left = malloc(sizeof(Node));
            memcpy(left, node, sizeof(Node));

            node->kind = NODE_CONCAT;
            node->u.concatNode.left = left;
            node->u.concatNode.right = right;
            r = parseConcat(s, right, token);
            if (r < 0)
                return r;
        } else {
            return 0;
        }
    }
}

int parseQtrf(char** s, Node* node, Token* token)
{
    int r;
    r = parseFactor(s, node, token);
    if (r < 0)
        return r;
    r = fetchToken(token, s);
    if (r < 0)
        return r;
    if (token->kind == TK_ASTERISK) {
        (*s)++;
        Node* child = malloc(sizeof(Node));
        memcpy(child, node, sizeof(Node));
        node->kind = NODE_QTFR;
        node->u.qtfrNode.child = child;
        return 0;
    }
    return 0;
}

int parseFactor(char** s, Node* node, Token* token)
{
    int r;
    r = fetchToken(token, s);
    if (r < 0)
        return r;
    if (token->kind == TK_LATIN_LETTER) {
        return parseChar(s, node, token);
    } else if (token->kind == TK_LEFT_PARENTHESES) {
        (*s)++;
        r = parseSubexpr(s, node, token);
        if (r < 0)
            return r;
        r = fetchToken(token, s);
        if (r < 0)
            return r;
        if (token->kind == TK_RIGHT_PARENTHESES) {
            (*s)++;
        }
        return 0;
    }
    return -1;
}

int parseChar(char** s, Node* node, Token* token)
{
    int r;
    r = fetchToken(token, s);
    if (r < 0)
        return r;
    if (token->kind != TK_LATIN_LETTER)
        return -1;
    (*s)++;
    node->kind = NODE_CHAR;
    node->u.charNode.c = token->c;
    return 0;
}

int parseRegexp(Node* node, char* str)
{
    int r;
    char** s = &str;
    Token token;

    r = fetchToken(&token, s);
    if (r < 0) {
        return r;
    }

    r = parseSubexpr(s, node, &token);
    if (r < 0) {
        return r;
    }

    return 0;
}
