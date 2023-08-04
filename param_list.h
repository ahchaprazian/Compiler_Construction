
#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include <stdio.h>
#include "type.h"
#include "symbol.h"
#include "expr.h"

struct expr;

struct param_list {
	char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};

struct param_list* param_list_create( char *name, struct type *type, struct param_list *next ); // done
void param_list_print( struct param_list *a );												  	// done
struct param_list* param_list_copy( struct param_list *a ); 									// done
void param_list_delete( struct param_list *a );													// done
void param_list_resolve( struct param_list *a );												// done
bool param_list_equals( struct param_list *a, struct param_list *b );
bool param_list_fcall_compare(struct expr* e, struct param_list* a);

#endif
