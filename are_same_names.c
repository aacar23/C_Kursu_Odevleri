#include <stdio.h>


#define S1_TEST_SIZE 30
#define S2 TEST_SIZE 50
#define S1_STRING_LENGTH 70
#define S2_STRING_LENGTH 70
#define asize(a) (sizeof(a)/sizeof(a[0]))

int length_of_string(char *str){
    int i;
    for(i=0;str[i]!='\0';i++);
    
    return i;
}

int are_same_names(char *str1,char *str2){
    if(asize(str1)!=asize(str2)){
        return 0;
    }
    if(length_of_string(str1) != length_of_string(str2)){
        return 0;
    }
    
    for(int i=0;i<length_of_string(str1);i++){
        if(str1[i]!=str2[i])
           return 0;
    }
    
    return 1;
}

int main(void){
    char s1[S1_STRING_LENGTH];
    char s2[S2_STRING_LENGTH];
    scanf("%s%s",s1,s2);
    printf("1.yazi[%s] ve 2.yazi[%s]\n",s1,s2);
    if(are_same_names(s1,s2)){
        printf("ayni isimler\n");
    }
    else{
        printf("farkli isimler\n");
    }
}
