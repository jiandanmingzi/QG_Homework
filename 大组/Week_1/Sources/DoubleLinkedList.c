#include "DoubleList.c"
struct DoubleListOp
{
    int size;                // 记录节点个数
    struct DoubleList *head; // 指向头节点的指针
    struct DoubleList *end;  // 指向尾节点的指针
};

int GetSize(struct DoubleListOp *target) // 获取链表长度
{

    int FastCnt = 0, SlowCnt = 0;
    if (target->head != NULL)
    {
        struct DoubleList *FastNode = target->head, *SlowNode = target->head;
        while (FastNode->next != NULL)
        {
            FastNode = FastNode->next;
            SlowNode = SlowNode->next;
            if (FastNode->next != NULL)
            {
                FastNode = FastNode->next;
                if (FastNode == SlowNode)
                {
                    if (FastNode == target->head)
                        target->size = 0;
                    break;
                }
            }
        }
        if ((FastNode->next != NULL) && (target->size != 0))
        {
            FastCnt = 0;
            FastNode = target->head;
            while (FastNode != SlowNode)
            {
                FastNode = FastNode->next;
                SlowNode = SlowNode->next;
                FastCnt++;
            }
            SlowCnt = 0;
            while (SlowNode->next != FastNode)
            {
                SlowNode = SlowNode->next;
                SlowCnt++;
            }
            target->size = SlowCnt + FastCnt;
        }
    }
    return target->size;
}

struct DoubleList *GetNode(struct DoubleListOp *target, int cnt) // 获取特定位置的节点
{
    struct DoubleList *temp = NULL;
    if (cnt <= GetSize(target))
    {
        temp = target->head->next;
        for (size_t i = 1; i < cnt; i++)
            temp = temp->next;
    }
    return temp;
}

struct DoubleList *AddFromEnd(struct DoubleListOp *target, char *Data) // 从尾添加
{
    struct DoubleList *end = NULL;
    end = AddNode(Data, target->end);
    target->end = end;
    target->size++;
    return end;
}

struct DoubleList *AddFromHead(struct DoubleListOp *target, char *Data) // 从头添加
{
    struct DoubleList *temp = NULL;
    temp = AddNode(Data, target->head);
    if (temp != NULL)
        target->size++;
    return temp;
}

int DelFromEnd(struct DoubleListOp *target) // 删除尾节点
{
    struct DoubleList *Node = target->end;
    struct DoubleList *last = Node->last;
    if (Node != NULL)
        if (DeletNode(Node))
        {
            target->end = last;
            target->size--;
            return 1;
        }
        else
            return 0;
    else
        return 0;
}

int Linked(struct DoubleListOp *target) // 将链表头尾相连
{
    target->end->next = target->head;
    target->head->last = target->end;
    return 1;
}

int *SearchLocate(struct DoubleListOp *target, char *Data) // 根据数据搜索节点所在位置
{
    int Size = GetSize(target), *num = (int *)malloc(Size * sizeof(int));
    int cnt = 0;
    struct DoubleList *answer = NULL, *temp = target->head->next;
    for (size_t i = 1; i <= Size; i++)
    {
        num[i - 1] = 0;
        if (!strcmp(Data, temp->Data))
        {
            answer = temp;
            num[cnt] = i;
            cnt++;
        }
    }
    return num;
}

struct DoubleListOp *CreatDoubleList(char *Name) // 创建新链表
{
    struct DoubleListOp
        *HeadNode = NULL;
    HeadNode = (struct DoubleListOp *)malloc(sizeof(struct DoubleListOp *));
    if (HeadNode != NULL)
    {
        HeadNode->head = CreatHead(Name);
        if (HeadNode->head != NULL)
        {
            HeadNode->end = HeadNode->head;
            HeadNode->size = 0;
        }
    }
    return HeadNode;
}

