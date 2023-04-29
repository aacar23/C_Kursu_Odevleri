#include <stdio.h>

#define SIZE 100

int len_str(char *str){
    int i;
    for(i=0;str[i]!='\0';i++);
    return i;
}

void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=c;
    *str='\0';
}


void reverse_string( char *str){
    int limit=len_str(str);
    for(int i=0;i<limit/2;i++){
        int temp=str[i];
        str[i]=str[limit-1-i];
        str[limit-1-i]=temp;
    }    
}

int main(void){
    char str[SIZE];
    sgets(str);
    reverse_string(str);
    puts(str);
}