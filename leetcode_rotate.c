void reverse (int *start, int *end)
{
    while(start < end){
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void rotate(int* nums, int numsSize, int k){
    k %= numsSize;
    reverse(nums, nums + numsSize - 1);
    reverse(nums, nums + k - 1);
    reverse(nums + k, nums + numsSize - 1);
}