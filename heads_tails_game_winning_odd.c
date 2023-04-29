#include <stdio.h>
#define TAILS 0
#define HEADS 1
#define MATCHES 1000000




int a_turn(void){
    int randval;
    FILE *f;

    f= fopen("/dev/random","r");

    int player_money=100;
    int owner_money=100;
    int coin=-1;
    int prev_coin=-2;
    while(player_money>0 && owner_money>0) {
        fread(&randval,sizeof(randval),1,f);
        player_money -= 10;
        owner_money += 10;
        int prev_prev_coin=prev_coin;
        prev_coin=coin;
        coin = randval%2;

        if (coin == HEADS && coin==prev_coin && prev_prev_coin==coin)
            owner_money -= 60,player_money += 60;
        else if (coin == TAILS && coin==prev_coin)
            owner_money -= 30,player_money += 30;

    }

    fclose(f);
    if(player_money<=0)
        return 0;

    return 1;
}

double odd_of_winning(int matches){
    int wins=0;
    for(int i=0;i<matches;i++){
        wins+= a_turn();
    }
    return (double)wins/matches;
}

int main(void){

    

    printf("%lf\n", odd_of_winning(MATCHES));

    
}