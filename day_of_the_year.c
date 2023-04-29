#include <stdio.h>
int isleap(int year){
    return (year%400==0 || year%100!=0 && year%4==0)?1:0;
}
int day_of_year(int day,int mon,int year){
    int ret_val=day;
    mon-=1;
    int days_of_months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(isleap(year)){
        days_of_months[1]=29;
    }
    for(int i=0;i<mon;i++){
        ret_val+=days_of_months[i];
    }
    return ret_val;

}
int main(void){
    printf("%d", day_of_year(31,12,2004));
}