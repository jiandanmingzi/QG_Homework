#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Timer.h"
#include "Sort.h"

int main()
{
    int time, numbers[4] = { 100, 10000, 50000, 200000 }, times = 100000;
    struct Sort sorts[7] = {
        {"冒泡排序", BubbleSort},
        {"计数排序", CountSort},
        {"插入排序", InsertSort},
        {"归并排序", MergeSort},
        {"递归快速排序", RQuickSort},
        {"非递归快速排序", NonRecirsopmQuickSort},
        {"基数排序", RadixSort} };
    for (int Nnums = 1; Nnums <= 3; Nnums++)
    {
        for (int Snums = 0; Snums < 7; Snums++)
        {
            time = SingleDataTest(sorts[Snums].sort, numbers[Nnums]);
            printf("%s : %d 个数据耗时: %d ms\n", sorts[Snums].name, numbers[Nnums], time);
        }
    }
    for (int Snums = 0; Snums < 7; Snums++)
    {
        time = MultipleDataTest(sorts[Snums].sort, numbers[0], times);
        printf("%s : %d 个数据运行 %d 次耗时: %d ms\n", sorts[Snums].name, numbers[0], times, time);
    }
    system("pause");
    return 0;
}