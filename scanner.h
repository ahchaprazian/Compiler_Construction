#ifndef SCANNER_H
#define SCANNER_H

typedef enum {
  TOKEN_IDENT,
  TOKEN_NUMBER,
  TOKEN_ERROR,

  TOKEN_CHAR,
  TOKEN_INTEGER,
  TOKEN_STRING,
  TOKEN_ARRAY,
  TOKEN_AUTO,
  TOKEN_VOID,
  TOKEN_BOOLEAN,
  TOKEN_FALSE,
  TOKEN_TRUE,
  TOKEN_IF,
  TOKEN_FOR,
  TOKEN_PRINT,
  TOKEN_RETURN,
  TOKEN_FUNCTION,
  TOKEN_ELSE,
  TOKEN_WHILE,
  TOKEN_COLON,
  TOKEN_SEMICOLON,

  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_LBRACKET,
  TOKEN_RBRACKET,
  TOKEN_INCREMENT,
  TOKEN_DECREMENT,
  TOKEN_MINUS,
  TOKEN_NOT,
  TOKEN_EXPONENT,
  TOKEN_MULT,
  TOKEN_DIV,
  TOKEN_MOD,
  TOKEN_PLUS,
  TOKEN_LT,
  TOKEN_LTE,
  TOKEN_GT,
  TOKEN_GTE,
  TOKEN_EQUAL,
  TOKEN_NOTEQ,
  TOKEN_AND,
  TOKEN_OR,
  TOKEN_ASSIGN,
  TOKEN_FUNCCALL,
    
  TOKEN_EOF
} token_t;

token_t scan_token();
int     expect_token( token_t t );
void    putback_token( token_t t );
const char * token_string( token_t t );

#endif
