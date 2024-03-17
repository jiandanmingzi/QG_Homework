#ifndef SingleList_H
#define SingleList_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct SingleList;

struct SingleList *CreatHead(char *List_Name); // 创建新链表

struct SingleList *AddNode(char *Data, struct SingleList *last); // 添加节点

int DeletNode(struct SingleList *last, struct SingleList *Node); // 删除节点

int ChangeData(char *Data, struct SingleList *Node); // 修改节点数据

void swap(struct SingleList *First, struct SingleList *Second, struct SingleList *FirstLast); // 交换节点位置