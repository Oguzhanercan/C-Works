#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define lenght 100
#define size 200
#define charlimit 100
typedef struct point
{
    int x;
    int y;

} POINT;
FILE *fileopen(char *filename, char *x)
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

int read_point(char *path, POINT *points)
{
    char *token; // storage the return value of strtok
    FILE *fp;
    fp = fileopen(path, "r");
    char *buffer = (char *)malloc(charlimit * sizeof(char)); // storage the return value of fgets
    register int i = 0;
    while (fgets(buffer, charlimit, fp) != NULL)
    {
        token = strtok(buffer, " ");
        points[i].x = atoi(token);
        token = strtok(NULL, " ");
        points[i].y = atoi(token);
        i++;
    }
    fclose(fp);
    free(buffer);
    return i; // i equals lenght + 1
}

void swap(POINT *points, int index_1, int index_2)
{
    int tmp_x;
    int tmp_y;
    tmp_x = points[index_1].x;
    tmp_y = points[index_1].y;
    points[index_1].x = points[index_2].x;
    points[index_1].y = points[index_2].y;
    points[index_2].x = tmp_x;
    points[index_2].y = tmp_y;
}
int init_part(POINT *points, int p, int r)
{
    int x = p;
    register int i;
    for (i = p; i < r; i++)
    {
        if (points[i].x < points[r].x)
        {
            swap(points, i, x++);
        }
    }
    swap(points, x, r);
    return x;
}

void quick(POINT *points, int p, int r)
{
    if (p >= r)
    {
        return;
    }
    int q = init_part(points, p, r);
    quick(points, p, q - 1);
    quick(points, q + 1, r);
}
double squareRoot(double n)
{
    double i, precision = 0.00001;

    for (i = 1; i * i <= n; ++i)
        ;

    for (--i; i * i < n; i += precision)
        ;
    return i;
}

double squarePow(int n)
{
    double pow;
    pow = n * n;
    return pow;
}

double distance(POINT *points, int idx_1, int idx_2)
{
    double distance = squareRoot(squarePow(points[idx_1].x - points[idx_2].x) + squarePow(points[idx_1].y - points[idx_2].y));
    return distance;
}
int ceil_F(double n)
{
    int tmp;
    tmp = n;
    if (tmp < n)
    {
        return tmp + 1;
    }
    return tmp;
}

int floor_F(double n)
{
    return n;
}

double cpp(POINT *points, POINT *pair, int len, double min)
{
    double distance_array[3]; // it storage distances when we compare 3 points
    register int i;           // loop variable
    register int j;           // loop variable
    int mid;                  // median value
    int left_min;             // min value of left part of divided struct array
    int right_min;            // min value of left part of divided struct array
    double dist;              // to storage the distance

    if (len == 2)
    {

        if (distance(points, 0, 1) < min)
        {
            pair[0].x = points[0].x;
            pair[0].y = points[0].y;
            pair[1].x = points[1].x;
            pair[1].y = points[1].y;
        }
        return distance(points, 0, 1);
    }
    else if (len == 3)
    {
        distance_array[0] = distance(points, 0, 1);

        distance_array[1] = distance(points, 0, 2);

        distance_array[2] = distance(points, 1, 2);

        register int i;
        if (distance_array[0] < min)
        {
            min = distance_array[0];
            pair[0].x = points[0].x;
            pair[0].y = points[0].y;
            pair[1].x = points[1].x;
            pair[1].y = points[1].y;
        }

        if (distance_array[1] < min)
        {
            min = distance_array[1];
            pair[0].x = points[0].x;
            pair[0].y = points[0].y;
            pair[1].x = points[2].x;
            pair[1].y = points[2].y;
        }
        if (distance_array[2] < min)
        {
            min = distance_array[2];
            pair[0].x = points[1].x;
            pair[0].y = points[1].y;
            pair[1].x = points[2].x;
            pair[1].y = points[2].y;
        }

        return min;
    }
    POINT *points_left = (POINT *)malloc(floor_F((double)len / 2) * sizeof(POINT)); // left part of divided struct array
    POINT *points_right = (POINT *)malloc(ceil_F((double)len / 2) * sizeof(POINT)); // right part of divided struct array

    for (i = 0; i < floor_F(len / 2); i++)
    {
        points_left[i].x = points[i].x;
        points_left[i].y = points[i].y;
    }
    for (i = 0; i < ceil_F((double)len / 2); i++)
    {
        points_right[i].x = points[i + floor_F((double)len / 2)].x;
        points_right[i].y = points[i + floor_F((double)len / 2)].y;
    }


    left_min = cpp(points_left, pair, floor_F((double)len / 2), min);

    if (left_min < min)
    {
        min = left_min;
    }

    right_min = cpp(points_right, pair, ceil_F((double)len / 2), min);
    if (right_min < min)
    {
        min = right_min;
    }

    mid = points[floor_F((double)len / 2)].x;

    for (i = 0; i < len; i++)
    {
        if (points[i].x >= mid - min || points[i].x <= mid + min)
        {
            for (j = i + 1; j < len; j++)
            {
                if (points[j].x >= mid - min || points[j].x <= mid + min)
                {
                    dist = distance(points, i, j);

                    if (dist < min)
                    {
                        pair[0].x = points[i].x;
                        pair[0].y = points[i].y;
                        pair[1].x = points[j].x;
                        pair[1].y = points[j].y;
                        min = dist;
                    }
                }
            }
        }
    }
    free(points_left);
    free(points_right);
    return min;
}

int main()
{
    int len;                                                 // lenght of points
    double min = ULONG_MAX;                                  // it storage min value
    POINT *pair = (POINT *)malloc(2 * sizeof(POINT));        // pair storage the information of closest points
    POINT *points = (POINT *)malloc(lenght * sizeof(POINT)); // points read from txt file
    char path[charlimit] = "sample.txt";                     // path to file that includes coordinates of points
    printf("Welcome to the closest pair program, program will be read sample.txt file in the same directory with this program and then it will be finding cloesest points. Points represented in 2 dimensional space.");
    len = read_point(path, points);
    quick(points, 0, len - 1);
    min = cpp(points, pair, len, min);

    printf("The distance between closest points is : %f and the coordinates of point_1 -> x:%d y:%d, point_2 -> x:%d y:%d", min, pair[0].x, pair[0].y, pair[1].x, pair[1].y);

    free(points);
    free(pair);
    return 0;
}
