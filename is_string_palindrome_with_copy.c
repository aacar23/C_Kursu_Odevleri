#include <stdio.h>
#include <ctype.h>

#define SIZE 100

void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=(char)c;
    *str='\0';
}

int len_str(char *str){
    int i=0;
    for(i=0;str[i]!='\0';i++);
    return i;
}

void alphasize(char *str){
    int limit= len_str(str);
    int write_idx=0;
    for(int i=0;i<limit;i++){
        if(isalpha(str[i]))
            str[write_idx++]= toupper(str[i]);
    }
    str[write_idx]='\0';
}

void send_string(char *str,char *target){
    int limit= len_str(str);
    int i;
    for(i=0;i<limit && str[i]!='\0';i++){
        target[i]=str[i];
    }
    target[i]='\0';

}

void reverse_string(char *str){
    int limit= len_str(str);
    for(int i=0;i<limit/2;i++){
        char temp=str[i];
        str[i]=str[limit-1-i];
        str[limit-1-i]=temp;
    }
}

int main(void){
    char str[SIZE];
    sgets(str);
    alphasize(str);
    char copy[SIZE];
    send_string(str,copy);
    alphasize(copy);
    reverse_string(copy);

    for(int i=0;i< len_str(str);i++){
        if(str[i]!=copy[i]){
            puts("this isn't a palindrome");
            return 0;
        }
    }
    puts("this is a palindrome");
}