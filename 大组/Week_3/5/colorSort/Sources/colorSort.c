#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void colorSort(int* nums, int numsSize)
{
    int p0 = 0, p2 = numsSize - 1;
    for (int p1 = 0; p1 <= p2; p1++)
    {
        while (nums[p2] == 2)
            p2--;

        while (nums[p0] == 2)
            p0++;

        while (nums[p1] != 1)
        {
            if (nums[p1] == 0)
            {
                swap(&nums[p0], &nums[p1]);
                p0++;
            }
            else
            {
                swap(&nums[p1], &nums[p2]);
                p2--;
            }
        }
    }
}

void NumInput(int* num, int cnt)
{
    char* temp = (char*)malloc(cnt * sizeof(char)), flag = 0;
    *num = 0;
    while (flag == 0)
    {
        fgets(temp, cnt, stdin);
        rewind(stdin);
        flag = 1;
        for (int i = 0; (temp[i] != '\0' && temp[i] != '\n'); i++)
        {
            if (temp[i] < '0' || temp[i] > '9')
            {
                printf("输入错误，请重新输入:\n");
                flag = 0;
                break;
            }
            else
                *num = *num * 10 + temp[i] - '0';
        }
    }
}

int main()
{
    int n = 0, flag = 0;
    printf("请输入要排序的数组的数据量(不超过 200000 ,超过 6 位部分自动清除):\n");
    while (flag == 0)
    {
        NumInput(&n, 7);
        if (n > 200000)
            printf("输入错误，请重新输入:\n");
        else
            flag = 1;
    }
    int* nums = (int*)malloc(n * sizeof(int));
    printf("请输入要排序的数组:\n");
    for (int i = 0; i < n; i++)
    {
        flag = 1;
        printf("请输入第 %d 个数:", i + 1);
        while (flag)
        {
            NumInput(&nums[i], 2);
            if (nums[i] < 0 || nums[i] > 2)
                printf("输入错误，请重新输入:\n");
            else
                flag = 0;
        }
    }
    colorSort(nums, n);
    printf("排序后的数组为:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", nums[i]);
    return 0;
}