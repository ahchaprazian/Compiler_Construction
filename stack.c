#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "stack.h"

struct stack* stack_create() {
    struct stack *stk = (struct stack*)malloc(sizeof(struct stack));
    if(stk == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack.\n");
        return NULL;
    }
    stk->table = NULL;
    stk->next = NULL;

    return stk;
}

void stack_push(struct stack* stk, struct hash_table* item) {
    if(stk == NULL) {
        fprintf(stderr, "Stack does not exist.\n");
        return;
    }

    struct stack *ptr = (struct stack*)malloc(sizeof(struct stack*));

    if(stk->table == NULL) {
        ptr->table = item;
        ptr->next = NULL;
        stk = ptr;
    } else {
        ptr->table = item;
        ptr->next = stk;
        stk = ptr;
    }

    return;
}

void* stack_pop(struct stack* stk) {
    if(stk == NULL) {
        fprintf(stderr, "Stack does not exist");
        return NULL;
    }

    struct stack *temp = stk->next;
    hash_table_delete(stk->table);
    free(stk);
    stk = temp;
}

size_t stack_size(struct stack* stk){
    int size = 1;
    struct stack *temp = stk;
    if(stk == NULL)
        return 0;
    while(temp->next != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}

void* stack_item(struct stack* stk, size_t position){
    if(stk == NULL) return NULL;
    struct stack *temp = stk;
    int i = 0;
    while(temp->next != NULL && i == 0) {
        if(i == position) {
            return stk->table;
        } else {
            temp = temp->next;
            i++;
        }
    }

    printf("Cannot find item in given position %ld\n", position);
    return NULL;
}

void stack_delete(struct stack** stk) {
    struct stack* current = *stk;
    struct stack* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *stk = NULL;
}