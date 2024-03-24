#include "queue.h"

int main()
{
    struct Queue* QueueList[10];
    struct Queue* now = NULL;
    int flag = 0, QueueNum = 0, NowNo = 0;
    char line[3], ch;
    for (size_t i = 0; i < 10; i++)
        QueueList[i] = NULL;
    printf("链式队列(仅演示字符串类型数据):\n输入:\n 1->展示当前所有队列\n 2->新建队列\n 3->选择队列\n 4->当前队列从尾加节点\n 5->当前队列获取头节点数据\n 6->当前队列弹出头节点\n 7->当前队列长度\n 8->清空当前队列\n9->退出系统\n\n当前: ");
    if (now == NULL)
        printf("未指定队列\n\n");
    else
        printf("%d 号队列\n\n", QueueNum);
    while (flag != 9)
    {
        fgets(line, 3, stdin);
        // system("cls");
        fflush(stdin);
        printf("链式队列(仅演示字符串类型数据):\n输入:\n 1->展示当前所有队列\n 2->新建队列(队列总数不可大于10)\n 3->选择队列\n 4->当前队列从尾加节点\n 5->当前队列获取头节点数据\n 6->当前队列弹出头节点\n 7->当前队列长度\n 8->清空当前队列\n9->退出系统\n\n当前: ");
        if (now == NULL)
            printf("未指定队列\n\n");
        else
            printf("%d 号队列\n\n", QueueNum);
        if (((line[1] == '\0') || (line[1] == '\n')) && (line[0] <= '9') && line[0] >= '1')
            flag = line[0] - '0';
        else
        {
            flag = 0;
            printf("请正确输入!\n");
        }
        if (flag == 1)
        {
            if (QueueNum == 0)
                printf("当前无队列");
            else
            {
                printf("当前共 %d 条队列", QueueNum);
                for (size_t i = 0; i < QueueNum; i++)
                    printf("%d 号队列: %s 容量为 %d 个节点 当前占用 %d 个节点\n", i + 1, QueueList[i]->queueName, QueueList[i]->capacity, QueueList[i]->size);
            }
        }
        else if (flag == 2)
        {
            if (QueueNum < 10)
            {
                printf("当前正在创建 %d 号链表\n请输入链表名(不超过19个字符,多余字符将自动清除):\n", QueueNum + 1);
                char name[20];
                fgets(name, 20, stdin);
                fflush(stdin);
                printf("请输入队列容量(不超过2位数,不可为0):\n");
                char check = 1, capacity[4];
                int num;
                do
                {
                    check = 1;
                    fgets(capacity, 4, stdin);
                    fflush(stdin);
                    for (int cnt = 0; cnt < 2; cnt++)
                        if ((capacity[cnt] < '0') || (capacity[cnt] > '9'))
                            check = 0;
                    if (((capacity[2] == '\0') || (capacity[2] == '\n')) && (capacity[0] >= '0') && (capacity[0] <= '9') && (capacity[1] <= '9') && (capacity[1] >= '0'))
                        num = (capacity[0] - '0') * 10 + (capacity[1] - '0');
                    else if (((capacity[1] == '\0') || (capacity[1] == '\n')) && (capacity[0] <= '9') && capacity[0] >= '1')
                        num = capacity[0] - '0';
                    else
                        check = 0;
                    if ((check == 0) || (num == 0))
                    {
                        check = 0;
                        printf("请正确输入!\n");
                    }
                } while (!check);
                now = initQueue(num, name);
                if (now != NULL)
                {
                    QueueList[QueueNum] = now;
                    QueueNum++;
                    NowNo = QueueNum;
                }
                else
                    printf("创建失败");
            }
            else
                printf("无法创建队列");
        }
        else if (flag == 3)
        {
            if (QueueNum)
            {
                char line[4];
                int flag = 1, check = 0;
                do
                {
                    printf("请输入要选择的队列的编号:\n");
                    fgets(line, 4, stdin);
                    fflush(stdin);
                    check = 1;
                    if (((line[2] == '\0') || (line[2] == '\n')) && (line[0] == '1') && (line[1] == '0'))
                        flag = 10;
                    else if (((line[1] == '\0') || (line[1] == '\n')) && (line[0] <= '9') && line[0] >= '1')
                        flag = line[0] - '0';
                    else
                        check = 0;
                    if (!check)
                        printf("请正确输入!\n");
                } while (!check);
                if (QueueList[flag - 1] != NULL)
                    now = QueueList[flag - 1];
                else
                    printf("当前暂无号数为: %d 的队列", flag);
            }
            else
                printf("当前无队列");
        }
        else if (flag == 4)
        {
            if (now != NULL)
            {
                printf("请输入需要添加的数据(不超过20个字符):\n");
                char* name = (char*)malloc(21 * sizeof(char));
                fgets(name, 21, stdin);
                fflush(stdin);
                if (addNode(now, name))
                    printf("添加成功\n");
                else
                    printf("添加失败");
            }
            else
                printf("当前未指定链表");
        }
        else if (flag == 5)
        {
            char* data = getData(now);
            if (data != NULL)
                printf("头节点数据为:%s\n", data);
            else
                printf("获取失败！\n");
        }
        else if (flag == 6)
        {
            char* data = getNode(now);
            if (data != NULL)
                printf("头节点数据为:%s\n", data);
            else
                printf("获取失败！\n");
        }
        else if (flag == 7)
        {
            if (now != NULL)
                printf("当前队列长%d", now->size);
            else
                printf("当前未指定队列");
        }
        else if (flag == 8)
        {
            if (now != NULL)
                if (cleanQueue(now))
                {
                    printf("清除成功\n");
                    now = NULL;
                    for (int i = NowNo; i < QueueNum; i++)
                        QueueList[i - 1] = QueueList[i];
                    QueueNum--;
                    QueueList[QueueNum] = NULL;
                }
                else
                    printf("清除失败\n");
            else
                printf("当前未指定队列");
        }
        printf("\n继续输入:\n");
    }
    return 0;
}