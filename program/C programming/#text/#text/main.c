#include<stdio.h>

#define MAXSIZE 100

typedef struct
{
    int element[MAXSIZE];
    int front;
    int rear;
}SeqQueue;

void InitQueue(SeqQueue *Q)//队列初始化
{
    Q->front=Q->rear=0;
}

void EnterQueue(SeqQueue *Q,int x)//入队
{
    if((Q->rear+1)%MAXSIZE==Q->front) return;
    Q->element[Q->rear]=x;
    Q->rear=(Q->rear+1)%MAXSIZE;
}

void deleteQueue(SeqQueue *Q,int *x)//出队
{
    if(Q->front==Q->rear)  return ;//队列为空
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
    printf("入队元素为1 2 3 4\n");
    printf("第一个出队元素为%d",x);
    return 0;

}
