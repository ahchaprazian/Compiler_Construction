#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr.h"

void print_n_tabs(int n) {
    for (int i = 0 ; i < n ; ++i)
        printf("    ");
}

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ) {
    struct expr* exp = malloc(sizeof(struct expr));

    exp->kind = kind;
    exp->left = left;
    exp->right = right;

    return exp;
}

struct expr * expr_create_name( const char *n ) {
    struct expr *e = expr_create(EXPR_IDENT, 0, 0);
    e->name = n;
    return e;
}
struct expr * expr_create_integer_literal( int c ) {
    struct expr *e = expr_create(EXPR_LIT_INT, 0, 0);
    e->literal_value = c;
    return e;
}
struct expr * expr_create_boolean_literal( int c ) {
    struct expr *e = expr_create(EXPR_LIT_BOOL, 0, 0);
    e->literal_value = c;
    return e;
}

struct expr * expr_create_char_literal( unsigned char c ) {
    struct expr *e = expr_create(EXPR_LIT_CHAR, 0, 0);
    //printf("line 34 %c\n", c);
    e->literal_value = (unsigned char)c;
    return e;
}

struct expr * expr_create_string_literal( const char *str ) {
    struct expr *e = expr_create(EXPR_LIT_STR, 0, 0);
    e->string_literal = str;
    return e;
}

struct expr *expr_create_array_type(struct type *array_type) {
    struct expr *e = malloc(sizeof(*e));
    e->array_type = array_type;
    return e;
}

void expr_print(struct expr *e, int level) {
    if(!e) return;
    switch(e->kind) {
        case EXPR_ADD:
            expr_print(e->left, level);
            printf(" + ");
            expr_print(e->right, level);
            break;
        case EXPR_MINUS:
            expr_print(e->left, level);
            printf(" - ");
            expr_print(e->right, level);
            break;
        case EXPR_MULT:
            expr_print(e->left, level);
            printf(" * ");
            expr_print(e->right, level);
            break;
        case EXPR_DIV:
            expr_print(e->left, level);
            printf(" / ");
            expr_print(e->right, level);
            break;
        case EXPR_NEGATION:
            printf("-");
            expr_print(e->left, level);
            break;
        case EXPR_EXPONENT:
            expr_print(e->left, level);
            printf("^");
            expr_print(e->right, level);
            break;
        case EXPR_MOD:
            expr_print(e->left, level);
            printf(" %% ");
            expr_print(e->right, level);
            break;
        case EXPR_INCREMENT:
            expr_print(e->left, level);
            printf("++");
            break;
        case EXPR_DECREMENT:
            expr_print(e->left, level);
            printf("--");
            break;
        case EXPR_GT:
            expr_print(e->left, level);
            printf(" > ");
            expr_print(e->right, level);
            break;
        case EXPR_GEQ:
            expr_print(e->left, level);
            printf(" >= ");
            expr_print(e->right, level);
            break;
        case EXPR_LT:
            expr_print(e->left, level);
            printf(" < ");
            expr_print(e->right, level);
            break;
        case EXPR_LEQ:
            expr_print(e->left, level);
            printf(" <= ");
            expr_print(e->right, level);
            break;
        case EXPR_EQUAL:
            expr_print(e->left, level);
            printf(" == ");
            expr_print(e->right, level);
            break;
        case EXPR_NOTEQ:
            expr_print(e->left, level);
            printf(" != ");
            expr_print(e->right, level);
            break;
        case EXPR_NOT:
            printf("!");
            expr_print(e->left, level);
            break;
        case EXPR_AND:
            expr_print(e->left, level);
            printf(" && ");
            expr_print(e->right, level);
            break;
        case EXPR_OR:
            expr_print(e->left, level);
            printf(" || ");
            expr_print(e->right, level);
            break;
        case EXPR_IDENT:
            printf("%s", e->name);
            break;
        case EXPR_LIT_INT:
            printf("%d", e->literal_value);
            break;
        case EXPR_LIT_CHAR:
            putchar('\'');
            printf("%c", e->literal_value);
            putchar('\'');
            break;
        case EXPR_LIT_STR:
            for(int i=0; i<strlen(e->string_literal); i++){
                if(e->string_literal[i]==10){
                    printf("\\n");
                }
                else if(e->string_literal[i] == 0) {
                    printf("\\0");
                }

                else {
                    printf("%c", e->string_literal[i]);
                }
            }
            break;
        case EXPR_LIT_BOOL:
            if (e->literal_value == 0) printf("false");
            else printf("true");
            break;
        case EXPR_PARENS:
            printf("(");
            if (e->left != NULL){
                expr_print(e->left, level);
            }
            printf(")");
            break;
        case EXPR_CURLY:
            printf("{");
            if(e->left != NULL){
                expr_print(e->left, level);
            }
            printf("}");
            break;
        case EXPR_BRACKETS:
            expr_print(e->left, level);
            printf("]");
            if(e->right != NULL) {
                printf("[");
                expr_print(e->right, 0);
            }
            break;
        case EXPR_ARRAY_INDEX:
            expr_print(e->left, level);
            printf("[");
            expr_print(e->right, level);
            printf("]");
            break;
        case EXPR_FUNC_CALL:
            expr_print(e->left, level);
            printf("(");
            if(e->right != NULL) {
                expr_print(e->right, level);
            }
            printf(")");
            break;
        case EXPR_ARGS:
            expr_print(e->left, level);
            if(e->right != NULL) {
                printf(", ");
                expr_print(e->right, level);
            }
            break;
        case EXPR_ASSIGN:
            expr_print(e->left, level);
            printf(" = ");
            expr_print(e->right, level);
            break;
        case EXPR_GROUPING:
            printf("(");
            expr_print(e->left, level);
            if(e->right != NULL)
                expr_print(e->right, level);
            printf(")");
            break;
        default:
            printf("Error: Invalid Expression");
            return;
    }
}




