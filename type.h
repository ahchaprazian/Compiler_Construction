#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>
#include "param_list.h"

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_FUNCTION_PROTO,
	TYPE_AUTO
} type_t;

struct type {
	type_t kind;
	struct param_list *params;
	struct type *subtype;
	int arr_size;
};

struct type *   type_create( type_t kind, struct type *subtype, struct param_list *params, int arr_size ); // done
void          	type_print( struct type *t );												 // done
bool    		type_equals( struct type *a, struct type *b );  							 // done
struct type * 	type_copy( struct type *t );												 // done
void 			type_delete( struct type *t );												 // done
bool 			type_is_atomic(type_t kind);												 // done


#endif
