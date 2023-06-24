#if !defined MY_DYNAMIC_ARRAY_H && defined MEMBERS
#define MY_DYNAMIC_ARRAY_H

struct elem MEMBERS;

#include <stddef.h>

typedef struct{
    void *core_pointer;
}dynamic_array;

typedef struct elem element;

dynamic_array *create_array(size_t capacity_value, size_t type_size_value);
void disable_array(dynamic_array *arr);

dynamic_array *append_element(dynamic_array *arr, element *val);
dynamic_array *insert_element(dynamic_array *arr, element *val, size_t index);
dynamic_array *push_element(dynamic_array *arr, element *val);

dynamic_array *delete_element(dynamic_array *arr, size_t index);
dynamic_array *pop_element(dynamic_array *arr);
dynamic_array *drop_element(dynamic_array *arr);

size_t get_size(const dynamic_array *arr);
size_t get_capacity(const dynamic_array *arr);
element *get_array(const dynamic_array *arr);
size_t get_type_size(const dynamic_array *arr);

#endif
