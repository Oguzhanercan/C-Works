// imagine that there is 2D area that contains some coins at some coordinates, the mission of robot is collecting maximum coin by moving right or down only.
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
    register int j;
    int x,y;
    int x_axis;
    int y_axis;
    int coin_number;
    printf("enter the len of x axis ");
    scanf("%d",&x_axis);
    printf("\nenter the len of y axis");
    scanf("%d",&y_axis);
    printf("\nenter the number of coins");
    scanf("%d",&coin_number);


    int** area = (int **)malloc((x_axis)*sizeof(int *));
    
    
    for(i = 0; i<x_axis;i++){
        area[i] = (int *)calloc(y_axis, sizeof(int));
    }

    for(i = 0;i<coin_number;i++){
        printf("\nenter the x and y values of coin in the following format x y : ");
        scanf("%d %d",&x,&y);
        area[x][y] = 1;
    }


    int** matrix = (int **)malloc((x_axis )*sizeof(int *));
    for(i = 0; i<x_axis+1;i++){
        matrix[i] = (int *)malloc((y_axis) * sizeof(int));
    }
    
    for(i = 0; i< y_axis; i++){
        if(area[0][i]==0){
            matrix[0][i] = 0;}
        else{
            matrix[0][i] = 1;
        }
    }
    
    for(i = 0;i<x_axis;i++){
         if(area[i][0]==0){
            matrix[i][0] = 0;}
        else{
            matrix[i][0] = 1;
        }
    }
    
    for(i = 1;i<x_axis;i++){
        for(j = 1;j<y_axis;j++){
            if(area[i][j] != 1){
                matrix[i][j] = find_max(matrix[i-1][j],matrix[i][j-1]);
            }
            else{
                matrix[i][j] = find_max(matrix[i-1][j]+1,matrix[i][j-1]+1);
            }
        }
    }
    for(i = 0; i< x_axis;i++){
        for(j = 0; j<y_axis;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }


    return 0;
}
