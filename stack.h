#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include "hash_table.h"

//typedef struct stack stack;
struct stack {
    struct hash_table* table;
    struct stack* next;
}; 


struct stack* stack_create();
void stack_push(struct stack* stk, struct hash_table* item);
void* stack_pop(struct stack* stk);
size_t stack_size(struct stack* stk);
void* stack_item(struct stack* stk, size_t position);
void stack_delete(struct stack** stk);

#endif 