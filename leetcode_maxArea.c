#define smaller(a, b) ((a) > (b) ? (b) : (a))
#define absolute(expr) ((expr) > 0 ? (expr) : -(expr))
#define result(index_left, index_right, array) (smaller((array)[(index_left)], (array)[(index_right)]) * absolute((index_left) - (index_right)))
#include <stddef.h>
int find_min(int *arr, size_t size)
{
    int min = *arr;
    while(size--){
        if (*arr < min)
            min = *arr;
        *arr++;
    }
    return *arr;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_two_biggest(int **max, int **runner_up, const int *arr, size_t size)
{
    *max = arr;
    *runner_up = arr + 1;
    if (**max < **runner_up)
        swap(max, runner_up);
    while(size--){
        if (*arr > **max)
            *max = arr;
        else if (*arr > **runner_up)
            *runner_up = arr;
        *arr++;
    }

}
int maxArea(const int* height, int heightSize){
    
    int idx_left_max = 0;
    int idx_right_max = heightSize - 1;
    int *max;
    int *runner_up;
    find_two_biggest(&max, &runner_up, height, (size_t)heightSize);
    for(int idx_left = 0, idx_right = heightSize - 1;idx_left < idx_right;){
        if (result(idx_left_max, idx_right_max, height) < result(idx_left + 1, idx_right, height) && result(idx_left, idx_right - 1, height) < result(idx_left + 1, idx_right, height)) {
            idx_left_max = ++idx_left;
            idx_right_max = idx_right;
        }
        else if (result(idx_left_max, idx_right_max, height) < result(idx_left, idx_right - 1, height) && result(idx_left + 1, idx_right, height) < result(idx_left, idx_right - 1, height)) {
            idx_right_max = --idx_right;
            idx_left_max = idx_left;
        }
        else{
            if(height[idx_left] > height[idx_right])
                idx_right--;
            else
                idx_left++;
        }
    }
    return result(idx_left_max, idx_right_max, height) < result(max - height, runner_up - height, height) ? result(max - height, runner_up - height, height) : result(idx_left_max, idx_right_max, height) ;   
}