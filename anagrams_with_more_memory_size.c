#include <stdio.h>
#include <ctype.h>
#define ALPHA_SIZE 26

#define SIZE 100
int len_str(char *str){
    int i;
    for(i=0;str[i]!='\0';i++);
    return i;
}

void sgets(char *str){
    int c;
    while((c=getchar())!='\n' && c!=EOF)
        *str++=(char)c;
    *str='\0';
}


void are_anagrams_alpha_count(char *str,int *str_alpha){
    for(int i=0;i< len_str(str);i++){
        str_alpha[toupper(str[i])-'A']++;
    }
}

int are_anagrams_compare_counts(int *al_counts_a,int *al_counts_b){
    for(int i=0;i<ALPHA_SIZE;i++){
        if(al_counts_a[i]!=al_counts_b[i]){
            return 0;
        }
    }
    return 1;
}

int are_anagrams(char *str_a,char *str_b){
    int str_a_alpha[ALPHA_SIZE]={0};
    int str_b_alpha[ALPHA_SIZE]={0};

    are_anagrams_alpha_count(str_a,str_a_alpha);
    are_anagrams_alpha_count(str_b,str_b_alpha);

    return are_anagrams_compare_counts(str_a_alpha,str_b_alpha);

}

int main(void){
    char str_0[SIZE];
    char str_O[SIZE];

    sgets(str_0);
    sgets(str_O);

    if(are_anagrams(str_O,str_0)){
        printf("these texts are anagrams");
        return 0;
    }
    printf("they are not anagrams");
}