#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand((unsigned)(time)(NULL))

#define NUMBER_OF_MATCHES 10000000

void craps_win_odd_in_helper(long long *win_count,int *dice_sum,int *first_dice,int *second_dice){
    for(long long turn=0;;turn++){
        *first_dice=rand()%6+1;
        *second_dice=rand()%6+1;
        int prev_dice_sum=*dice_sum;
        *dice_sum=*first_dice+*second_dice;


        if((*dice_sum==7 || *dice_sum==11) && turn==0){
            (void)(*win_count)++;
            break;
        }
        else if((*dice_sum==2 || *dice_sum==3 || *dice_sum==12) && turn==0){
            break;
        }
        else if(prev_dice_sum==*dice_sum){
            (void)(*win_count)++;
            break;
        }
        else if(*dice_sum==7){
            break;
        }

    }
}

double craps_win_odd_in(long long matches){

    long long win_count=0;

    int first_dice=0;
    int second_dice=0;
    int dice_sum=0;

    for(int match=0;match<matches;match++){
        craps_win_odd_in_helper(&win_count,&dice_sum,&first_dice,&second_dice);
    }
    return (double)win_count/matches;
}

int main(void){
    randomize();
    printf("%lf",craps_win_odd_in(NUMBER_OF_MATCHES));
}