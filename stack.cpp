#include "stack.h"
#include <climits>

Stack* stack_create(const string& name) {
    Stack* s = new Stack;
    s->name = name;
    s->top = nullptr;
    return s;
}

void stack_push(Stack* s, int v) {
    SNode* n = new SNode;
    n->value = v;
    n->next = s->top;
    s->top = n;
}

int stack_pop(Stack* s) {
    if (!s->top) {
        return INT_MIN;
    }
    SNode* n = s->top;
    int v = n->value;
    s->top = n->next;
    delete n;
    return v;
}

int stack_peek(Stack* s) {
    if (!s->top) {
        return INT_MIN;
    }
    return s->top->value;
}

bool stack_empty(Stack* s) {
    return s->top == nullptr;
}

void stack_free(Stack* s) {
    while (s->top) {
        SNode* n = s->top;
        s->top = n->next;
        delete n;
    }
    delete s;
}

