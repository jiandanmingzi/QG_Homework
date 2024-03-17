#include "DoubleList.c"
struct DoubleListOp
{
};

int GetSize(struct DoubleListOp *target); // ��ȡ������

struct DoubleList *GetNode(struct DoubleListOp *target, int cnt); // ��ȡ�ض�λ�õĽڵ�

struct DoubleList *AddFromEnd(struct DoubleListOp *target, char *Data); // ��β���

struct DoubleList *AddFromHead(struct DoubleListOp *target, char *Data); // ��ͷ���

int DelFromEnd(struct DoubleListOp *target); // ɾ��β�ڵ�

int Linked(struct DoubleListOp *target); // ������ͷβ����

int *SearchLocate(struct DoubleListOp *target, char *Data); // �������������ڵ�����λ��

struct DoubleListOp *CreatDoubleList(char *Name); // ����������

struct DoubleList *InsertNode(struct DoubleListOp *target, int cnt, char *Data); // ����λ�ò���ڵ�

int DelNode(int locate, struct DoubleListOp *target); // ɾ��ָ��λ�õĽڵ�

int ChangeNode(int cnt, struct DoubleListOp *target, char *Data); // ����ָ���ڵ�����

int CleanList(struct DoubleListOp *target); // �������

int isCircle(struct DoubleListOp *target); // �ж��Ƿ�ɻ�

int ParitySwapping(struct DoubleListOp *target); // ��ż�Ի�

struct DoubleList *GetMiddle(struct DoubleListOp *target); // ȡ�м�ֵ

int Reversal(struct DoubleListOp *target); // �ǵݹ鷴ת����

int recursionReveral(struct DoubleListOp *target, int cnt, int Size); // �ݹ鷴ת����