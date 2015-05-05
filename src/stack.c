#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"

#define T   Stack_T
#define isBadPtr(ptr) ((NULL == ptr) || (0xc0000000 <= ptr))

struct T {
    unsigned int magic;     /*verify the stack is valid or not*/
    int count;
    struct elem {
        void *x;
        struct elem *link;
    } *head;
};

T Stack_new(void)
{
    T stk;

    NEW(stk);
    stk->magic = 0x1a2b3c4d;
    stk->count = 0;
    stk->head = NULL;
    return stk;
}

int Stack_empty(T stk)
{
    assert(stk && stk->magic == 0x1a2b3c4d);
    return stk->count == 0;
}

void Stack_push(T stk, void *x)
{
    struct elem *t;

    assert(stk && stk->magic == 0x1a2b3c4d);
    NEW(t);
    t->x = x;
    t->link = stk->head;
    stk->head = t;
    stk->count++;
}

void *Stack_pop(T stk)
{
    void *x;
    struct elem *t;

    assert(stk && stk->magic == 0x1a2b3c4d);
    assert(stk->count > 0);
    t = stk->head;
    stk->head = t->link;
    stk->count--;
    FREE(t);
    return x;
}

void Stack_free(T *stk)
{
    struct elem *t, *u;

    assert(stk && *stk && stk->magic == 0x1a2b3c4d);
    for (t = (*stk)->head; t; t = u) {
        u = t->link;
        FREE(t);
    }
    FREE(*stk);
}

/*other interfaces to do*/
