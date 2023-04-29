#include <s#include <stdlib.h>
#include <stdio.h>

struct linked_element{
    int val;
    struct linked_element *next;
    struct linked_element *prev;
};

void swap_ptr(struct linked_element **a, struct linked_element **b)
{
    struct linked_element *temp = *a;
    *a = *b;
    *b = temp;
}

size_t size_of_linked_list(const struct linked_element *head)
{
    const struct linked_element *node = head;
    size_t size = 2;
    while ((node = node -> next))
        size++;
    return size;
}

struct linked_element *access_index(const struct linked_element *head, int index)
{
    const struct linked_element *node = head;
    for (int i = 0;i < index;i++)
        node = node -> next;
    return (struct linked_element *)node;
}

struct linked_element *access_key(const struct linked_element *head, int key)
{
    const struct linked_element *node = head;
    while (node -> val != key && (node = node -> next))
        ;
    return (struct linked_element *)node;
}

struct linked_element *append(struct linked_element **end, int val)
{
    struct linked_element *new = malloc(sizeof(struct linked_element));
    new -> val = val;
    new -> next = NULL;
    new -> prev = *end;
    (*end) -> next = new;
    return *end = (*end) -> next;
}

struct linked_element *push(struct linked_element **head, int val)
{
    struct linked_element *new = malloc(sizeof(struct linked_element));
    new -> val = val;
    new -> next = *head;
    new -> prev = NULL;
    (*head) -> prev = new;
    return *head = (*head) -> prev;
}

void insert(struct linked_element *head, int index, int val)
{
    struct linked_element *new = malloc(sizeof(struct linked_element));
    struct linked_element *previous = access_index(head, index - 1);
    new -> next = previous -> next;
    new -> prev = previous;
    new -> val = val;
    previous -> next = new;
}

void remove_end (struct linked_element **end)
{
    struct linked_element *old = *end;
    (*end) -> prev -> next = NULL;
    *end = (*end) -> prev;
    free(old);
}

void remove_head(struct linked_element **head)
{
    struct linked_element *old = *head;
    (*head) -> next -> prev = NULL;
    *head = (*head) -> next;
    free(old);
}

void remove_it(struct linked_element *object)
{
    object -> prev -> next = object -> next;
    object -> next -> prev = object -> prev;
    free(object);
}

void print_linked_list(const struct linked_element *head)
{
    const struct linked_element *node = head;
    while (printf("%d ", node -> val), (node = node -> next))
        ;
    putchar('\n');
}
