
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define asize(array) ((sizeof(array))/(sizeof(array[0])))
#define var_switch(type,var1,var2) do{type temp=var1;var1=var2;var2=temp;}while(0)
#define print_array(array)  for(int i=0;i<asize(array);i++) printf("%d\040",array[i]); printf("\xA")
int main(void){

	srand((unsigned)time(NULL));

	int a[12]={0};



	for(int i=0;i<sizeof(a)/sizeof(int);i++){
		a[i]=rand()%100;
	}

	print_array(a);

	for(int repeat=0;repeat<asize(a) -1;++repeat){
		for(int index=0;index<asize(a)-1-repeat;++index){
			if((a[index] + a[index+1])%2!=0){
				if(a[index]%2!=0){
					var_switch(int,a[index],a[index+1]);
				}


			}
			else if(a[index]>a[index+1]){
					var_switch(int,a[index],a[index+1]);
			}
		}
	}

	print_array(a);


}