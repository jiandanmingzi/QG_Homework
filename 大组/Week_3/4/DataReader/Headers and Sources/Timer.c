#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int GetTime(void (*sort)(int*, int), int* arr, int n)
{
    clock_t start, end;
    start = clock();
    sort(arr, n);
    end = clock();
    return end - start;
}

int SingleDataTest(void (*sort)(int*, int), int n)
{
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr != NULL)
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 1000000;
        }
        int time = GetTime(sort, arr, n);
        free(arr);
        return time;
    }
    else
    {
        printf("Error\n");
        return -1;
    }
}

int MultipleDataTest(void (*sort)(int*, int), int n, int times)
{
    int sum = 0;
    for (int i = 0; i < times; i++)
        sum += SingleDataTest(sort, n);
    return sum;
}