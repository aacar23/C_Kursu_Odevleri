#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 100



int len_str(char *p){
    int i;
    for(i=0;p[i]!='\0';i++)
       ;
    return i;
}

void bubble_sort_string_helper(char *s){
    for(int i=0;i<len_str(s)-1;i++){
        for(int k=0;k<len_str(s)-1;k++){
            if(s[k]<0){
                int temp=s[k];
                s[k]=s[k+1];
                s[k+1]=temp;
            }
        }
    }
}

void clear_buffer(){
    int c;
    while((c=getchar())!='\n' && c!=-1);
}

void sgets(char *p){
    
    int c;
    int i;
    for(i=0;((c=getchar())!='\n' && c!=-1);i++){
        p[i]=(char)(c);
    }
    
    p[i]='\0';
    
}

void send_removed(signed char *start,signed char *dest){
    
    char rmv[SIZE];
    int c;
    int i;
    for(i=0;(c=getchar())!='\n';i++){
        rmv[i]=(char)c;
    }
    
    rmv[i]='\0';
    
    int count=0;
    
    int cnt=0;
    for(cnt=0;cnt<len_str(start);cnt++){
        int co=0;
        
        while(co<len_str(start)){
            if(start[cnt]==rmv[co]){
                start[cnt]=-1;
                co++;
                break;
            }
            co++;
        }
        
        
       
        
    }
    bubble_sort_string_helper(start);
    int s;
    for(s=0;start[s]!=-1;s++){
        dest[s]=start[s];
    }
    dest[s]='\0';
    
}




int main(void){
    signed char str[SIZE]={0};
    printf("isim girin:");
    sgets(str);
    clear_buffer();
    signed char dest[SIZE]={0};
    printf("yok edilecek karakter ya da karakterleri girin:");
    send_removed(str,dest);
    
    
    for(int i=0;dest[i]!='\0';i++){
        printf("%c",dest[i]);
    }
    printf("\n");
    
}