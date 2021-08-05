#include<stdio.h>

#define MAXSIZE 100

typedef struct
{
    int element[MAXSIZE];
    int front;
    int rear;
}SeqQueue;

void InitQueue(SeqQueue *Q)//���г�ʼ��
{
    Q->front=Q->rear=0;
}

void EnterQueue(SeqQueue *Q,int x)//���
{
    if((Q->rear+1)%MAXSIZE==Q->front) return;
    Q->element[Q->rear]=x;
    Q->rear=(Q->rear+1)%MAXSIZE;
}

void deleteQueue(SeqQueue *Q,int *x)//����
{
    if(Q->front==Q->rear)  return ;//����Ϊ��
    *x=Q->element[Q->front];
    Q->front=(Q->front+1)%MAXSIZE;
}

int main()
{     int x;
    SeqQueue Q;
    InitQueue(&Q);
    EnterQueue(&Q,1);
     EnterQueue(&Q,2);
      EnterQueue(&Q,3);
    deleteQueue(&Q,&x);
    printf("���Ԫ��Ϊ1 2 3 4\n");
    printf("��һ������Ԫ��Ϊ%d",x);
    return 0;

}
