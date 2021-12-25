// knapsack problem, pick the optimal items that maximize total value. Limitation is that every item has a weight; total weight cannot be bigger then a constant N
#include <stdio.h>
#include <stdlib.h>

typedef struct item{
    int value;
    int weight;
}ITEM;

int find_max(int arg1,int arg2){ // Returns the maximum argument
    if(arg1>arg2){
        return arg1;
    }
    return arg2;
}

int main(){
    register int i;
    register int j;
    int max_weight;
    int num_items;

    printf("enter the max weight: ");
    scanf("%d",&max_weight);
    printf("\nenter the number of items");
    scanf("%d",&num_items);
    int** matrix = (int **)malloc((num_items + 1)*sizeof(int *));
    
    
    for(i = 0; i<num_items+1;i++){
        matrix[i] = (int *)malloc((max_weight+1) * sizeof(int));
    }
    
    for(i = 0; i< max_weight+1; i++){
        matrix[0][i] = 0;
    }
    
    for(i = 0;i<num_items+1;i++){
        matrix[i][0] = 0;
    }
    
    ITEM *items = (ITEM *)malloc(num_items*sizeof(ITEM));
    for(i = 0; i<num_items;i++){
        printf("\nenter the value of %d. item: ",i);
        scanf("%d",&items[i].value);
        printf("\nenter the weight of %d. item: ",i);
        scanf("%d",&items[i].weight);
    }
  
    for(i = 1;i<num_items+1;i++){
        for(j = 1;j<max_weight+1;j++){
            if(items[i-1].weight > j){
                matrix[i][j] = matrix[i-1][j];
            }
            else{
                matrix[i][j] = find_max(matrix[i-1][j-items[i-1].weight]+items[i-1].value,matrix[i-1][j]);
            }
        }
    }
    for(i = 0; i< num_items+1;i++){
        for(j = 0; j<max_weight+1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }


    printf("%d",matrix[num_items][max_weight]);

    //backtracking for finding that wich items selected,,,,,,,,,, there is a problem due to indexing solve it
    int *array = (int*)calloc(num_items,sizeof(int));
    j = 0;
    printf("%d",items[num_items].value);
    while(items[num_items-1].value!= 0){
        printf("sex but bruh");
        if(matrix[num_items][max_weight] > matrix[num_items-1][max_weight]){
            printf("sex");
            array[j] = num_items;
            max_weight -= items[num_items].weight;
            num_items--;
            j++;
        }
        else{
            num_items -= 1;
        }
    }
    for(i = 0; i<j;i++){
        printf("alooo ha %d",array[i]);
    }

    return 0;
}
