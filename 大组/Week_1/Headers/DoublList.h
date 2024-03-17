#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct DoubleList
{
};

struct DoubleList *CreatHead(char List_Name[]); // 创建新链表

struct DoubleList *AddNode(char Data[], struct DoubleList *last); // 添加节点

int DeletNode(struct DoubleList *Node); // 删除节点

int ChangeData(char *Data, struct DoubleList *Node); // 修改节点数据

void swap(struct DoubleList *First, struct DoubleList *Second); // 交换节点位置
