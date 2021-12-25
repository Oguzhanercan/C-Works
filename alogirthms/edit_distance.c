// Consider that there are 2 arrays, find the distance between these arrays
#include <stdio.h>
#include <stdlib.h>


int find_min3(int arg1,int arg2,int arg3){ // Returns the min argument
    if(arg1<arg2){
        if(arg1<arg3){
        return arg1;}
        else{
            return arg3;
        }
    }
    return arg2;
}

int main(){
    register int i;
    register int j;
    int len_first;
    int len_second;
    
    printf("enter the len of first array ");
    scanf("%d",&len_first);
    printf("\nenter the len of second array");
    scanf("%d",&len_second);
    
    int* first_array = (int*)malloc(len_first*sizeof(int));
    int* second_array = (int*)malloc(len_second*sizeof(int));
    for(i = 0; i<len_first;i++){
        printf("\nenter the %d. element of first array: ");
        scanf("%d",&first_array[i]);
    }
    for(i = 0; i<len_second;i++){
        printf("\nenter the %d. element of second array: ");
        scanf("%d",&second_array[i]);
    }


    int** matrix = (int **)malloc((len_first +1 )*sizeof(int *));
    
    
    for(i = 0; i<len_first+1;i++){
        matrix[i] = (int *)malloc((len_second+1)* sizeof(int));
    }

    for(i = 0; i<len_second+1; i++){
        matrix[0][i] = i;
    }

    for(i = 0; i<len_first+1; i++){
        matrix[i][0] = i;
    }
    

    for(i = 1;i<len_first+1;i++){
        for(j = 1;j<len_second+1;j++){
            if(first_array[i] == second_array[j]){
                matrix[i][j] = matrix[i-1][j-1];
            }
            else{
                matrix[i][j] = find_min3(matrix[i][j-1],matrix[i-1][j-1],matrix[i-1][j])+1;
            }
        }
    }
    for(i = 0; i< len_first+1;i++){
        for(j = 0; j<len_second+1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }


    return 0;
}
