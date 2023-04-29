#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define asize(a) (sizeof(a) / sizeof(*a))
#define randomize() srand((unsigned)(time(NULL)))

int * search_in_array(const int *p, int size, int key)
{
    int *temp_p = (int *)p;
    int temp_size = size;
    while(temp_size--) {
        if (*temp_p == key)
            return temp_p;
        temp_p++;
    }
    return NULL;
}

void set_random_array(int *p, size_t size, int less)
{
    while (size--){
        *p++ = rand() % less;
    }
}

int main(void)
{
    randomize();
    int a[10];
    set_random_array(a, asize(a), 20);
    int key;
    (void)printf("Aranacak degeri girin:");
    (void)scanf("%d", &key);
    int *p = search_in_array(a, asize(a), key);
    if(p == NULL){
        (void)printf("\nbulunamadi");
    }
    else{
        (void)printf("\n%ld. indiste bulundu", p - a);
    }

}



