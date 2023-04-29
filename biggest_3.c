#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 8
#define randomize() srand((unsigned)time(0))

int main(void){
    randomize();
    int a[SIZE]={0};
    
    for(int i=0;i<SIZE;i++){
        a[i]=rand()%100;
    }
    
    int a_print[SIZE]={0};
    
    for(int i=0;i<SIZE;i++){
        a_print[i]=a[i];
    }
    
    int max_numbers[3]={0};
    int min=a[0];
    
    for(int i=0;i<SIZE;i++){
        if(a[i]<min){
            min=a[i];
        }
    }
    
    for(int rep=0;rep<3;rep++){
        
        int max_index=0;
        for(int i=0;i<SIZE;i++){
            if(a[i]>a[max_index]){
                max_index=i;
            }
        }
        
        max_numbers[2-rep]=a[max_index];
        a[max_index]=min;
    }
    
    for(int i=0;i<SIZE;i++){
        switch(i){
            case 0:printf("{%d,",a_print[i]);break;
            case SIZE-1:printf("%d}",a_print[i]);break;
            default:printf("%d,",a_print[i]);break;
        }
    }
    
    printf("\n");
    
    for(int i=0;i<3;i++){
        printf("%d ",max_numbers[i]);
    }
}