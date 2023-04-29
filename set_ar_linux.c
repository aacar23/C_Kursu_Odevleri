#include <stdio.h>

void set_random_ar_linux(int (*ptr)[5], int less, size_t size)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while (size--){
        for (int i = 0;i < 5;i++){
            fread(&element, sizeof(element), 1, f);
            *(*ptr + i) = element % less;
        }
        ptr++;
    }
    fclose(f);
}