#include <stdio.h>
double double_max3(double first,double second,double third){
    return (first>=second)?
           (first >=third) ?(first) :(third)
                          :(second>=third)?(second):(third);
}
int integer_max3(int first,int second,int third){
    return (first>=second)?
           (first >=third) ?(first) :(third)
                          :(second>=third)?(second):(third);
}
int integer_max4(int first,int second,int third,int fourth){
    int big_number1;
    int big_number2;
    if(first>=second){
        big_number1=first;
    }
    else{
        big_number1=second;
    }

    if(third>=fourth){
        big_number2=third;
    }
    else{
        big_number2=fourth;
    }

    if(big_number1>=big_number2){
        return big_number1;
    }
    return big_number2;
}
double double_max4(double first,double second,double third,double fourth){
    double big_number1;
    double big_number2;
    if(first>=second){
        big_number1=first;
    }
    else{
        big_number1=second;
    }

    if(third>=fourth){
        big_number2=third;
    }
    else{
        big_number2=fourth;
    }

    if(big_number1>=big_number2){
        return big_number1;
    }
    return big_number2;
}
int main(void){
    printf("%lf\n",double_max3(1.9,2.0,2.0));
    printf("%d\n",integer_max3(3,5,4));
    printf("%d\n", integer_max4(3,5,3,4));
    printf("%.11lf\n", double_max4(3.25679902334,3.25679902333,3.2,3.23));
}