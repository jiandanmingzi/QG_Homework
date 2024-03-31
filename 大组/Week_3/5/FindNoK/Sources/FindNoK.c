#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

int FindNoK(int* arr, int left, int right, int k)
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
    if (LNode == (k-1))
        return arr[LNode];
    else if (LNode < (k - 1))
        return FindNoK(arr, LNode + 1, right, k);
    else
        return FindNoK(arr, left, LNode - 1, k);
}

int main()
{
    int n = 0, flag = 0, k, answer;
    printf("请输入要生成的数组的数据量(不超过 200000 ,超过 6 位部分自动清除):");
    while (flag == 0)
    {
        NumInput(&n, 7);
        if (n > 200000)
            printf("输入错误，请重新输入:\n");
        else
            flag = 1;
    }
    srand((unsigned int)time(NULL));
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (n*10);
    }
    printf("排序前的数组为:\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n请输入要查找的第 k 大的数:\n");
    while (flag==1)
    {
        NumInput(&k, 7);
        if (k<1 || k>n)
            printf("请正确输入\n");
        else 
            flag = 0;
    }
    /*if (n == k)
        answer = arr[n-1];
    else*/
        answer = FindNoK(arr, 0, n - 1, k);
    printf("第 %d 大的数为: %d\n", k, answer);
    system("pause");
    return 0;
}