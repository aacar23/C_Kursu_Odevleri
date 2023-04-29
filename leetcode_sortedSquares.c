/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

void reverse(int *a, size_t size)
{
    for (int i = 0;i < (int)size / 2;i++){
        int temp = *(a + i);
        *(a + i) = *(a + size - 1 - i);
        *(a + size - 1 - i) = temp;
    }
}

void merge(int *dest, const int *a, size_t size_a, const int *b, size_t size_b)
{
    int idx_a = 0;
    int idx_b = 0;
    for (int i = 0;i < (int)(size_a + size_b);i++){
        if (idx_a == (int)size_a)
            dest[i] = b[idx_b++];
        else if (idx_b == (int)size_b)
            dest[i] = a[idx_a++];
        else if (a[idx_a] > b[idx_b])
            dest[i] = b[idx_b++];
        else
            dest[i] = a[idx_a++]; 
    }    
}

int* sortedSquares(const int* nums, int numsSize, int* returnSize){
    int positive_count = 0;
    int negative_count = 0;
    for (int i = 0;i < numsSize;i++){
        if (*(nums + i) >= 0)
            positive_count++;
        else
            negative_count++;
    }
    int *positives = malloc(sizeof(int) * positive_count);
    int *negatives = malloc(sizeof(int) * negative_count);
    int positives_idx = 0;
    int negatives_idx = 0;
    for (int i = 0;i < numsSize;i++){
        if (*(nums + i) >= 0)
            positives[positives_idx++] = nums[i] * nums[i];
        else
            negatives[negatives_idx++] = nums[i] * nums[i];
    }
    reverse(negatives, negative_count);
    int *final = malloc((positive_count + negative_count) * sizeof(int));
    *returnSize = (positive_count + negative_count);
    merge(final, positives, positive_count, negatives, negative_count);
    return final;
}