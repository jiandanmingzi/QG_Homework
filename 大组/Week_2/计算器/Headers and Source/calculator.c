#define _CRT_SECURE_NO_WARNINGS
#include "calculate.h"
int main()
{
    double* answer;
    char expression[101], flag = 1, DecFlag = 0;
    struct Stack* NumStack = NULL;
    struct Stack* OpStack = NULL;
    struct NUM* num = NULL;
    while (1)
    {
        answer = 0;
        flag = 1;
        DecFlag = 0;
        NumStack = initStack("NumStack");
        OpStack = initStack("OpStack");
        num = InitNum();
        printf("请输入正确的表达式(仅支持不超过100个字符):\n");
        fgets(expression, 101, stdin);
        fflush(stdin);
        int i = 0;
        for (i = 0; (expression[i] != '\n') && (expression[i] != '\0'); i++)
        {
            if (isNum(expression[i]))
            {
                if (DecFlag)
                    addDec(num, expression[i]);
                else if (!DecFlag)
                    addInt(num, expression[i]);
            }
            else if (isOperator(expression[i]))
            {
                DecFlag = 0;
                double* value = (double*)malloc(sizeof(double)), * num1, * num2;
                if ((expression[i] != '(') && (expression[i - 1] != ')'))
                {
                    *value = GetNum(num);
                    addNode(NumStack, value);
                    free(num);
                    num = InitNum();
                }
                if (expression[i] == ')')
                {
                    char* c;
                    do
                    {
                        if (OpStack->size == 0)
                        {
                            flag = 0;
                            break;
                        }
                        c = getNode(OpStack);
                        if (*c != '(')
                        {
                            if (NumStack->size > 0)
                            {
                                num1 = getNode(NumStack);
                                if (NumStack->size == 0)
                                {
                                    flag = 0;
                                    break;
                                }
                                else
                                    num2 = getNode(NumStack);
                                double* value = (double*)malloc(sizeof(double));
                                *value = GetAnswer(*num1, *num2, *c);
                                addNode(NumStack, value);
                                free(num1);
                                free(num2);
                                num1 = NULL;
                                num2 = NULL;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                    } while (*c != '(');
                    if (flag == 0)
                        break;
                }
                else
                {
                    if (expression[i] == '(')
                        if ((expression[i + 1] == '*') || (expression[i + 1] == '/'))
                        {
                            flag = 0;
                            break;
                        }
                    if (OpStack->size > 0)
                    {
                        char* c = getData(OpStack);
                        while ((c != NULL) && (*c != '(') && (expression[i] != '(') && (precedence(*c)) >= (precedence(expression[i])))
                        {
                            getNode(OpStack);
                            if (NumStack->size > 0)
                            {
                                num1 = getNode(NumStack);
                                if (NumStack->size == 0)
                                {
                                    flag = 0;
                                    break;
                                }
                                else
                                    num2 = getNode(NumStack);
                                double* value = (double*)malloc(sizeof(double));
                                *value = GetAnswer(*num1, *num2, *c);
                                addNode(NumStack, value);
                                free(num1);
                                free(num2);
                                num1 = NULL;
                                num2 = NULL;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                            c = getData(OpStack);
                        }
                    }
                    addNode(OpStack, &expression[i]);
                }
            }
            else if (expression[i] == '.')
                DecFlag = 1;
            else if ((expression[i] != ' ') && (expression[i] != '\n') && (expression[i] != '\0'))
                flag = 0;
        }
        if (flag != 0)
        {
            if (isNum(expression[i - 1]) || (expression[i - 1] == ')'))
            {
                if (isNum(expression[i - 1]))
                {
                    double* value = (double*)malloc(sizeof(double));
                    *value = GetNum(num);
                    addNode(NumStack, value);
                }
                while (OpStack->size != 0)
                {
                    char* c = getNode(OpStack);
                    double* value = (double*)malloc(sizeof(double)), * num1, * num2;
                    if (*c == '(')
                    {
                        flag = 0;
                        break;
                    }
                    if (NumStack->size > 0)
                    {
                        num1 = getNode(NumStack);
                        if (NumStack->size == 0)
                        {
                            flag = 0;
                            break;
                        }
                        else
                            num2 = getNode(NumStack);
                        double* value = (double*)malloc(sizeof(double));
                        *value = GetAnswer(*num1, *num2, *c);
                        addNode(NumStack, value);
                        free(num1);
                        free(num2);
                        num1 = NULL;
                        num2 = NULL;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                if ((NumStack->size > 1) || (NumStack->size == 0))
                    flag = 0;
                else
                    answer = getNode(NumStack);
            }
            else
                flag = 0;
        }
        if (flag == 0)
            printf("请正确输入!\n");
        else
            printf("结果为:%lf\n", *answer);
        free(NumStack);
        free(OpStack);
    }
    return 0;
}