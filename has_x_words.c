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
    while((c=getchar())!='\n' && c!=-1)
        *str++=(char)c;
    *str='\0';
}


int word_count_of_string(char *str){
    int word_count=0;

    for(int i=0;str[i]!='\0';i++){
        if(((isblank)(str[i])) && (isalpha)(str[i+1])){
            word_count++;
        }

        else if(i==0 && str[i]!='\x20'){
            word_count++;
        }
    }
    return word_count;
}


int main(void){
    char str[SIZE];
    sgets(str);
    printf("This text has %d words", word_count_of_string(str));
}
