#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SingleLinkedList.h" 
#include "SingleList.h"
int main()
{
    struct SingleListOp *Operater[10];
    struct SingleListOp *now = NULL;
    int flag = 0, ListNo = 0, TotalNo = 0;
    for (size_t i = 0; i < 10; i++)
        Operater[i] = NULL;
    printf("单向链表:\n输入:\n 1->展示当前所有链表\n 2->新建链表\n 3->选择链表\n 4->当前链表从尾加节点\n 5->当前链表插入节点\n 6->当前链表删除尾节点\n 7->当前链表删除指定节点\n 8->当前链表尾节点链接任意节点\n 9->当前链表判断是否成环\n10->当前链表表长\n11->当前链表根据内容获取节点位置\n12->当前链表展示指定节点内容\n13->当前链表奇偶节点互换\n14->当前链表展示中间节点\n15->当前链表展示所有节点\n16->清空当前链表\n17->非递归倒转当前链表\n18->递归倒转当前链表\n19->退出系统\n\n");
    printf("当前:  ");
    if (now == NULL)
        printf("未指定链表\n\n");
    else
        printf("%d 号链表\n\n", ListNo);
    int cnt;
    char data[20];
    char answer;
    int *locate = NULL;
    struct SingleList *temp = NULL;
    while (flag != 19)
    {
        scanf("%d", &flag);
        getchar();
        //system("cls");
        printf("单向链表:\n输入:\n 1->展示当前所有链表\n 2->新建链表\n 3->选择链表\n 4->当前链表从尾加节点\n 5->当前链表插入节点\n 6->当前链表删除尾节点\n 7->当前链表删除指定节点\n 8->当前链表尾节点链接任意节点\n 9->当前链表判断是否成环\n10->当前链表表长\n11->当前链表根据内容获取节点位置\n12->当前链表展示指定节点内容\n13->当前链表奇偶节点互换\n14->当前链表展示中间节点\n15->当前链表展示所有节点\n16->清空当前链表\n17->非递归倒转当前链表\n18->递归倒转当前链表\n19->退出系统\n\n");
        printf("当前:  ");
        if (now == NULL)
            printf("未指定链表\n\n");
        else
            printf("%d 号链表:%s\n\n", ListNo, now->head->Data);
        printf("\n");
        switch (flag)
        {
        case 1:
            if (Operater[0] == NULL)
            {
                printf("当前无链表.");
                break;
            }
            for (size_t i = 0; i < 50; i++)
            {
                if (Operater[i] != NULL)
                    printf("%d 号链表:%s\t", i + 1, Operater[i]->head->Data);
                else
                    break;
            }
            break;
        case 2:
            printf("当前正在创建%d号链表\n请输入链表名:\n", TotalNo + 1);
            scanf("%s", &data);
            now = CreatSingleList(data);
            if (now != NULL)
            {
                ListNo = TotalNo + 1;
                Operater[TotalNo] = now;
                TotalNo = ListNo;
                printf("创建成功!");
            }
            break;
        case 3:
            if (now != NULL)
            {
                int i;
                printf("请输入要选的链表的编号:\n");
                scanf("%d", &i);
                getchar();
                if (Operater[i - 1] != NULL)
                {
                    now = Operater[i - 1];
                    ListNo = i;
                    printf("选择成功");
                }
                else
                    printf("暂无标号为%d的链表", i);
            }
            else
                printf("当前未指定链表");
            break;
        case 4:
            if (now != NULL)
            {
                printf("请输入需要添加的节点的数据:\n");
                scanf("%s", &data);
                getchar();
                temp = AddFromEnd(now, data);
                if (temp != NULL)
                    printf("添加成功");
            }
            else
                printf("当前未指定链表");
            break;
        case 5:
            if (now != NULL)
            {
                printf("请输入节点插入的位置(头为1,尾为当前链表节点数+1)");
                scanf("%d", &cnt);
                getchar();
                printf("请输入需要添加的节点的数据:\n");
                scanf("%s", &data);
                getchar();
                temp = InsertNode(now, cnt, data);
                if (temp != NULL)
                    printf("添加成功");
            }
            else
                printf("当前未指定链表");
            break;
        case 6:
            if (now != NULL)
            {
                printf("是否删除?(Y/N)");
                scanf("%c", &answer);
                getchar();
                if (answer == 'Y')
                    if (DelFromEnd(now))
                        printf("删除成功!");
                    else
                        printf("删除失败");
                else if (answer != 'N')
                    printf("请正确输入");
            }
            else
                printf("当前未指定链表");
            break;
        case 7:
            if (now != NULL)
            {
                printf("是否删除?(Y/N)");
                char answer;
                scanf("%c", &answer);
                getchar();
                if (answer == 'Y')
                {

                    printf("请输入要删除的节点的位置(头为1,尾为当前链表节点数)");
                    scanf("%d", &cnt);
                    getchar();
                    if (DelNode(cnt, now))
                        printf("添加成功");
                    else
                        printf("删除失败");
                }
                else if (answer != 'N')
                    printf("请正确输入");
            }
            else
                printf("当前未指定链表");
            break;
        case 8:
            if (now != NULL)
            {
                printf("请输入尾节点需要链接的节点的位置(头为1,尾为当前链表节点数)");
                scanf("%d", &cnt);
                if (Linked(now, cnt))
                    printf("连接成功");
                else
                    printf("连接失败");
            }
            else
                printf("当前未指定链表");
            break;
        case 9:
            if (now != NULL)
            {
                if (isCircle(now))
                    printf("该链表已成环");
                else
                    printf("该链表未成环");
            }
            else
                printf("当前未指定链表");
            break;
        case 10:
            if (now != NULL)
            {
                printf("该链表有：%d个节点", GetSize(now));
            }
            else
                printf("当前未指定链表");
            break;
        case 11:
            if (now != NULL)
            {
                printf("请输入想要获取的节点的内容:");
                scanf("%s", &data);
                getchar();
                locate = SearchLocate(now, data);
                if (locate[0] == 0)
                    printf("该链表中无节点为此内容");
                else
                {
                    printf("该链表中，内容为此的节点有:");
                    for (size_t i = 0; locate[i] != 0; i++)
                        printf("%d号节点\t", locate[i]);
                }
            }
            else
                printf("当前未指定链表");
            break;
        case 12:
            if (now != NULL)
            {
                printf("请输入需要展示内容的节点的编号:");
                scanf("%d", &cnt);
                getchar();
                temp = GetNode(now, cnt);
                if (temp != NULL)
                    printf("%d号节点的内容为:%s", cnt, temp->Data);
                else
                    printf("该链表无该号节点");
            }
            else
                printf("当前未指定链表");
            break;
        case 13:
            if (now != NULL)
            {
                ParitySwapping(now);
                printf("互换成功");
            }
            else
                printf("当前未指定链表");
            break;
        case 14:
            if (now != NULL)
            {
                temp = GetMiddle(now);
                printf("中间节点内容为:%s", temp->Data);
            }
            else
                printf("当前未指定链表");
            break;
        case 15:
            if (now != NULL)
            {
                cnt = 1;
                for (temp = now->head->next; cnt <= GetSize(now); temp = temp->next)
                {
                    printf("%d号节点:%s\t", cnt, temp->Data);
                    cnt++;
                }
            }
            else
                printf("当前未指定链表");
            break;
        case 16:
            if (now != NULL)
            {
                {
                    printf("是否删除?(Y/N)");
                    scanf("%c", &answer);
                    getchar();
                    if (answer == 'Y')
                        if (CleanList(now))
                        {
                            printf("清除成功!");
                            now = NULL;
                            for (int i = ListNo; i < TotalNo; i++)
                                Operater[i] = Operater[i + 1];
                            Operater[TotalNo - 1] = NULL;
                            TotalNo--;
                        }
                        else
                            printf("清除失败");
                    else if (answer != 'N')
                        printf("请正确输入");
                }
            }
            else
                printf("当前未指定链表");
            break;
        case 17:
            if (Reversal(now))
                printf("倒转成功");
            else
                printf("倒转失败");
            break;
        case 18:
            if (recursionReveral(now, 1, GetSize(now)))
                printf("倒转成功");
            else
                printf("倒转失败");
            break;
        case 19:
            break;
        default:
            printf("请正确输入！");
            flag = 0;
            break;
        }
        printf("\n继续输入:\n");
    }
    return 0;
}