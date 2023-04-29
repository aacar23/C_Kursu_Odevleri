#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void sgets(char *p){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
       *p++=c;
    p='\0';
}

int len_str(char *str){
    int i;
    for(i=0;str[i]!='\0';i++);
    return i;
}

void bubble_sort_remove_from_helper(char *str){
    int limit=len_str(str)-1;
    for(int i=0;i<limit;i++){
        for(int k=0;k<limit;k++){
            if(str[k]==-1){
                int temp=str[k];
                str[k]=str[k+1];
                str[k+1]=temp;
            }
        }
    }
}

void fix_coding_place(char *str){
    for(int i=0;i<len_str(str);i++){
        if(str[i]==-1){
            str[i]=0;
        }
    }
}

void remover_loop(char *str,char *rmv){
    for(int i=0;i<len_str(str);i++){
        for(int k=0;k<len_str(rmv);k++){
            if(str[i]==rmv[k]){
                str[i]=-1;
                break;
            }
        }
    }
}

void remove_from(char *str){
    char rmv[SIZE];
    sgets(rmv);
    remover_loop(str,rmv);
    bubble_sort_remove_from_helper(str);
    fix_coding_place(str);
}

int main(void){
    char str[SIZE];
    sgets(str);
    remove_from(str);
    printf("%s",str);
}