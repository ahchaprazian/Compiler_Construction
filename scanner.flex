%{
#include "token.h"
#include <stdio.h>

%}

%option yylineno
%x c_comment

DIGIT   [0-9]
LETTERS [a-zA-Z]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%
(" "|\t|\n|\r)     /* skip whitespace */

    /************ Key Words and data types ************/
while          { return TOKEN_WHILE; }
if             { return TOKEN_IF; }
else           { return TOKEN_ELSE; }
for            { return TOKEN_FOR; }
char           { return TOKEN_CHAR; }
integer        { return TOKEN_INTEGER; }
string         { return TOKEN_STRING; }
array          { return TOKEN_ARRAY; }
boolean        { return TOKEN_BOOLEAN; }
false          { return TOKEN_FALSE; }
true           { return TOKEN_TRUE; }
auto           { return TOKEN_AUTO; }
function       { return TOKEN_FUNCTION; }
void           { return TOKEN_VOID; }
print          { return TOKEN_PRINT; }
return         { return TOKEN_RETURN; }
\{             { return TOKEN_LCURLY; }
\}             { return TOKEN_RCURLY; }
;              { return TOKEN_SEMICOLON; }
:              { return TOKEN_COLON; }
,              { return TOKEN_COMMA; }

    /************ Parenthesis and Brackets ************/
\(             { return TOKEN_LPAREN; }
\)             { return TOKEN_RPAREN; }
\[             { return TOKEN_LBRACKET; }
\]             { return TOKEN_RBRACKET; }

    /************ Operators ************/
\+\+           { return TOKEN_INCREMENT; }
\+             { return TOKEN_PLUS; }
--             { return TOKEN_DECREMENT; }
-              { return TOKEN_MINUS; }
!              { return TOKEN_NOT; }
\^             { return TOKEN_EXPONENT; }
\*             { return TOKEN_MULT; }
\/             { return TOKEN_DIV; }
%              { return TOKEN_MOD; }

    /************ Conditionals ************/
\<             { return TOKEN_LT; }
\<=            { return TOKEN_LTE; }
\>             { return TOKEN_GT; }
\>=            { return TOKEN_GTE; }
==             { return TOKEN_EQUAL; }
!=             { return TOKEN_NOTEQ; }
&&             { return TOKEN_AND; }
\|\|           { return TOKEN_OR; }
=              { return TOKEN_ASSIGN; }

{DIGIT}+                        { return TOKEN_LIT_INT; }
{ID}                            { return TOKEN_IDENT; }
'([^'\\]|\\[^\\\n])'            { return TOKEN_LIT_CHAR; }
\"([^\"\\\n]|\\[^\\\n])*\"      { return TOKEN_LIT_STR;}

\/\/.*          //  Single line comments
                /* Multi-line C-style comments */
"/*"                  BEGIN(c_comment);
<c_comment>.|\n
<c_comment>\*+\/      BEGIN(INITIAL);

.               {
                    fprintf(stderr,
                        "scan error:\t%s is invalid token type, line %d\n",
                        yytext, yylineno);
                    return TOKEN_ERROR;
                }
%%
int yywrap() { return 1; }
/*
int main(int argc, char *argv[])
{
	yyin = fopen(argv[1],"r");
	if(!yyin) {
		printf("could not open program.c!\n");
		return 1;
	}

	while(1) {
		socklen_t t = yylex();
		if(t==TOKEN_EOF) break;
        if(t != TOKEN_ERROR)
        printf("Token %d \t%s at line number %d\n", t, yytext, yylineno);
	}
}
*/