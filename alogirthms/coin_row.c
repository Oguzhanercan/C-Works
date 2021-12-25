//coin row problem, the limitation is that: if you pick i. coin you cannot pick i+1. coin

#include <stdio.h>
#include <stdlib.h>

int find_max(int arg1,int arg2){ // Returns the maximum argument
    if(arg1>arg2){
        return arg1;
    }
    return arg2;
}

int main(){
    register int i;
    int n;
    printf("enter the number of coins");
    scanf("%d",&n);

    int *array = (int *)malloc(n*sizeof(int));
    int *gain = (int *)malloc((n+1)*sizeof(int));
    for(i = 0; i<n; i++){
        printf("enter the %d. coin gain : \n",i);
        scanf("%d",&array[i]);
    }

    gain[0] = 0;
    gain[1] = array[0];

    for(i = 1;i<n;i++ ){
        gain[i+1] = find_max(array[i]+gain[i-1],gain[i]);
    }
    printf("%d",gain[n]);
    free(array);
    free(gain);
    return 0;
}   



