#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Sorts.h"
#include "Timer.h"
int ReadData(int** arr)
{
    FILE* file;
    file = fopen("numbers.txt", "r");
    if (file != NULL)
    {
        int* numbers = NULL;
        int count = 0;
        int number;
        while (fscanf(file, "%d", &number) == 1)
        {
            int* temp = realloc(numbers, sizeof(int) * (count + 1));
            if (temp == NULL)
            {
                if (numbers != NULL)
                    free(numbers);
                fclose(file);
                return 0;
            }
            numbers = temp;
            numbers[count] = number;
            count++;
        }
        fclose(file);
        *arr = numbers;
        return count;
    }
    else
        return 0;
}
int main()
{
    struct Sort sorts[7] = {
    {"冒泡排序", BubbleSort},
    {"计数排序", CountSort},
    {"插入排序", InsertSort},
    {"归并排序", MergeSort},
    {"递归快速排序", RQuickSort},
    {"非递归快速排序", NonRecirsopmQuickSort},
    {"基数排序", RadixSort} };
    int* arr;
    int n = ReadData(&arr);
    if (n != 0)
    {
        int* temp = (int*)malloc(n * sizeof(int));
        if (temp != NULL) {
            int time;
            for (int Snums = 0; Snums < 7; Snums++)
            {
                for (int i = 0; i < n; i++)
                    temp[i] = arr[i];
                time = GetTime(sorts[Snums].sort,temp ,n);
                printf("%s : %d 个数据耗时: %d ms\n", sorts[Snums].name, n, time);
            }
            free(temp);
        }
    }
    else
        printf("读取失败\n");
    return 0;
}