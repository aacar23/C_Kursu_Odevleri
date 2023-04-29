int searchInsert(int* nums, int numsSize, int target){
    int first = 0;
    int last = numsSize - 1;
    int mid;
    int mid_ret = 10*10*10*10 + 1;
    while (first <= last){
        mid = (first + last) / 2;
        if (*(nums + mid) == target)
            return mid;
        if (mid != 0 && *(nums + mid) > target && *(nums + mid - 1) < target)
            mid_ret = mid;
        else if (mid != numsSize - 1 && *(nums + mid) < target && *(nums + mid + 1) > target)
            mid_ret = mid + 1;
        
        if (*(nums + mid) > target)
            last = mid - 1;
        else
            first = mid + 1;
    }
    

    if (*nums > target)
        return 0;
    else if (*(nums + numsSize - 1) < target)
        return numsSize;
    return mid_ret;
}