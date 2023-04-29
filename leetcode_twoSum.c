/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
    int l = 0;
    int r = numbersSize - 1;
    int *returnArray = malloc(sizeof(int) * 2);
    while (l < r){
        if (numbers[l] + numbers[r] > target)
            r--;
        else if (numbers[l] + numbers[r] < target)
            l++;
        else{
            returnArray[0] = l + 1;
            returnArray[1] = r + 1;
            break;
        }
    }
    *returnSize = 2;
    return returnArray;
}