// TO DO
// CHECK IF EXPR_PRINT WORKS WITH LOGIC

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "expr.h"
//#include "symbol.h"
#include "decl.h"
#include "stmt.h"

struct decl * decl_create( char *name, struct type *type, struct expr *value, struct stmt *code, struct decl *next ) {
    struct decl* dec = malloc(sizeof(struct decl));

    dec->name = name;
    dec->type = type;
    dec->value = value;
    dec->code = code;
    //dec->symbol = NULL; // consider symbol_create, also symbol is not in the compiler book
    dec->next = next;
    return dec;
}

void decl_print( struct decl *d, int level ) {

    if (!d) return; // check if null

    printf("%s: ", d->name);
    type_print(d->type);

    if (d->value){
        printf(" = ");
        if(d->value->kind == EXPR_ARGS) {
            printf("{ ");
            expr_print(d->value, level);
            printf(" }");
        } else {
            expr_print(d->value, level);
        }
        printf(";\n");
    } else if (d->code){
        printf("{\n");
        stmt_print(d->code, level + 1);
        printf("}\n");
    } else {
        printf(";\n");
    }
    if(d->next != NULL) {
        decl_print(d->next, level);
    }
}


void decl_resolve( struct decl *d )
{
    if(!d) return;
    printf("%s\n", d->name);
    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    d->symbol = symbol_create(kind, d->type, d->name);
    ///printf("before expr resolve\n");

    expr_resolve(d->value);
    //printf("after expr resolve\n");
    printf("decl resolve %s\n", d->name);
    scope_bind(d->name,d->symbol);
    if(d->type->kind != TYPE_FUNCTION || d->type->kind != TYPE_FUNCTION_PROTO) {
        if(d->code) {
            scope_enter();
            param_list_resolve(d->type->params);
            ///printf("after param list resolve\n");
            stmt_resolve(d->code);
            //printf("after stmt resolve\n");
            scope_exit();
        }
    } else if(d->type->kind == TYPE_FUNCTION || d->type->kind == TYPE_FUNCTION_PROTO) {
            struct symbol* sym = scope_lookup_current(d->name);
            if (sym == NULL) { return; }
            ///printf("in if #2\n");
            switch(sym->type->kind) {
                case TYPE_FUNCTION_PROTO:
                    //printf("function proto switch case\n");
                    if(param_list_equals(d->type->params, sym->type->params)) {
                        d->symbol->type->kind = TYPE_FUNCTION;
                        scope_bind(d->name, d->symbol);
                    }
                    break;
                case TYPE_FUNCTION:
                    ///printf("function switch case\n");
                    scope_bind(d->name, d->symbol);
                    break;
                default:
                    printf("DECL RESOLVE ERROR\n");
                    break;
            }
    }

    decl_resolve(d->next);
}

void decl_typecheck( struct decl *d )
{
    if(d->value) { // if exists
        struct type *t; // cast struct temp
        t = expr_typecheck(d->value);
        if(!type_equals(t,d->symbol->type)) {
            // display an error  if incorrect type
            fprintf(stderr, "Type error: %s declared with incorrect type\n", d->name);
            type_print(d->symbol->type); // incorrect type proof
            fprintf(stderr, " but called with ");
            type_print(t); // show temp
            fprintf(stderr, "\n");
        }
    }

    if(d->code) {
        stmt_typecheck(d->code);
    }
}
