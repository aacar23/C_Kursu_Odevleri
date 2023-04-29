#include <stdlib.h>
#include <stdio.h>

#define generate_func(name) void name (void){ printf(#name " is called\n");}

typedef void(*FPTR)(void);

generate_func(foo)

generate_func(bar)

generate_func(proc)

generate_func(method)

generate_func(past)

generate_func(gus)

generate_func(fun)

generate_func(solid)

generate_func(rust)

struct linked_list{
    struct linked_list *prev;
    struct linked_list *next;
    FPTR fptr;
};

static struct linked_list *start;
static struct linked_list *last;

int global_count = 0;

void append(struct linked_list **end, FPTR fp)
{
    struct linked_list *new = malloc(sizeof(struct linked_list));
    (*end) -> next = new;
    new -> next = NULL;
    new -> prev = *end;
    new -> fptr = fp;
    *end = new;
}



void free_the_linked_list(struct linked_list *head)
{
    struct linked_list *node = head;
    while (node = node -> next, free(node -> prev), node -> next)
        ;
    free(node);
    global_count = 0;
}

void f_record(FPTR fp)
{
    if (!global_count){
        start = malloc(sizeof(struct linked_list));
        last = malloc(sizeof(struct linked_list));
        start -> next = last;
        start -> prev = NULL;
        start -> fptr = fp;
        last -> next = NULL;
        last -> prev = start;
        last -> fptr = NULL;
    }
    else if (global_count == 1){
        last -> fptr = fp;
    }
    else{
        append(&last, fp);
    }
    global_count++;
}

void func(void)
{
    struct linked_list *node = start;
    do {
        (node -> fptr)();
    } while ((node = node -> next));
    free_the_linked_list(start);
}

int main(void)
{
    f_record(bar);
    f_record(foo);
    f_record(proc);
    f_record(method);
    f_record(past);
    f_record(rust);

    func();
    printf("\n \n");

    f_record(gus);
    f_record(past);
    f_record(rust);

    func();

}