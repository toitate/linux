
#ifndef MY_STACK_H
#define MY_STACK_H

typedef struct Stack_tag* Stack;

Stack init(int size);

void my_delete(Stack stack);

void my_push(Stack stack, int value);

int my_pop(Stack stack);

int is_empty(Stack stack);

#endif


