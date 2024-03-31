#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int DataFormer(int n, int max, int min)
{
    FILE *file;
    file = fopen("numbers.txt", "w");
    if (file != NULL)
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n; i++)
            fprintf(file, "%d ", rand() % (max - min + 1) + min);
        fclose(file);
    }
    else
        return 0;
}

void NumInput(int *num, int cnt)
{
    char *temp = (char *)malloc(cnt * sizeof(char)), flag = 0;
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
    int n = 0, min = 0, max = 0, flag = 0;
    printf("请输入要生成的数组的数据量(不超过 200000 ,超过 6 位部分自动清除):");
    while (flag == 0)
    {
        NumInput(&n, 7);
        if (n > 200000)
            printf("输入错误，请重新输入:\n");
        else
            flag = 1;
    }
    flag = 0;
    while (flag == 0)
    {
        printf("请输入要生成的数组的最小值(不超过 7 位数,超过部分自动清除):");
        NumInput(&min, 7);
        printf("请输入要生成的数组的最大值(不超过 7 位数,超过部分自动清除):");
        NumInput(&max, 7);
        if (min > max)
            printf("输入错误，请重新输入:\n");
        else
            flag = 1;
    }
    DataFormer(n, max, min);
    printf("数据生成成功\n");
    system("pause");
    return 0;
}