struct DoubleList *InsertNode(struct DoubleListOp *target, int cnt, char *Data) // 任意位置插入节点
{
    struct DoubleList *temp = NULL;
    if (cnt == (GetSize(target) + 1))
        temp = AddFromEnd(target, Data);
    else if (cnt == 1)
        temp = AddFromHead(target, Data);
    else
    {
        struct DoubleList *last = GetNode(target, cnt - 1);
        if (last != NULL)
        {
            temp = AddNode(Data, last);
            if (temp != NULL)
                target->size++;
        }
    }
    return temp;
}

int DelNode(int locate, struct DoubleListOp *target) // 删除指定位置的节点
{
    if (locate == GetSize(target))
        return DelFromEnd(target);
    else
    {
        struct DoubleList *Node = GetNode(target, locate);
        if (Node != NULL)
            if (DeletNode(Node))
            {
                target->size--;
                return 1;
            }
            else
                return 0;
        else
            return 0;
    }
}

int ChangeNode(int cnt, struct DoubleListOp *target, char *Data) // 更改指定节点数据
{
    struct DoubleList *Node = GetNode(target, cnt);
    if (Node != NULL)
    {
        ChangeData(Data, Node);
        return 1;
    }
    else
        return 0;
}

int CleanList(struct DoubleListOp *target) // 清空链表
{
    struct DoubleList *temp = target->head->next;
    int cnt = GetSize(target);
    target->end->next = NULL;
    for (size_t i = 0; i < cnt; i++)
    {
        struct DoubleList *next = temp->next;
        DeletNode(temp);
        temp = next;
    }
    free(target->head);
    target->head = NULL;
    temp = NULL;
    target->end = NULL;
    target->size = 0;
    target = NULL;
    if (target == NULL)
        return 1;
    else
        return 0;
}

int isCircle(struct DoubleListOp *target) // 判断是否成环
{
    int Size = GetSize(target);
    struct DoubleList *Node = target->head;
    int answer = 0, cnt = 0;
    while (Node->next != NULL)
    {
        Node = Node->next;
        cnt++;
        if (cnt > Size)
        {
            answer = 1;
            break;
        }
    }
    return answer;
}

int ParitySwapping(struct DoubleListOp *target) // 奇偶对换
{
    struct DoubleList *Node = target->head->next;
    int Size = GetSize(target);
    for (int cnt = 1; cnt < Size; cnt += 2)
    {
        if (Node->next == target->end)
            target->end = Node;
        swap(Node, Node->next);
        Node = Node->next;
    }
    return 1;
}

struct DoubleList *GetMiddle(struct DoubleListOp *target) // 取中间值
{
    int Middle = GetSize(target) / 2;
    struct DoubleList *Node = GetNode(target, Middle);
    return Node;
}

int Reversal(struct DoubleListOp *target) // 非递归反转链表
{
    struct DoubleList *Node = target->head->next;
    if (Node != target->head && Node != NULL)
    {
        int Size = GetSize(target);
        for (int i = 1; i < Size; i++)
        {
            Node = target->head->next;
            for (int i1 = 1; i1 <= Size - i; i1++)
                swap(Node, Node->next);
        }
        target->end = GetNode(target, Size);
        return 1;
    }
    else
        return 0;
}

int recursionReveral(struct DoubleListOp *target, int cnt, int Size) // 递归反转链表
{
    struct DoubleList *First = GetNode(target, cnt), *Second = GetNode(target, Size + 1 - cnt);
    struct DoubleList *Flast = First->last, *Fnext = First->next, *Slast = Second->last, *Snext = Second->next;
    if (Snext != NULL)
        Snext->last = First;
    Slast->next = First;
    Flast->next = Second;
    Fnext->last = Second;
    First->last = Slast;
    First->next = Snext;
    Second->next = Fnext;
    Second->last = Flast;
    cnt++;
    if (cnt <= (Size / 2))
        recursionReveral(target, cnt, Size);
    return 1;
}