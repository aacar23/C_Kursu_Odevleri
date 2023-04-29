#include <stddef.h>

#define asize(a) (sizeof(a) / sizeof(*a))

int *max_point(const int *arr, const int *end)
{
    const int *max = arr;


    while (arr <= end){
        if (*arr > *max)
            max = arr;
        arr++;
    }


    return (int *)max;
}

int trap_forward(const int *arr, const int *max)
{
    int sum = 0;
    do{
        if (*arr)
            break;
    }while (++arr);
    const int *current_max = arr;


    while (arr < max){
        if((*arr > *(arr + 1) && *arr > *current_max) || (*arr == *(arr + 1) && *arr > *current_max)){
            sum += *current_max - *arr;
            current_max =  arr++;
            continue;
        }
        else if(*(arr + 1) > *arr && *(arr + 1) > *current_max)
        {
            sum += *current_max - *arr;
            current_max = arr++ + 1;
            continue;
        }
        sum += *current_max - *arr++;
    }


    return sum;

}

int trap_backward(const int *max, const int *end)
{
    int sum = 0;
    do{
        if (*end)
            break;
    } while (--end);
    const int *current_max = end;


    while (end > max) {
        if ((*end > *(end - 1) && *end > *current_max) || (*end == *(end - 1) && *end > *current_max)){
            sum += *current_max - *end;
            current_max = end--;
            continue;
        }
        else if(*(end - 1) > *end && *(end - 1) > *current_max)
        {
            sum += *current_max - *end;
            current_max = end-- - 1;
            continue;
        }
        sum += *current_max - *end--;
    }


    return sum;
}

int trap(int *arr, size_t size)
{
    if (size == 1 || size == 0)
        return 0;

    
    return trap_forward(arr, max_point(arr, arr + size - 1)) + trap_backward(max_point(arr, arr + size - 1), arr + size - 1);
}