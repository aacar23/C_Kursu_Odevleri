#ifdef EOF
#define define_set_multidimensional_array_int(type_length) void set_multidimensional_array_int_##type_length(int (*arr)[type_length], int less, size_t size) \
                                                            {                                                                        \
                                                                int element;                                                         \
                                                                FILE *f = fopen("/dev/urandom", "r");                                \
                                                                while(size--){                                                       \
                                                                    for (size_t i = 0;i < type_length;i++){                             \
                                                                        fread(&element, sizeof(element), 1, f);                      \
                                                                        *(*arr + i) = element % less;                                \
                                                                    }                                                                \
                                                                    arr++;                                                           \
                                                                }                                                                    \
                                                                fclose(f);                                                           \
                                                            }    \

#define define_print_multidimensional_array_int(type_length) void print_multidimensional_array_##type_length(const int (*arr)[type_length], size_t size) \
                                                            {                                                                             \
                                                                while(size--){                                                            \
                                                                    for (size_t i = 0;i < type_length;i++)                                   \
                                                                        printf("%-3d ", *(*arr + i));                                       \
                                                                    putchar('\n');                                                        \
                                                                    arr++;                                                                \
                                                                }                                                                         \
                                                                                                                                          \
                                                                putchar('\n');                                                            \
                                                            }                                                                             \
                                                            \

#endif