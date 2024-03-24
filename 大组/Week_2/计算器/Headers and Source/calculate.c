#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <math.h>
// 数字结构体
struct NUM
{
    char INTEGER[11];
    char DECIMAL[11];
    char IntegerNum;
    char DecimalNum;
};

// 初始化并获取一个数字结构体
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

// 获取数字大小
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

// 执行计算
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

// 判断是否为操作符
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

// 判断是否为数字
int isNum(char c)
{
    return ((c <= '9') && (c >= '0'));
}

// 获取操作符优先级
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