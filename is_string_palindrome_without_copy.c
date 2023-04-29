#include <stdio.h>
#include <ctype.h>

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

void reverse_string(char *str){
    int limit=len_str(str);

    for(int i=0;i<limit/2;i++){
        char temp=str[i];
        str[i]=str[limit-1-i];
        str[limit-1-i]=temp;
    }

}

void alphabetisize(char *str){
    int limit=len_str(str);

    int write_idx=0;
    for(int i=0;i<limit;i++){
        if(isalpha(str[i])){
            str[write_idx++]=(char)toupper(str[i]);
        }
    }
    str[write_idx]='\0';
}

int is_palindrome(char *str){
    alphabetisize(str);
    int limit=len_str(str);

    for(int i=0;i<limit/2;i++){
        if(str[i]!=str[limit-1-i]){
            return 0;
        }
    }

    return 1;
}

int main(void){
    char str[SIZE];
    sgets(str);
    
    if(is_palindrome(str)){
        puts("this writing is a palindrome");
    }
    else{
        puts("this isn't a palindrome");
    }
}