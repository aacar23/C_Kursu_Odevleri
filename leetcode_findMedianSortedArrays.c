#include <stdlib.h>
#include <stdio.h>
double findMedianSortedArrays(const int* nums1, int nums1Size, const int* nums2, int nums2Size)
{
    int idx_nums1 = 0;
    int idx_nums2 = 0;
    int *pd = malloc((nums1Size + nums2Size) * sizeof(int));
    if (pd == NULL){
        printf("not enough memory");
        return -2.23;
    }
    for (int i = 0;i < nums1Size + nums2Size;i++){
        if (idx_nums1 == nums1Size)
            pd[i] = nums2[idx_nums2++];
        else if (idx_nums2 == nums2Size)
            pd[i] = nums1[idx_nums1++];
        else if (nums1[idx_nums1] < nums2[idx_nums2])
            pd[i] = nums1[idx_nums1++];
        else
            pd[i] = nums2[idx_nums2++];
    }

    if ((nums1Size + nums2Size) % 2){
        double ret_val = (double)pd[(nums1Size + nums2Size - 1)/2];
        free(pd);
        return ret_val;
    }
    else{
        double ret_val = ((double)pd[(nums1Size + nums2Size - 2) / 2] + (double)pd[(nums1Size + nums2Size) / 2]) / 2;
        free(pd);
        return ret_val;
    }
}