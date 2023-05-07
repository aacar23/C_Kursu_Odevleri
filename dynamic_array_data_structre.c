#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define malloc(bytes) (checked_malloc(bytes))
#define realloc(ptr, new_size) (checked_realloc(ptr, new_size))

void *checked_malloc(size_t bytes)
{
    void *new_ptr = (malloc)(bytes);

    if (!new_ptr){
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void *checked_realloc(void *ptr, size_t new_size)
{
    void *new_ptr = (realloc)(ptr, new_size);

    if (!new_ptr) {
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

struct dynamic_array{
    size_t size;
    size_t capacity;
    size_t type_size;
    void *address;
};

struct dynamic_array *create_new_dynamic_array(size_t start_capacity, size_t type_sz)
{
    struct dynamic_array *new_dynamic_array = (struct dynamic_array *) malloc(sizeof(struct dynamic_array));

    new_dynamic_array -> address = malloc((new_dynamic_array -> capacity = start_capacity) * (new_dynamic_array -> type_size = type_sz));
    new_dynamic_array -> size = 0;
    return new_dynamic_array;
}

struct dynamic_array *resize_dynamic_array(struct dynamic_array *ptr, size_t new_size)
{
    return ptr -> address = realloc(ptr -> address, (ptr -> capacity = new_size) * ptr -> type_size);
}

struct dynamic_array *append_new_value_generic(struct dynamic_array *dyn_arr, const void *val_pointer)
{
    if (dyn_arr -> size < dyn_arr -> capacity){
        char *array_pointer = (char *) (dyn_arr -> address);

        memcpy((array_pointer + dyn_arr -> size++ * dyn_arr -> type_size), val_pointer, dyn_arr -> type_size);
    }
    else if (dyn_arr -> size == dyn_arr -> capacity){
        char *array_pointer = (char *) resize_dynamic_array(dyn_arr, dyn_arr -> capacity * 2);

        memcpy((array_pointer + dyn_arr -> size++ * dyn_arr -> type_size), val_pointer, dyn_arr -> type_size);
    }
    return dyn_arr;
}

struct dynamic_array *add_from_middle(struct dynamic_array *ptr, const void *val_pointer, int index)
{
    resize_dynamic_array(ptr, (ptr -> capacity + 1));
    char *ptr_address = (char *)(ptr -> address);

    *(ptr_address + ptr -> size) = 0;
    memmove(ptr_address + (index + 1) * ptr -> type_size, ptr_address + index * ptr -> type_size, (ptr -> size++ - index) * ptr -> type_size);
    memcpy(ptr_address + index * ptr -> type_size, val_pointer, ptr -> type_size);
    return ptr;
}

void free_dynamic_array(struct dynamic_array *ptr)
{
    free(ptr -> address);
    free(ptr);
}