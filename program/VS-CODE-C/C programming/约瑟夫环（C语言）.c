#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct queue{
    int Qnum[MAXSIZE];//ע��˴�Ϊ�ؼ��������õĶ���Ҫ�����ǵ�ADT������ͬ����
    int front;
    int rear;
}Queue;//��������ѡ��������������

void initilize(Queue *Q) { //��ʼ������
    Q->front = 0;
    Q->rear = 0;
}

int Pop(Queue *Q)//����
{
    Q->front++;
    return Q->Qnum[Q->front];
}

void Push(Queue *Q,int i)//���
{
    Q->rear++;
    Q->Qnum[Q->rear]=i;
}

int Isempty(Queue *Q)//�п�
{
    return Q->front==Q->rear;
}

void Setup(Queue *Q,int length)//�����������
{
    initilize(Q);
    for(int i=1;i<=length;i++)
    {
        Push(Q,i);
    }
}

void Josephus(Queue *Q,int m)
{
    int i,j=1,move,remove;
    while(!Isempty(Q))
    {
        while(j<m)
        {
            move=Pop(Q);
            Push(Q,move);
            j++;
        }

        remove=Pop(Q);
        printf("%d ",remove);
        j=1;
    }
}

int main()
{
    Queue Q;
    int length,m;
    scanf("%d %d",&length,&m);
    Setup(&Q,length);
    Josephus(&Q,m);

    return 0;
}
