#include "queue.h"

int main()
{
    struct Queue* QueueList[10];
    struct Queue* now = NULL;
    int flag = 0, QueueNum = 0, NowNo = 0;
    char line[3], ch;
    for (size_t i = 0; i < 10; i++)
        QueueList[i] = NULL;
    printf("��ʽ����(����ʾ�ַ�����������):\n����:\n 1->չʾ��ǰ���ж���\n 2->�½�����\n 3->ѡ�����\n 4->��ǰ���д�β�ӽڵ�\n 5->��ǰ���л�ȡͷ�ڵ�����\n 6->��ǰ���е���ͷ�ڵ�\n 7->��ǰ���г���\n 8->��յ�ǰ����\n9->�˳�ϵͳ\n\n��ǰ: ");
    if (now == NULL)
        printf("δָ������\n\n");
    else
        printf("%d �Ŷ���\n\n", QueueNum);
    while (flag != 9)
    {
        fgets(line, 3, stdin);
        // system("cls");
        fflush(stdin);
        printf("��ʽ����(����ʾ�ַ�����������):\n����:\n 1->չʾ��ǰ���ж���\n 2->�½�����(�����������ɴ���10)\n 3->ѡ�����\n 4->��ǰ���д�β�ӽڵ�\n 5->��ǰ���л�ȡͷ�ڵ�����\n 6->��ǰ���е���ͷ�ڵ�\n 7->��ǰ���г���\n 8->��յ�ǰ����\n9->�˳�ϵͳ\n\n��ǰ: ");
        if (now == NULL)
            printf("δָ������\n\n");
        else
            printf("%d �Ŷ���\n\n", QueueNum);
        if (((line[1] == '\0') || (line[1] == '\n')) && (line[0] <= '9') && line[0] >= '1')
            flag = line[0] - '0';
        else
        {
            flag = 0;
            printf("����ȷ����!\n");
        }
        if (flag == 1)
        {
            if (QueueNum == 0)
                printf("��ǰ�޶���");
            else
            {
                printf("��ǰ�� %d ������", QueueNum);
                for (size_t i = 0; i < QueueNum; i++)
                    printf("%d �Ŷ���: %s ����Ϊ %d ���ڵ� ��ǰռ�� %d ���ڵ�\n", i + 1, QueueList[i]->queueName, QueueList[i]->capacity, QueueList[i]->size);
            }
        }
        else if (flag == 2)
        {
            if (QueueNum < 10)
            {
                printf("��ǰ���ڴ��� %d ������\n������������(������19���ַ�,�����ַ����Զ����):\n", QueueNum + 1);
                char name[20];
                fgets(name, 20, stdin);
                fflush(stdin);
                printf("�������������(������2λ��,����Ϊ0):\n");
                char check = 1, capacity[4];
                int num;
                do
                {
                    check = 1;
                    fgets(capacity, 4, stdin);
                    fflush(stdin);
                    for (int cnt = 0; cnt < 2; cnt++)
                        if ((capacity[cnt] < '0') || (capacity[cnt] > '9'))
                            check = 0;
                    if (((capacity[2] == '\0') || (capacity[2] == '\n')) && (capacity[0] >= '0') && (capacity[0] <= '9') && (capacity[1] <= '9') && (capacity[1] >= '0'))
                        num = (capacity[0] - '0') * 10 + (capacity[1] - '0');
                    else if (((capacity[1] == '\0') || (capacity[1] == '\n')) && (capacity[0] <= '9') && capacity[0] >= '1')
                        num = capacity[0] - '0';
                    else
                        check = 0;
                    if ((check == 0) || (num == 0))
                    {
                        check = 0;
                        printf("����ȷ����!\n");
                    }
                } while (!check);
                now = initQueue(num, name);
                if (now != NULL)
                {
                    QueueList[QueueNum] = now;
                    QueueNum++;
                    NowNo = QueueNum;
                }
                else
                    printf("����ʧ��");
            }
            else
                printf("�޷���������");
        }
        else if (flag == 3)
        {
            if (QueueNum)
            {
                char line[4];
                int flag = 1, check = 0;
                do
                {
                    printf("������Ҫѡ��Ķ��еı��:\n");
                    fgets(line, 4, stdin);
                    fflush(stdin);
                    check = 1;
                    if (((line[2] == '\0') || (line[2] == '\n')) && (line[0] == '1') && (line[1] == '0'))
                        flag = 10;
                    else if (((line[1] == '\0') || (line[1] == '\n')) && (line[0] <= '9') && line[0] >= '1')
                        flag = line[0] - '0';
                    else
                        check = 0;
                    if (!check)
                        printf("����ȷ����!\n");
                } while (!check);
                if (QueueList[flag - 1] != NULL)
                    now = QueueList[flag - 1];
                else
                    printf("��ǰ���޺���Ϊ: %d �Ķ���", flag);
            }
            else
                printf("��ǰ�޶���");
        }
        else if (flag == 4)
        {
            if (now != NULL)
            {
                printf("��������Ҫ��ӵ�����(������20���ַ�):\n");
                char* name = (char*)malloc(21 * sizeof(char));
                fgets(name, 21, stdin);
                fflush(stdin);
                if (addNode(now, name))
                    printf("��ӳɹ�\n");
                else
                    printf("���ʧ��");
            }
            else
                printf("��ǰδָ������");
        }
        else if (flag == 5)
        {
            char* data = getData(now);
            if (data != NULL)
                printf("ͷ�ڵ�����Ϊ:%s\n", data);
            else
                printf("��ȡʧ�ܣ�\n");
        }
        else if (flag == 6)
        {
            char* data = getNode(now);
            if (data != NULL)
                printf("ͷ�ڵ�����Ϊ:%s\n", data);
            else
                printf("��ȡʧ�ܣ�\n");
        }
        else if (flag == 7)
        {
            if (now != NULL)
                printf("��ǰ���г�%d", now->size);
            else
                printf("��ǰδָ������");
        }
        else if (flag == 8)
        {
            if (now != NULL)
                if (cleanQueue(now))
                {
                    printf("����ɹ�\n");
                    now = NULL;
                    for (int i = NowNo; i < QueueNum; i++)
                        QueueList[i - 1] = QueueList[i];
                    QueueNum--;
                    QueueList[QueueNum] = NULL;
                }
                else
                    printf("���ʧ��\n");
            else
                printf("��ǰδָ������");
        }
        printf("\n��������:\n");
    }
    return 0;
}