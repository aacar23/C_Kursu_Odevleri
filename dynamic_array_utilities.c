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


void set_dynamic_array_random(struct dynamic_array *dyn_arr, size_t blocks_to_be_set)
{
    FILE *f = fopen("/dev/urandom", "r");
    char *arr_address = (char *)(dyn_arr -> address);

    while (blocks_to_be_set--){
        fread(arr_address, dyn_arr -> type_size, 1, f);
        arr_address += dyn_arr -> type_size;
        dyn_arr -> size++;
    }
    fclose(f);
}


struct dynamic_array *create_new_dynamic_array(size_t start_capacity, size_t type_sz)
{
    struct dynamic_array *dyn_arr = (struct dynamic_array *) malloc(sizeof(struct dynamic_array));

    dyn_arr -> address = malloc((dyn_arr -> capacity = start_capacity) * (dyn_arr -> type_size = type_sz));
    dyn_arr -> size = 0;
    return dyn_arr;
}


struct dynamic_array *create_new_dynamic_array_full_of_random_values(size_t start_capacity, size_t type_sz)
{
    struct dynamic_array *dyn_arr = create_new_dynamic_array(start_capacity, type_sz);

    set_dynamic_array_random(dyn_arr, start_capacity);
    return dyn_arr;
}


struct dynamic_array *create_new_dynamic_array_has_n_random_values(size_t start_capacity, size_t type_sz, size_t n)
{
    struct dynamic_array *dyn_arr = create_new_dynamic_array(start_capacity, type_sz);

    set_dynamic_array_random(dyn_arr, n);
    return dyn_arr;
}


struct dynamic_array *resize_dynamic_array(struct dynamic_array *dyn_arr, size_t new_size)
{
    dyn_arr -> address = realloc(dyn_arr -> address, (dyn_arr -> capacity = new_size) * dyn_arr -> type_size);

    return dyn_arr;
}


struct dynamic_array *append_new_value(struct dynamic_array *dyn_arr, const void *val_pointer)
{
    if (dyn_arr -> size < dyn_arr -> capacity){
        char *array_pointer = (char *) (dyn_arr -> address);

        memcpy((array_pointer + dyn_arr -> size++ * dyn_arr -> type_size), val_pointer, dyn_arr -> type_size);
    }
    else{
        char *array_pointer = (char *) resize_dynamic_array(dyn_arr, dyn_arr -> capacity * 2);

        memcpy((array_pointer + dyn_arr -> size++ * dyn_arr -> type_size), val_pointer, dyn_arr -> type_size);
    }
    return dyn_arr;
}


struct dynamic_array *add_from_middle(struct dynamic_array *dyn_arr, const void *val_pointer, int index)
{
    if (dyn_arr -> size < dyn_arr -> capacity) {
        char *ptr_address = (char *)(dyn_arr->address);

        *(ptr_address + dyn_arr -> size++) = 0;
        memmove(ptr_address + (index + 1) * dyn_arr -> type_size, ptr_address + index * dyn_arr -> type_size,(dyn_arr -> size - index) * dyn_arr -> type_size);
        memcpy(ptr_address + index * dyn_arr -> type_size, val_pointer, dyn_arr -> type_size);
    }
    else{
        char *ptr_address = (char *)(dyn_arr -> address);

        resize_dynamic_array(dyn_arr, dyn_arr -> capacity * 2);
        *(ptr_address + dyn_arr -> size++) = 0;
        memmove(ptr_address + (index + 1) * dyn_arr -> type_size, ptr_address + index * dyn_arr -> type_size,(dyn_arr -> size - index) * dyn_arr -> type_size);
        memcpy(ptr_address + index * dyn_arr -> type_size, val_pointer, dyn_arr -> type_size);
    }
    return dyn_arr;
}


void free_dynamic_array(struct dynamic_array *ptr)
{
    free(ptr -> address);
    free(ptr);
}


#define create_append_new_value_type_func(type) struct dynamic_array *append_new_value_##type(struct dynamic_array *dyn_arr, type val) \
                                                {                                                                                      \
                                                    const void *val_pointer = &val;                                                    \
                                                                                                                                       \
                                                    return append_new_value(dyn_arr, val_pointer);                             \
                                                }


#define create_add_from_middle_type_func(type) struct dynamic_array *add_from_middle_##type(struct dynamic_array *dyn_arr, type val, int index) \
                                                {                                                                                               \
                                                    const void *val_pointer = &val;                                                             \
                                                                                                                                                \
                                                    return add_from_middle(dyn_arr, val_pointer, index);                                        \
                                                }


#define dynamic_array_access_type(dyn_arr, type, index) (((type *)((dyn_arr) -> address))[(index)])
