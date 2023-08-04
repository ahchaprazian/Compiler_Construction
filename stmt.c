#include <stdio.h>
#include <stdlib.h>
#include "stmt.h"
#include "type.h"
#include "expr.h"

struct stmt* stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next ) {
    struct stmt* st = malloc(sizeof(struct stmt));

    st->kind = kind;
    st->decl = decl;
    st->init_expr = init_expr;
    st->expr = expr;
    st->next_expr = next_expr;
    st->body = body;
    st->else_body = else_body;
    st->next = next;

    return st;
}

void stmt_print( struct stmt *s, int level ){
   if (s == NULL)
        return;

    if(s->kind != STMT_BLOCK) {
        print_n_tabs(level);
    }

    switch (s->kind) {
    case STMT_DECL:
        decl_print(s->decl, level);
        break;
	case STMT_EXPR:
        expr_print(s->expr, level);
        printf(";");
        break;
    case STMT_IF:
        printf("if (");
        expr_print(s->expr, level);
        printf(") ");
        stmt_print(s->body, level);
        break;
	case STMT_IF_ELSE:
        printf("if (");
        expr_print(s->expr, level);
        printf(") ");
        stmt_print(s->body, 0);
        if(s->else_body != NULL) {
            print_n_tabs(level);
            printf("else ");
            stmt_print(s->else_body, level);
        }
        break;
	case STMT_FOR:
        printf("for (");
        expr_print(s->init_expr, 0);
        printf(" ; ");
        expr_print(s->expr, 0);
        printf(" ; ");
        expr_print(s->next_expr, 0);
        printf(" )");
        //print_n_tabs(level++);
        stmt_print(s->body, level);
        //print_n_tabs(level++);
        
        break;
	case STMT_PRINT:
        printf("print ");
        expr_print(s->expr, level);
        printf(";");
        break;
	case STMT_RETURN:
        printf("return ");
        expr_print(s->expr, level);
        printf(";");
        break;
	case STMT_BLOCK:
        printf(" {\n");
        stmt_print(s->body, level + 1);
        print_n_tabs(level);
        printf("}");
        break;
    default:
        printf("Error! Invalid statement kind\n");
        return;
    }
    printf("\n");
    if(s->next != NULL)
        stmt_print(s->next, level++);
}


void stmt_typecheck( struct stmt *s )
{
    struct type *t;
    struct type *t2;
    switch(s->kind) {
        case STMT_EXPR:
            t = expr_typecheck(s->expr);
            type_delete(t);
            break;
        case STMT_IF_ELSE:
            t = expr_typecheck(s->expr);
            if(t->kind!=TYPE_BOOLEAN) {
            // display an error 
            }
            type_delete(t);
            stmt_typecheck(s->body);
            stmt_typecheck(s->else_body);
            break;
        case STMT_IF:
            t = expr_typecheck(s->expr);
            if(t->kind != TYPE_BOOLEAN) {
                printf("Expression in if statement is invalid.\n");
                return;
            }
            type_delete(t);
            stmt_typecheck(s->body);
            break;
        case STMT_DECL:
            decl_typecheck(s->decl);
            break;
        case STMT_FOR:
            t = expr_typecheck(s->expr);
            if(t->kind != TYPE_BOOLEAN) {
                printf("Expression in for loop is invalid.\n");
                return;
            }
            type_delete(t);
            expr_typecheck(s->init_expr);
            if(s->expr) {
                t2 = expr_typecheck(s->expr);
                if(t2->kind != TYPE_BOOLEAN) {
                    printf("Expression in middle of the for loop is not boolean.\n");
                }
            }
            struct type *t3 = expr_typecheck(s->next_expr);
            stmt_typecheck(s->body);
            type_delete(t);
            type_delete(t2);
            type_delete(t3);
            break;
        case STMT_WHILE:
            t = expr_typecheck(s->expr);
            if(t->kind != TYPE_BOOLEAN){
                printf("Expression in while statement is invalid.\n");
                return;
            }
            type_delete(t);
            t2 = expr_typecheck(s->expr);
            stmt_typecheck(s->body);
            type_delete(t2);
            break;
        case STMT_PRINT:
            t = expr_typecheck(s->expr);
            if(t->kind == TYPE_VOID) {
                printf("Cannot print type void.\n");
            }
            type_delete(t);
            // maybe
            if(s->expr->right) {
                t= expr_typecheck(s->expr->right);
            }
            break;
        case STMT_RETURN:
            t = expr_typecheck(s->expr);         
            if(t->kind == TYPE_VOID) {
                printf("Cannot return type void.\n");
            }
            type_delete(t);
            break;
        case STMT_BLOCK:
            stmt_typecheck(s->body);
            break;
        }
}

void stmt_resolve( struct stmt *s ) {
    if (s == NULL)
        return;

    printf("%d\n", s->kind);
    switch(s->kind) {
        case STMT_DECL:
            printf("case1\n");
            decl_resolve(s->decl);
            break;
        case STMT_EXPR:
            printf("case2\n");
            expr_resolve(s->expr);
            break;
        case STMT_IF:
            printf("case3\n");
            expr_resolve(s->expr);
            stmt_resolve(s->body);
            break;
        case STMT_IF_ELSE:
            printf("case4\n");
            expr_resolve(s->expr);
            stmt_resolve(s->body);
            stmt_resolve(s->else_body);
            break;
        case STMT_FOR:
            printf("case5\n");
            expr_resolve(s->init_expr);
            expr_resolve(s->expr);
            expr_resolve(s->next_expr);
            stmt_resolve(s->body);
            break;
        case STMT_PRINT:
            printf("case6\n");
            expr_resolve(s->expr);
            break;
        case STMT_RETURN:
            printf("case7\n");
            expr_resolve(s->expr);
            break;
        case STMT_BLOCK:
            printf("case8\n");
            scope_enter();
            stmt_resolve(s->body);
            scope_exit();
            break;
        default:
            printf("ERROR: Invalid stmt kind in stmt_resolve()");
            break;
    }
    if(s->next != NULL) {
        stmt_resolve(s->next);
        //printf("if statement\n");
    }
}