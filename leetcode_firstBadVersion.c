// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
#include <stdbool.h>
#include <stdlib.h>
int firstBadVersion(int n) {

    int first = 1;
    int last = n;
    if (isBadVersion(first))
        return first;
    while(first <= last){
        int mid = (int)(((long)first + last) / 2);
        if (!isBadVersion(mid) && isBadVersion(mid + 1))
            return mid + 1;
        else if (!isBadVersion(mid) && !isBadVersion(mid + 1))
            first = mid + 1;
        else
            last = mid - 1;
    }
    return 0;
}