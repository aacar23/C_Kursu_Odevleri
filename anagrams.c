#include <stdio.h>
#define SIZE 100
int len_str(char *str){
    int i;
    for(i=0;str[i]!='\0';i++);
    return i;
}


void bubble_sort_string(char *str){
    for(int i=0;i<len_str(str)-1;i++){
        for(int k=0;k< len_str(str)-1;k++){
            if(str[k]>str[k+1]){
                char temp=str[k];
                str[k]=str[k+1];
                str[k+1]=temp;
            }
        }
    }
}

void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=c;
    *str='\0';
}

int are_anagrams(char *str_a,char *str_b){
    bubble_sort_string(str_a);
    bubble_sort_string(str_b);
    if(len_str(str_a)!=len_str(str_b)){
        return 0;
    }
    for(int i=0;str_a[i]!='\0';i++){
        if(str_a[i]!=str_b[i]){
            return 0;
        }
    }
    return 1;
}


int main(void){
    char str[SIZE];
    char another_str[SIZE];
    puts("Enter the first writing:");
    sgets(str);
    puts("Enter the second one:");
    sgets(another_str);
    if (are_anagrams(str,another_str)){
        printf("These arrays are anagrams");
    }
    else{
        printf("they are not anagrams");
    }
}