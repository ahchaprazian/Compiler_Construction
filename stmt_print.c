#include <stdio.h>

void print_n_tabs(int n) {
    for (int i = 0 ; i < n ; ++i)
        printf("\t");
}

void stmt_print(struct stmt *s, int level) {
    if (s == NULL)
        return;

    print_n_tabs(level);
    switch (s->kind) {
    case STMT_DECL:
        decl_print(s->decl, level);
        break;
	case STMT_EXPR:
        expr_print(s->expr, level);
        break;
	case STMT_IF_ELSE:
        printf("if (");
        expr_print(s->expr, level);
        printf(") {\n");
        stmt_print(s->body, level++);
        printf("}");
        if(s->else_body != NULL) {
            printf("\nelse {\n");
            stmt_print(s->else_body, level++);
            printf("}");
        }
        break;
	case STMT_FOR:
        printf("for (");
        expr_print(s->init_expr, 0);
        printf(" ; ");
        expr_print(s->expr, 0);
        printf(" ; ");
        expr_print(s->next_expr, 0);
        printf(" ) {\n");
        stmt_print(s->body, level++);
        printf("}");
        break;
	case STMT_PRINT:
        printf("print ");
        expr_print(s->expr, 0);
        printf(";");
        break;
	case STMT_RETURN:
        printf("return ");
        expr_print(s->expr, 0);
        printf(";");
        break;
	case STMT_BLOCK:
        printf("{\n");
        stmt_print(s->body, level++);
        printf("}");
        break;
    default:
        printf("Error! Invalid statement kind\n");
        return;
    }
    printf("\n");
    stmt_print(s->next, level);
}
