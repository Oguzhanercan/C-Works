#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define charlimit 100
#define lenght 100

typedef struct ad{
    int starttime;
    int duration;
    int cost;
    int th;
} AD;


void bublesort(AD *points, int s){ // this function sorts the structs by AD.starttime + AD.duration
    int i, j;
    AD temp;
    
        for (i=0;i<s-1;i++)
        {
            for (j=0;j<(s-1-i);j++)
            {
                if (points[j].starttime+points[j].duration> points[j + 1].duration+points[j+1].starttime)
                {
                    temp = points[j];
                    points[j] = points[j + 1];
                    points[j + 1] = temp;
                } 
            }
        }
    
    

}




int find_max(int arg1,int arg2){ // Returns the maximum argument
    if(arg1>arg2){
        return arg1;
    }
    return arg2;
}





int find_place(AD* ads,int n, int value){ //this function finds the last index that does not intersection between the start time of sample that we interested with finishing times of structed array sorted by finishing time 
    register int i = n-1;
    int flag = 0;
    while (i > -1 && flag == 0){
        
        if(ads[i].starttime + ads[i].duration <= value ){
            return i;

        }
         i--;
    }

    return -1;
}

void intersection(AD* ads,int n,int* first_intersection){ //initiliaze the value of intersection array according to intersections
    register int i;
    for(i = 0; i< n ; i++){
        first_intersection[i] = find_place(ads,n,ads[i].starttime);
    }

}

int recursive(AD* ads,int n,int index,int* results,int* first_intersection){ // calculates the profit recursively and returns
    if (index == -1){
        
        return 0;
    }
    else if(index > -1 && results[index] != -1){
        return results[index];
    }
    else{
        int idx_o = recursive(ads,n,first_intersection[index],results,first_intersection);
        int idx_o_m = recursive(ads,n,index-1,results,first_intersection);
        return find_max(ads[index].cost+idx_o,idx_o_m);
    }

}

void algo(AD* ads,int n, int* results,int* first_intersection){ // calls the recursive function for all indexes
    register int i;
    for(i =0;i<n;i++){
        results[i] = recursive(ads,n,i,results,first_intersection);
    
    }
}



FILE *fileopen(char *filename, char *x) // opens the txt file that contains samples and returns file pointer
{
    FILE *fp; // file pointer
    fp = fopen(filename, x);
    if (!fp)
    {
        printf("The file could not be opened, program will be closed...");
        exit(0);
    }
    return fp;
}


int read_point(char *path, AD *ads) // reads the points from txt file to struct array and returns the lenght of array.
{
    char *token; // storage the return value of strtok
    FILE *fp;
    fp = fileopen(path, "r");
    char *buffer = (char *)malloc(charlimit * sizeof(char)); // storage the return value of fgets
    register int i = 0;
    while (fgets(buffer, charlimit, fp) != NULL)
    {
        token = strtok(buffer, " ");
        ads[i].starttime = atoi(token);
        token = strtok(NULL, " ");
        ads[i].duration = atoi(token);
        token = strtok(NULL, " ");
        ads[i].cost = atoi(token);
        ads[i].th = i;
        i++;
    }
    fclose(fp);
    free(buffer);
    return i; // i equals lenght + 1
}

int back_track(AD *ads,int n,int index,int* results,int* first_intersection,AD *back,int i){ // back tracks the samples taken for best profit
    if (index == -1){
        return i;
    }
    else{
        if(ads[index].cost + recursive(ads,n,first_intersection[index],results,first_intersection) > results[index-1] ){
            back[i] = ads[i];
            i++;
            back_track(ads,n,first_intersection[index],results,first_intersection,back,i);
            
        }
        else{
            back_track(ads,n,index-1,results,first_intersection,back,i);
        }
    }
    
}

int main(){
    printf("Looking for Sample.txt in the same directory, please put it in same directory if you get error.... Start...\n");
    int n; // len of arrays
    register int i;
    AD *ads = (AD*)malloc(lenght*sizeof(AD)); // struct array for samples
    AD *back = (AD*)malloc(lenght*sizeof(AD)); // struct arrays for sapmles taken for best profit
    char path[charlimit] = "Sample.txt";     // path to txt file
    n = read_point(path,ads);
    int *first_intersection =  (int*)malloc(n*sizeof(int)); // storage the last non intersections
    int *results = (int*)malloc(n*sizeof(int)); // results for best profits
    for(i = 0;i<n;i++){
        results[i] = -1;
    }
    /*   terminal version for entering the values 
    for(i = 0 ; i <AD *ads = (AD*)malloc(lenght*sizeof(AD)); n ; i++){
        printf("\nstart time of %d . ad",i+1);
        scanf("%d",&ads[i].starttime);
        printf("\nduration of %d . ad",i+1);
        scanf("%d",&ads[i].duration);
        printf("\ncost of %d . ad",i+1);
        scanf("%d",&ads[i].cost);
    }*/
    printf("Ads taken, calculating best profit... \n \n");
    bublesort(ads,n);
    intersection(ads,n,first_intersection);
    
    algo(ads,n,results,first_intersection);
    int k = 0;
    k = back_track(ads,n,n-1,results,first_intersection,back,k);
    printf("Best profit : %d \nThe ads are : ",results[n-1]);
    for(i = 0 ; i< k ; i++){
        
        printf("%d ",back[i].th+1);
    }
    free(ads);
    free(back);
    free(first_intersection);
    free(results);
    return 0;
}