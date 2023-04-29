#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE (20)
#define LESS (100)
#define asize(arr) (sizeof(arr)/sizeof(arr[0]))
#define print_array(arr) printf("{"); for(int i_##arr=0;i_##arr<asize(arr);i_##arr++) printf("%d,",arr[i_##arr]); printf("}\n")
#define swap_couple(type,a,b) do{type temp=a;a=b;b=temp;}while(0)
#define randomize() (srand((unsigned)(time)(NULL)))
#define give_random_values(arr,less_than) for(int i_##arr=0;i_##arr<asize(arr);i_##arr++) arr[i_##arr]=rand() % less_than
int main(void){
	randomize();

	int b[SIZE]={0};
	int rand_init=rand()%LESS;
	for(int i=0;i<SIZE;i++){
		b[i]=rand_init;
	}
	int random_rep_break=0;
	int rep;
	int smallest_index=0;
	while((random_rep_break+=rep=rand()%(SIZE/2))<SIZE){
		int val=rand()%LESS;
		for(int i=0;i<rep;i++){
			b[smallest_index]=val;
			smallest_index++;
		}
	}

	print_array(b);
	int c[asize(b)]={0};


	int count=0;

	for(int i=0;i<asize(b);i++){
		int k;
		for(k=0;k<asize(b);k++){
			if(b[i]==c[k]){
				break;
			}
		}
		if(!(k<asize(b))){
			c[count]=b[i];
			count++;
		}
	}

	if(c[0]!=0 && c[asize(b)-1]==0){
		printf("{");
		for(int i=0;c[i]!=0;i++){
			printf("%d,",c[i]);
		}
		printf("}");
	}
}
