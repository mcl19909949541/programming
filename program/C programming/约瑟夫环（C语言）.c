#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct queue{
    int Qnum[MAXSIZE];//注意此处为关键。我们用的队列要与我们的ADT类型相同！！
    int front;
    int rear;
}Queue;//在这里我选择用数组来操作

void initilize(Queue *Q) { //初始化队列
    Q->front = 0;
    Q->rear = 0;
}

int Pop(Queue *Q)//出队
{
    Q->front++;
    return Q->Qnum[Q->front];
}

void Push(Queue *Q,int i)//入队
{
    Q->rear++;
    Q->Qnum[Q->rear]=i;
}

int Isempty(Queue *Q)//判空
{
    return Q->front==Q->rear;
}

void Setup(Queue *Q,int length)//建立题意队列
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
