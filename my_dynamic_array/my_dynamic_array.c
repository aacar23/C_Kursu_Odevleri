#define MEMBERS

#include "my_dynamic_array.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CORE(dyn_arr) ((dyn_arr) -> core_pointer)
#define ARRAY(dyn_arr) (((dynamic_array_core *)CORE(dyn_arr)) -> arr)
#define SIZE(dyn_arr) (((dynamic_array_core *)CORE(dyn_arr)) -> size)
#define CAPACITY(dyn_arr) (((dynamic_array_core *)CORE(dyn_arr)) -> capacity)
#define TYPE_SIZE(dyn_arr) (((dynamic_array_core *)CORE(dyn_arr)) -> type_size)

#define malloc(size) (checked_malloc((size)))
#define calloc(number_of_elements, size) (checked_calloc((number_of_elements), (size)))






typedef struct{
    size_t size;
    size_t capacity;
    element *arr;
    size_t type_size;
}dynamic_array_core;







static void *checked_calloc(size_t number_of_elements, size_t size)
{
    void *vp = (calloc)(number_of_elements, size);
    if (!vp){
        fprintf(stderr, "failed to allocate");
        exit(EXIT_FAILURE);
    }
    return vp;
}

static dynamic_array *initiate_capacity(dynamic_array *arr)
{
    if (SIZE(arr) >= CAPACITY(arr)){
        element *reallocated = realloc(ARRAY(arr), (CAPACITY(arr) *= 2) * TYPE_SIZE(arr));
        if (!reallocated)
            return NULL;
        ARRAY(arr) = reallocated;
        memset((char *)ARRAY(arr) + (CAPACITY(arr) / 2) * TYPE_SIZE(arr), 0, (CAPACITY(arr) / 2) * TYPE_SIZE(arr));
    }
    return arr;
}






dynamic_array *create_array(size_t capacity_value, size_t type_size_value)
{
    dynamic_array *new_array = calloc(1, sizeof(dynamic_array));
    dynamic_array_core *new_array_core = calloc(1, sizeof(dynamic_array_core));

    CORE(new_array) = new_array_core;
    TYPE_SIZE(new_array) = type_size_value;
    CAPACITY(new_array) = capacity_value;
    ARRAY(new_array) = calloc(capacity_value + 1, type_size_value);

    return new_array;
}

void disable_array(dynamic_array *arr)
{
    free(arr -> core_pointer);
    free(arr);
}






dynamic_array *append_element(dynamic_array *arr, element *val)
{
    if (!initiate_capacity(arr))
        return NULL;
    memcpy((char *)ARRAY(arr) + (SIZE(arr)++) * TYPE_SIZE(arr), val, TYPE_SIZE(arr));
    return arr;
}

dynamic_array *insert_element(dynamic_array *arr, element *val, size_t index)
{
    if (index >= SIZE(arr))
        return NULL;
    SIZE(arr)++;
    if (!initiate_capacity(arr))
        return NULL;
    memmove((char *)ARRAY(arr) + (index + 1) * TYPE_SIZE(arr), (char *)ARRAY(arr) + index * TYPE_SIZE(arr), TYPE_SIZE(arr) * (SIZE(arr)));
    memcpy((char *)ARRAY(arr) + index * TYPE_SIZE(arr), val, TYPE_SIZE(arr));
    return arr;
}

dynamic_array *push_element(dynamic_array *arr, element *val)
{
    return insert_element(arr, val, 0);
}






dynamic_array *delete_element(dynamic_array *arr, size_t index)
{
    if (SIZE(arr) < 2)
        return NULL;
    SIZE(arr)--;
    memmove((char *)ARRAY(arr) + index * TYPE_SIZE(arr), (char *)ARRAY(arr) + (index + 1) * TYPE_SIZE(arr), TYPE_SIZE(arr) * (SIZE(arr) - index + 1));
    return arr;
}

dynamic_array *pop_element(dynamic_array *arr)
{
    if (SIZE(arr) == 1)
        return drop_element(arr);
    return delete_element(arr, 0);
}

dynamic_array *drop_element(dynamic_array *arr)
{
    if (SIZE(arr) == 0)
        return NULL;
    SIZE(arr)--;
    return arr;
}






size_t get_size(const dynamic_array *arr)
{
    return SIZE(arr);
}

size_t get_capacity(const dynamic_array *arr)
{
    return CAPACITY(arr);
}

element *get_array(const dynamic_array *arr)
{
    return ARRAY((dynamic_array *)arr);
}

size_t get_type_size(const dynamic_array *arr)
{
    return TYPE_SIZE(arr);
}