#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int min_size(const char **strs, int strsSize)
{
    int min = strlen(*strs);
    while(strsSize--)
        if (strlen(*strs) < min)
            min = strlen(*strs);
    return min;
}

char * longestCommonPrefix(const char ** strs, int strsSize){
    int shortest = min_size(strs, strsSize);
    printf("%d\n", shortest);
    if (shortest == 0)
        return "";
    if (strsSize == 1)
        return *strs;
    char *pd = malloc(sizeof(char) * (shortest + 1));
    for(int i = 0;i < shortest + 1;i++)
        pd[i] = '\0';
    for(int k = 0;k < shortest;k++){
        int previous = strs[0][k];
        int not_equal = 0;
        int i;
        for(i = 0;i < strsSize;i++){
            if (previous != strs[i][k]){
                not_equal = 1;
                break;
            }
            previous = strs[i][k];
        }
        printf("%d", k);
        if(not_equal)
            break;
        else if(k == shortest - 1 && strsSize == i){
            pd[k] = strs[0][k];
            return pd;
        }
        pd[k] = strs[0][k];
    }
    return pd;

}