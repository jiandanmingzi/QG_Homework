#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

// 冒泡排序
void BubbleSort(int *arr, int n)
{
    int temp, flag, right = n - 1, left = 0;
    while (left < right)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                flag = 1;
            }
        }
        left++;
        if (flag == 0)
            break;
    }
}

// 计数排序
void CountSort(int *arr, int n)
{
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    int *count = (int *)malloc((max + 1 - min) * sizeof(int));
    if (count != NULL)
    {
        for (int i = 0; i <= max - min; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[arr[i] - min]++;
        for (int i = 1; i <= max - min; i++)
            count[i] += count[i - 1];
        int *temp = (int *)malloc(n * sizeof(int));
        if (temp != NULL)
        {
            for (int i = n - 1; i >= 0; i--)
            {
                temp[count[arr[i] - min] - 1] = arr[i];
                count[arr[i] - min]--;
            }
            for (int i = 0; i < n; i++)
                arr[i] = temp[i];
            free(temp);
        }
        else
            printf("Error\n");
        free(count);
    }
    else
        printf("Error\n");
}

// 插入排序
void InsertSort(int *arr, int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

//--------------------------------------------------
// 归并排序
void Merge(int *arr, int *temp, int left, int right)
{
    int mid = (left + right) / 2;
    int LNode = left, RNode = mid + 1, NowNode = left;
    while (LNode <= mid && RNode <= right)
    {
        if (arr[LNode] < arr[RNode])
            temp[NowNode++] = arr[LNode++];
        else
            temp[NowNode++] = arr[RNode++];
    }

    while (LNode <= mid)
        temp[NowNode++] = arr[LNode++];

    while (RNode <= right)
        temp[NowNode++] = arr[RNode++];

    for (NowNode = left; NowNode <= right; NowNode++)
        arr[NowNode] = temp[NowNode];
}

void Divde(int *arr, int *temp, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        Divde(arr, temp, left, mid);
        Divde(arr, temp, mid + 1, right);
        Merge(arr, temp, left, right);
    }
}

void MergeSort(int *arr, int n)
{
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp != NULL)
    {
        Divde(arr, temp, 0, n - 1);
        free(temp);
    }
    else
        printf("Error\n");
}
//-----------------------------------------

// 递归版快速排序
void recursionQuickSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int LNode, RNode, temp;
        LNode = left;
        RNode = right;
        temp = arr[left];
        while (LNode < RNode)
        {
            while (LNode < RNode && arr[RNode] >= temp)
                RNode--;
            if (LNode < RNode)
            {
                arr[LNode] = arr[RNode];
                LNode++;
            }
            while (LNode < RNode && arr[LNode] < temp)
                LNode++;
            if (LNode < RNode)
            {
                arr[RNode] = arr[LNode];
                RNode--;
            }
        }
        arr[LNode] = temp;
        recursionQuickSort(arr, left, LNode - 1);
        recursionQuickSort(arr, LNode + 1, right);
    }
}

// 递归版快速排序随机取轴优化
void recursionQuickSortRandom(int *arr, int left, int right)
{
    if (left < right)
    {
        int LNode, RNode, temp, pivot;
        pivot = rand() % (right - left + 1) + left;
        temp = arr[left];
        arr[left] = arr[pivot];
        arr[pivot] = temp;
        LNode = left;
        RNode = right;
        temp = arr[left];
        while (LNode < RNode)
        {
            while (LNode < RNode && arr[RNode] >= temp)
                RNode--;
            if (LNode < RNode)
            {
                arr[LNode] = arr[RNode];
                LNode++;
            }
            while (LNode < RNode && arr[LNode] < temp)
                LNode++;
            if (LNode < RNode)
            {
                arr[RNode] = arr[LNode];
                RNode--;
            }
        }
        arr[LNode] = temp;
        recursionQuickSortRandom(arr, left, LNode - 1);
        recursionQuickSortRandom(arr, LNode + 1, right);
    }
}

