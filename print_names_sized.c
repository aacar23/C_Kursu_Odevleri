#include <stdio.h>

#define define_print_names(type_size) void print_names_##type_size(const char (*ptr)[type_size], size_t size) \
                                       {                                                          \
                                            while(size--)                                         \
                                                puts(*ptr++);                                     \
                                                                                                  \
                                            putchar('\n');                                        \
                                       }                                                          \