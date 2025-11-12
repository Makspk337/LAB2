#ifndef STACK_H
#define STACK_H
#include <string>

using namespace std;

struct SNode {
    int value;
    SNode* next;
};

struct Stack {
    string name;
    SNode* top;
};

Stack* stack_create(const string& name);
void stack_push(Stack* s, int v);
int stack_pop(Stack* s);
int stack_peek(Stack* s);
bool stack_empty(Stack* s);
void stack_free(Stack* s);

#endif
