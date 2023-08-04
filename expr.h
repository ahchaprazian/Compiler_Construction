#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "type.h"

typedef enum {
	EXPR_ADD,
	EXPR_MINUS,
	EXPR_MULT,
	EXPR_DIV,
    EXPR_NEGATION,
	EXPR_EXPONENT,
	EXPR_MOD,
	EXPR_INCREMENT,
	EXPR_DECREMENT,
	EXPR_GT,
	EXPR_GEQ,
	EXPR_LT,
	EXPR_LEQ,
	EXPR_EQUAL,
	EXPR_NOTEQ,
	EXPR_NOT,
	EXPR_AND,
	EXPR_OR,
	EXPR_IDENT,
    EXPR_LIT_INT,
    EXPR_LIT_CHAR,
    EXPR_LIT_STR,
    EXPR_LIT_BOOL,
    EXPR_BRACKETS,
    EXPR_PARENS,
    EXPR_CURLY,
    EXPR_ARRAY_INDEX,
    EXPR_FUNC_CALL,
    EXPR_ARGS,
    EXPR_ASSIGN,
	EXPR_GROUPING,
	EXPR_ARRAY_TYPE,
	/* many more kinds of exprs to add here */
} expr_t;

struct expr {
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by various leaf exprs */
	const char *name;
	int literal_value;
	const char * string_literal;
	struct symbol *symbol;
	struct type *array_type;
};
void print_n_tabs(int n);

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_char_literal( unsigned char c );
struct expr * expr_create_string_literal( const char *str );

void expr_resolve( struct expr *e );
struct type * expr_typecheck( struct expr *e );

void expr_print( struct expr *e, int level );
struct expr *expr_create_array_type(struct type *array_type);


#endif
