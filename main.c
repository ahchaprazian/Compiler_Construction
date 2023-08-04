/*
Main program of calculator example.
Validate whether the input matches the grammar.
*/

#include <stdio.h>
#include "decl.h"

/* Clunky: Declare the parse function generated from parser.bison */
extern int yyparse();
extern FILE *yyin;
extern struct decl *parser_result; 
extern void decl_print(struct decl*, int);

#ifdef YYDEBUG
	yydebug = 1;
#endif

int main( int argc, char *argv[] )
{
    yyin = fopen(argv[1], "r'");
    if(!yyin) {
        printf("Could open the file!\n");
        return 0;
    }

	if(yyparse()==0) {
		printf("Parse successful!\n");
		decl_print(parser_result, 0);
		decl_resolve(parser_result);
		return 0;
	} else {
		printf("Parse failed.\n");
		return 1;
	}
}