void expr_resolve( struct expr *e )
{
    if(!e) return;
    if( e->kind == EXPR_IDENT ) {
        ///printf("before scope lookup\n");

        e->symbol = scope_lookup(e->name);
        //printf("after scope lookup\n");
        if(e->symbol == NULL) {
            printf("EXPR RESOLVE MADE ME EXPLODE\n");
        }
    } else {
        //printf("entered else clause");
        expr_resolve( e->left );
        expr_resolve( e->right );
    }
}



// TODO
struct type * expr_typecheck( struct expr *e )
{
    if(!e) return 0;

    struct type *lt = expr_typecheck(e->left);
    struct type *rt = expr_typecheck(e->right);
    struct type *result;

    switch(e->kind) {
        case EXPR_LIT_INT:
            result = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case EXPR_LIT_STR:
            result = type_create(TYPE_STRING, 0, 0, 0);
            break;
        case EXPR_LIT_CHAR:
            result = type_create(TYPE_CHARACTER, 0, 0, 0);
            break;
        case EXPR_LIT_BOOL:
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_ADD:
            if(lt->kind != TYPE_INTEGER) {
                printf("TYPE CHECKING ERROR: cannot increment ");
                type_print(lt);
                if(e->left->name != NULL) {
                    printf(" %s\n", e->left->name);
                } else {
                    printf(" (");
                    expr_print(e->left, 0);
                    printf(") \n");
                }
            }
            result = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case EXPR_MINUS:
            if(lt->kind != TYPE_INTEGER) {
                printf("TYPE CHECKING ERROR: cannot decrement ");
                type_print(lt);
                if(e->left->name != NULL) {
                    printf(" %s\n", e->left->name);
                } else {
                    printf(" (");
                    expr_print(e->left, 0);
                    printf(") \n");
                }
            }
            result = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case EXPR_DIV:
        case EXPR_MULT:
        case EXPR_MOD:
        case EXPR_EXPONENT:
            if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
                fprintf(stderr, "Number was not passed into ADD. Cannot do between ");
                type_print(lt);
                fprintf(stderr, " and ");
                expr_print(e->right, 0);
                fprintf(stderr, "\n");
    
            }
            result = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case EXPR_INCREMENT:
        case EXPR_DECREMENT:
            if(lt->kind != TYPE_INTEGER) {
                fprintf(stderr, "Type error: cannot inc/dec ");
                type_print(lt);
                fprintf(stderr, "\n");
            }
            result = type_create(TYPE_INTEGER, 0, 0, 0);
        case EXPR_EQUAL:
        case EXPR_NOTEQ:
            if(!type_equals(lt,rt)) {
                fprintf(stderr, "Type error: Left and right are not equal");
            }
            if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
                fprintf(stderr, "Type error: Void, array or function was given.\n");
            }
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_GT:
        case EXPR_GEQ:
        case EXPR_LT:
        case EXPR_LEQ:
            if(lt->kind != TYPE_BOOLEAN && rt->kind != TYPE_BOOLEAN) {
                fprintf(stderr, "Type error: Left and right are not valid bools: ");
                expr_print(e->left, 0);
                fprintf(stderr, " and ");
                expr_print(e->right, 0);
            }
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_NOT:
            if(lt->kind != TYPE_BOOLEAN) {
                fprintf(stderr, "Type error: Value from not is not valid.");
                expr_print(e->left, 0);
            }
            break;
        case EXPR_AND:
        case EXPR_OR:
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_IDENT:
            result = type_copy(e->symbol->type);
            break;
        case EXPR_BRACKETS:
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_CURLY:
            result = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case EXPR_ARRAY_INDEX:
            break;
        case EXPR_FUNC_CALL:
            if(lt->kind == TYPE_FUNCTION) {
                if(lt->params == NULL) {
                    result = type_copy(lt->subtype);
                    break;
                }
                // kinda sus
                if(param_list_fcall_compare(lt->params, e->right) == false) {
                    fprintf(stderr, "Type error: Failed to call param_list_fcall_compare");
                }
                result = type_copy(lt->subtype);
            } else {
                fprintf(stderr, "Invalid function call to non-function.");
                result = type_copy(lt);
            }

            type_delete(lt);
            type_delete(rt);
            break;
        case EXPR_ARGS:
            result = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case EXPR_ASSIGN:
            if(lt) {
                if(type_equals(lt, rt) == false) {
                    fprintf(stderr, "Type error: Assigning variable with a different type.");
                }
                result = type_copy(lt);
            }
            break;
        case EXPR_GROUPING:
            result = type_copy(lt);
            break;
        case EXPR_ARRAY_TYPE:
            break;
    }
    type_delete(lt);
    type_delete(rt);
    return result;
}
