#include <stdio.h>
#include <stdlib.h>
#include "param_list.h"

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ) {
    struct param_list* params = malloc(sizeof(struct param_list));
    if(params == NULL) {
        printf("Failed to allocate memory for param list.\n");
        return NULL;
    }

    params->name = name;
    params->type = type;
    params->next = next;

    return params;
}

void param_list_print( struct param_list *a ) {
    // Maybe do NULL check for a??
    printf("%s: ", a->name);
    type_print(a->type);
    if(a->next != NULL) {
        printf(", ");
        param_list_print(a->next);
    }
}

struct param_list * param_list_copy( struct param_list *a ) {
    struct param_list* params_copy;

    params_copy->name = a->name;
    params_copy->type = type_copy(a->type);
    params_copy->next = param_list_copy(a->next);

    return params_copy;
}

void param_list_delete( struct param_list *a ) {
    if(a == NULL) { return; }

    param_list_delete(a->next);
    type_delete(a->type);

    if(a->name != NULL) { free(a->name); }
    free(a);
}

bool param_list_equals( struct param_list *a, struct param_list *b) {
    if(a == NULL || b == NULL) return false;
    struct param_list *a_temp = a;
    struct param_list *b_temp = b;

    while(a_temp != NULL && b_temp != NULL) {
        if(!type_equals(a_temp->type, b_temp->type))
            return false;
        a_temp = a_temp->next;
        b_temp = b_temp->next;
    }

    return true;
}

void param_list_resolve( struct param_list *a ) {
    if(a == NULL) {
        return;
    }

    if(scope_lookup_current(a->name) != NULL) {
        printf("%s Declared in scope", a->name);
    } else {
        a->symbol = symbol_create(SYMBOL_PARAM, type_copy(a->type), a->name);
        scope_bind(a->name, a->symbol);

    }

    param_list_resolve(a->next);
}

bool param_list_fcall_compare(struct expr* e, struct param_list* a) {
    if (e == NULL || a == NULL) {
        return false;
    }

    if(e == NULL && a == NULL) {
        return true;
    }

    if(e->left != NULL && e->right->kind == EXPR_ARGS) {
        if(type_equals(expr_typecheck(e->left), a->type)) {
            return param_list_fcall_compare(e->right, a->next);
        } else {
            return false;
        }
    } else if(e->left != NULL && e->right->kind != EXPR_ARGS) {
        if(type_equals(expr_typecheck(e->left), a->type)) {
            if(a->next != NULL && type_equals(expr_typecheck(e->right), a->next->type)) {
                return param_list_fcall_compare(NULL, a->next->next);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    return false;
}