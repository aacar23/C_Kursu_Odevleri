#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int digits(int number,int base){
    int digit=0;
    while(number){
        number/=base;
        digit++;
    }
    return digit;
}

int number_reversal(int number,int base){
    int digit= digits(number,base);
    int reversed_number=0;
    while(number){

        reversed_number+=number%base*(int)pow(base,--digit);

        number/=base;
    }
    return reversed_number;
}

int input_control_prompt();
int subprompt();
void buffer_cleaner();

int prompt(){
    while(1){
        int process_label;
        printf("What would you like to do ?\n");
        printf("(press 1) seeing the number of digits of a number in a particular base\xA");
        printf("(press 2) reversing a numbers,which is in a particular base of your choosing,digits\xA");
        scanf("%d",&process_label);

        if(process_label==1) {
            int base;
            int number=0;
            printf("Please enter the base of the number whicch you are going to enter after this input:");
            scanf("%d",&base);
            buffer_cleaner();

            switch(base){
                case(10):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%d",&number);
                    break;
                case(16):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%X",&number);
                    break;
                case(8):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%o",&number);
                    break;
                default:
                    printf("Wrong base input try again restarting the prompt...\xA"),prompt();
                    break;
            }
            if(number==0){
                input_control_prompt();
            }
            printf("%d in base %d has %d digits\xA ",number,base,digits(number,base));
            subprompt();
            buffer_cleaner();
            return 0;


        }
        else if(process_label==2) {
            int base;
            int number=0;
            printf("Please enter the base of the number whicch you are going to enter after this input:");
            scanf("%d",&base);
            buffer_cleaner();

            switch(base){
                case(10):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%d",&number);
                    break;
                case(16):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%X",&number);
                    break;
                case(8):
                    printf("Please enter the number that's going to get processed by the digit function:"),scanf("%o",&number);
                    break;
                default:
                    printf("Wrong base input try again restarting the prompt...\xA"),prompt();
                    break;
            }
            if(number==0){
                input_control_prompt();
            }
            printf("%X in base %d reversed is %X digits\xA ",number,base,number_reversal(number,base));
            subprompt();
            buffer_cleaner();
            return 0;
        }
        else {
            printf("Wrong process input restarting the prompt\xA");
            prompt();
            buffer_cleaner();
            return 0;
        }


    }


}
int input_control_prompt(){
    buffer_cleaner();
    char answer;
    printf("Are you sure that you have entered number 0 yes(y) or no(n):");
    scanf("%c",&answer);
    if(answer=='y'){
        printf("No problem then\xA");
        return 0;
    }
    else if(answer=='n'){
        printf("Restarting the prompt\xA");
        prompt();
        buffer_cleaner();
        return 0;
    }
    else{
        printf("No applicable input restarting the control sequence");
        input_control_prompt();
        buffer_cleaner();
        return 0;
    }
}
int subprompt(){
    buffer_cleaner();
    char answer=0;
    printf("Want to continue to operations ? yes(y) or no(n)\xA");
    scanf("%c",&answer);
    if(answer=='y'){
        prompt();
        buffer_cleaner();
        return 0;
    }
    else if(answer=='n'){
        return 0;
    }
    else{
        printf("Unexpected input restarting the subprompt sequence\xA");
        subprompt();
        buffer_cleaner();
        return 0;
    }
}
void buffer_cleaner(){
    int c;
    while((c=getchar())!='\n' && c!=-1)
        continue;
}
int main(void){
    prompt();
}