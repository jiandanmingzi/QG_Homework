#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <math.h>
// ���ֽṹ��
struct NUM
{
    char INTEGER[11];
    char DECIMAL[11];
    char IntegerNum;
    char DecimalNum;
};

// ��ʼ������ȡһ�����ֽṹ��
struct NUM* InitNum()
{
    struct NUM* Num = (struct NUM*)malloc(sizeof(struct NUM));
    if (Num != NULL)
    {
        Num->DecimalNum = 0;
        Num->IntegerNum = 0;
    }
    return Num;
}

void addInt(struct NUM* Num, char num)
{
    Num->INTEGER[Num->IntegerNum] = num;
    Num->IntegerNum++;
}

void addDec(struct NUM* Num, char num)
{
    Num->DECIMAL[Num->DecimalNum] = num;
    Num->DecimalNum;
}

// ��ȡ���ִ�С
double GetNum(struct NUM* Num)
{
    double result = 0;
    int integer = 0;
    for (size_t i = 0; i < Num->IntegerNum; i++)
        integer = integer * 10 + (Num->INTEGER[i] - '0');
    for (int i = 0; i < Num->DecimalNum; i++)
        result += ((double)(Num->DecimalNum - '0') / pow(10, -(i + 1)));
    result += (double)integer;
    return result;
}

// ִ�м���
double GetAnswer(double firstNum, double secondNum, char c)
{
    double answer = 0;
    switch (c)
    {
    case '+':
        answer = secondNum + firstNum;
        break;
    case '-':
        answer = secondNum - firstNum;
        break;
    case '*':
        answer = secondNum * firstNum;
        break;
    case '/':
        answer = secondNum / firstNum;
        break;
    }
    return answer;
}

// �ж��Ƿ�Ϊ������
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

// �ж��Ƿ�Ϊ����
int isNum(char c)
{
    return ((c <= '9') && (c >= '0'));
}

// ��ȡ���������ȼ�
int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return 0;
}