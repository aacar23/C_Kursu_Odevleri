void moveZeroes(int* nums, int numsSize){
    for (int i = numsSize - 1; i >= 0;i--){
        int temp_i = i;
        if (nums[temp_i] == 0){
            printf("a %d", temp_i);
            for (int k = temp_i;k < numsSize - 1;k++){
                if (nums[temp_i] == 0){
                    int temp = *(nums + k);
                    *(nums + k) = *(nums + k + 1);
                    *(nums + k + 1) = temp;
                    temp_i = k + 1;
                }
                else{
                    break;
                }
            }
        }
    }
}