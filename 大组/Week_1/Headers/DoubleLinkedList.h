#include "DoubleList.c"
struct DoubleListOp
{
};

int GetSize(struct DoubleListOp *target); // 获取链表长度

struct DoubleList *GetNode(struct DoubleListOp *target, int cnt); // 获取特定位置的节点

struct DoubleList *AddFromEnd(struct DoubleListOp *target, char *Data); // 从尾添加

struct DoubleList *AddFromHead(struct DoubleListOp *target, char *Data); // 从头添加

int DelFromEnd(struct DoubleListOp *target); // 删除尾节点

int Linked(struct DoubleListOp *target); // 将链表头尾相连

int *SearchLocate(struct DoubleListOp *target, char *Data); // 根据数据搜索节点所在位置

struct DoubleListOp *CreatDoubleList(char *Name); // 创建新链表

struct DoubleList *InsertNode(struct DoubleListOp *target, int cnt, char *Data); // 任意位置插入节点

int DelNode(int locate, struct DoubleListOp *target); // 删除指定位置的节点

int ChangeNode(int cnt, struct DoubleListOp *target, char *Data); // 更改指定节点数据

int CleanList(struct DoubleListOp *target); // 清空链表

int isCircle(struct DoubleListOp *target); // 判断是否成环

int ParitySwapping(struct DoubleListOp *target); // 奇偶对换

struct DoubleList *GetMiddle(struct DoubleListOp *target); // 取中间值

int Reversal(struct DoubleListOp *target); // 非递归反转链表

int recursionReveral(struct DoubleListOp *target, int cnt, int Size); // 递归反转链表