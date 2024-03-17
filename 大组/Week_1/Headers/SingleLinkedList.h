#ifndef SingleLinkedList_H
#define SingleLinkedList_H
#include "SingleList.h"
struct SingleListOp;

int GetSize(struct SingleListOp *target); // 获取链表长度

struct SingleList *GetNode(struct SingleListOp *target, int cnt); // 获取特定位置的节点

struct SingleList *AddFromEnd(struct SingleListOp *target, char *Data); // 从尾添加

struct SingleList *AddFromHead(struct SingleListOp *target, char *Data); // 从头添加

int DelFromEnd(struct SingleListOp *target); // 删除尾节点

int Linked(struct SingleListOp *target, int locate); // 将尾节点与指定节点连接

int *SearchLocate(struct SingleListOp *target, char *Data); // 根据数据搜索节点所在位置

struct SingleListOp *CreatSingleList(char *Name); // 创建新链表

struct SingleList *InsertNode(struct SingleListOp *target, int cnt, char *Data); // 任意位置插入节点

int DelNode(int locate, struct SingleListOp *target); // 删除指定位置的节点

int ChangeNode(int cnt, struct SingleListOp *target, char *Data); // 更改指定节点数据

int CleanList(struct SingleListOp *target); // 清空链表

int isCircle(struct SingleListOp *target); // 判断是否成环

int ParitySwapping(struct SingleListOp *target); // 奇偶对换

struct SingleList *GetMiddle(struct SingleListOp *target); // 取中间值

#endif