// 递归版快速排序三枢轴优化
void recursionQuickSortThree(int *arr, int left, int right)
{
    if (left < right)
    {
        int LNode, RNode, temp, pivot1, pivot2;
        pivot1 = rand() % (right - left + 1) + left;
        pivot2 = rand() % (right - left + 1) + left;
        if (arr[pivot1] > arr[pivot2])
        {
            temp = pivot1;
            pivot1 = pivot2;
            pivot2 = temp;
        }
        temp = arr[left];
        arr[left] = arr[pivot1];
        arr[pivot1] = temp;
        temp = arr[right];
        arr[right] = arr[pivot2];
        arr[pivot2] = temp;
        LNode = left;
        RNode = right;
        temp = arr[left];
        while (LNode < RNode)
        {
            while (LNode < RNode && arr[RNode] >= temp)
                RNode--;
            if (LNode < RNode)
            {
                arr[LNode] = arr[RNode];
                LNode++;
            }
            while (LNode < RNode && arr[LNode] < temp)
                LNode++;
            if (LNode < RNode)
            {
                arr[RNode] = arr[LNode];
                RNode--;
            }
        }
        arr[LNode] = temp;
        recursionQuickSortThree(arr, left, LNode - 1);
        recursionQuickSortThree(arr, LNode + 1, right);
    }
}

// 入口
void RQuickSort(int *arr, int n)
{
    recursionQuickSort(arr, 0, n - 1);
}

void RQuickSortR(int *arr, int n)
{
    recursionQuickSortRandom(arr, 0, n - 1);
}

void RQuickSortT(int *arr, int n)
{
    recursionQuickSortThree(arr, 0, n - 1);
}

// 非递归版快速排序
void NonRecirsopmQuickSort(int *arr, int n)
{
    int *stack = (int *)malloc(n * sizeof(int));
    if (stack != NULL)
    {
        int top = -1, left, right, LNode, RNode, temp;
        top++;
        stack[top] = 0;
        top++;
        stack[top] = n - 1;
        while (top != -1)
        {
            right = stack[top];
            top--;
            left = stack[top];
            top--;
            LNode = left;
            RNode = right;
            temp = arr[left];
            while (LNode < RNode)
            {
                while (LNode < RNode && arr[RNode] >= temp)
                    RNode--;
                if (LNode < RNode)
                {
                    arr[LNode] = arr[RNode];
                    LNode++;
                }
                while (LNode < RNode && arr[LNode] < temp)
                    LNode++;
                if (LNode < RNode)
                {
                    arr[RNode] = arr[LNode];
                    RNode--;
                }
            }
            arr[LNode] = temp;
            if (left < LNode - 1)
            {
                top++;
                stack[top] = left;
                top++;
                stack[top] = LNode - 1;
            }
            if (LNode + 1 < right)
            {
                top++;
                stack[top] = LNode + 1;
                top++;
                stack[top] = right;
            }
        }
        free(stack);
    }
    else
        printf("Error\n");
}

// 基数排序
void RadixSort(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    int *count = (int *)malloc(10 * sizeof(int));
    if (count != NULL)
    {
        int *temp = (int *)malloc(n * sizeof(int));
        if (temp != NULL)
        {
            int exp = 1;
            while (max / exp > 0)
            {
                for (int i = 0; i < 10; i++)
                    count[i] = 0;
                for (int i = 0; i < n; i++)
                    count[arr[i] / exp % 10]++;
                for (int i = 1; i < 10; i++)
                    count[i] += count[i - 1];
                for (int i = n - 1; i >= 0; i--)
                {
                    temp[count[arr[i] / exp % 10] - 1] = arr[i];
                    count[arr[i] / exp % 10]--;
                }
                for (int i = 0; i < n; i++)
                    arr[i] = temp[i];
                exp *= 10;
            }
            free(temp);
        }
        else
            printf("Error\n");
        free(count);
    }
    else
        printf("Error\n");
}