#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int DataFormer(int n)
{
    FILE* file;
    file = fopen("numbers.txt", "w");
    if (file != NULL)
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n; i++)
            fprintf(file, "%d ", rand() % 1000000);
        fclose(file);
    }
    else
        return 0;
}

int main()
{
    char temp[7], flag = 0;
    int n;
    printf("请输入要生成的数组的数据量(不超过200000,超过6位部分自动清除):");
    while (flag == 0)
    {
        fgets(temp, 7, stdin);
        fflush(stdin);
        if (atoi(temp))
        {
            n = atoi(temp);
            if (n > 200000)
                printf("请不要超过200000\n");
            else
                flag = 1;
            if (flag == 1)
                printf("生成成功\n");
        }
        else
            printf("请正确输入\n");
    }
    DataFormer(n);
    system("pause");
    return 0;
}