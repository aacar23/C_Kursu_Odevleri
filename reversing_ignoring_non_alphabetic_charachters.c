#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int len_str_letter(char *str){
    int length=0;
    for(int i=0;str[i]!='\0';i++){
        if(isalpha(str[i])){
            length++;
        }
    }
    return length;
}
int len_str(char *str){
    int i=0;
    for(i=0;str[i]!='\0';i++);
    return i;
}

void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=(char)c;
    *str='\0';
}

void reverse_alpha(char *str){
    int limit= len_str_letter(str);
    int i=0;
    int forward=0;
    int backward= len_str(str)-1;

        while(i<= limit/2) {
            if (!!isalpha(str[forward]) == !!isalpha(str[backward])) {
                char temp = str[forward];
                str[forward++] = str[backward];
                str[backward--] = temp;
                i++;
            }
            else if (!isalpha(str[forward]) && !!isalpha(str[backward])) {
                forward++;
            }
            else if (!!isalpha(str[forward]) && !isalpha(str[backward])) {
                backward--;
            }


        }
}


int main(void){
    char str[SIZE];
    sgets(str);
    reverse_alpha(str);
    puts(str);

}