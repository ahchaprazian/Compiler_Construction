#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "type.h"
#include "param_list.h"
#include "symbol.h"
#include "hash_table.h"

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params, int arr_size ) {
    struct type* typ = malloc(sizeof(struct type));

    typ->kind = kind;
    typ->params = params;
    typ->subtype = subtype;
    typ->arr_size = arr_size;

    return typ;
}

void type_print( struct type *t ) {
    switch(t->kind) {
        case TYPE_ARRAY:
            if(t->arr_size)
              printf("array[%d] ", t->arr_size);
            else
              printf("array[] ");
            type_print(t->subtype);
            break;
        case TYPE_INTEGER:
            printf("integer");
            break;
        case TYPE_STRING:
            printf("string");
            break;
        case TYPE_CHARACTER:
            printf("char");
            break;
        case TYPE_BOOLEAN:
            printf("boolean");
            break;
        case TYPE_VOID:
            printf("void");
            break;
        case TYPE_AUTO:
            printf("auto");
            break;
        case TYPE_FUNCTION:
            printf("function ");
            type_print(t->subtype);
            printf("(");
            if(t->params != NULL) {
                param_list_print(t->params);
            }
            printf(") = ");
            break;
        case TYPE_FUNCTION_PROTO:
            printf("function ");
            type_print(t->subtype);
            printf("(");
            if(t->params != NULL) {
              param_list_print(t->params);
            }
            printf(")");
            break;
        default:
            printf("Error! Invalid TYPE kind\n");
            return;
    }
}

bool type_is_atomic(type_t kind) {
  return (kind != TYPE_FUNCTION) && (kind != TYPE_ARRAY);
}


bool type_equals( struct type *a, struct type *b ){
  if( a->kind == b->kind ) {
    if ((TYPE_ARRAY == a->kind) && (TYPE_ARRAY == b-> kind)) {
        return type_equals(a->subtype, b->subtype);
    } else if ( a->kind == TYPE_FUNCTION && b->kind == TYPE_FUNCTION) {
        // return true if both subtype and params are recursively equal
        return type_equals(a->subtype, b->subtype) &&
            param_list_equals(a->params, b->params);
    } else return true;
  } else return false;
}

struct type * type_copy( struct type *t )
{
  // Return a duplicate copy of t, making sure
  // to duplicate subtype and params recursively.
  struct type* copy;

  copy->kind = t->kind;
  //copy->params = t->params; // shallow copy
  copy->params = param_list_copy(t->params); // deep copy
  //copy->subtype = t->subtype; // shallow copy
  copy->subtype = type_copy(t->subtype); // deep copy

  return copy;
}

void type_delete( struct type *t )
{
  // if type is null then return
  if(t == NULL) { return; }

  // recursive delete
  type_delete(t->subtype);

  // need to delete the params list too
  // pretend the functions exists
  param_list_delete(t->params);

  // frees the current node its on
  free(t);
}