// Use hash table
#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "stack.h"
#include "hash_table.h"


struct symbol * symbol_create( symbol_t kind, struct type *type, char *name ) {
    struct symbol* sym = malloc(sizeof(struct symbol));

    sym->kind = kind;
    sym->type = type;
    sym->name = name;
    sym->which = 0;

    return sym;
}

struct stack *stackTop;

//stack *hash_stack = stack_create();
// scope enter() causes a new hash table to be pushed on the top of the stack, representing a new scope
void scope_enter() {
    struct stack *newStack = stack_create();
    newStack->table = hash_table_create(0, 0);
    //stack_push(newStack, (void *)new_hash_table);
    newStack->next = stackTop;
    stackTop = newStack;
    return;
}

// scope exit() causes the topmost hash table to be removed.
void scope_exit() {
    //struct hash_table *topmost = (struct hash_table*)stack_item(stack_size(stackTop) - 1);
    struct stack* delete = stackTop;
    if(stackTop == NULL)
        return;
    if(stackTop->next != NULL) {
        stackTop = stackTop->next;
    } else {
        stackTop = NULL;
    }
    hash_table_delete(delete->table);
    //stack_delete(&delete);
    free(delete);

    //stack_pop(stackTop);
    
}

// scope level() returns the number of hash tables in the current stack.
// (This is helpful to know whether we are at the global scope or not.)
int scope_level() {
    return stack_size(stackTop);
}

// scope bind(name,sym) adds an entry to the topmost hash table of the stack,
// mapping name to the symbol structure sym.
void scope_bind(const char* name, struct symbol* sym) {
    if(stackTop == NULL) {
        return;
    }
    printf("in scope bind %s", name);
    hash_table_insert(stackTop->table, name, sym);
}

// scope lookup(name) searches the stack of hash tables from top to bottom,
// looking for the first entry that matches name exactly. If no match is found, it returns null.
struct symbol *scope_lookup(const char *name) {
    //int i = 0;
    //struct hash_table *current = (struct hash_table *)stack_item(stack_size(hash_stack) - 1);
    struct stack *current = stackTop;
    struct symbol *found;
    while (current != NULL) {
        ///printf("beginning of while\n");
        printf("in scope lookup %s, %ld\n", name, stack_size(current));
        //if(current->table == NULL) printf("table is null");
        //else printf("table isnt null\n");
        found = (struct symbol*)hash_table_lookup(current->table, name);
        //printf("after hash table lookup\n");
        if (found != NULL)
            return found;
        else printf("found is null\n");
        //i--;
        //current = (struct hash_table *)stack_item(stack_size(hash_stack) - 1 - i);
        current = current->next;
    }
    return NULL;
}

//scope lookup current(name) works like scope lookup except that it only searches the topmost table.
// This is used to determine whether a symbol has already been defined in the current scope.
struct symbol *scope_lookup_current(const char *name) {
    if(stackTop == NULL) {
        return NULL;
    }
    //struct hash_table* topmost = (struct hash_table *)stack_item(stack_size(hash_stack) - 1);
    return (struct symbol *)hash_table_lookup(stackTop->table, name);
}
