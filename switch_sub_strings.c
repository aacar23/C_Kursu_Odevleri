#include <stdio.h>
#define SIZE 100
void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=c;
    *str='\0';
}

int str_len(char *str){
    int i=0;
    for(i=0;str[i]!='\0';i++);
    return i;
}
int str_len_start(char *str){
    int i;
    for(i=0;str[i]!='\x20';i++);
    return i;
}
int str_len_end(char *str){
    return str_len(str)- str_len_start(str)+1;
}


void reverse(char *str){
    for(int i=0;i< str_len(str)/2;i++){
        char temp=str[i];
        str[i]=str[str_len(str)-i-1];
        str[str_len(str)-i-1]=temp;
    }
}

void reverse_start(char *str){
    for(int i=0;i< str_len_start(str)/2;i++){
        char temp=str[i];
        str[i]=str[str_len_start(str)-i-1];
        str[str_len_start(str)-i-1]=temp;
    }
}

void reverse_end(char *str){
    int ind= str_len_start(str)+1;
    for(int i= 0;i< (str_len(str)- str_len_start(str))/2;i++){
        char temp=str[ind];
        str[ind]=str[str_len(str)-i-1];
        str[str_len(str)-i-1]=temp;
        ind++;
    }
}

void switch_subs(char *str){
    reverse(str);
    reverse_start(str);
    reverse_end(str);
}

int main(void){
    char str[SIZE];
    sgets(str);
    switch_subs(str);
    puts(str);
}