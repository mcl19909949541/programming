#include<stdio.h>
#include<stdlib.h>

typedef int QueueElemType;

typedef struct Node
{
    QueueElemType data;
    struct Node *next;
}LQNode;

typedef struct {
LQNode *front;
LQNode *near;
}LinkQueue;

void EnterQueue(LinkQueue *Q,int x)//���
{
    LQNode *NewNode;
    NewNode=(LQNode*)malloc(sizeof(LQNode));
    if(NewNode!=NULL)
    {
        NewNode->data=x;
        NewNode->next=NULL;
        Q->near->next=NewNode;
        Q->near=NewNode;
    }
}

void DeleteQueue(LinkQueue *Q,int *x)//���ӣ�����x����
{
    LQNode *p;
    if(Q->near==Q->front)
        return;
    p=Q->front->next;
    Q->front->next=p->next;
    if(Q->near=p)  //��ֻ��һ��Ԫ��
    {
        Q->front=Q->near;
    }
    *x=p->data;
    free(p);
    return ;
}

int main()
{
    LinkQueue *Q;              //���г�ʼ��

    Q->front=(LQNode*)malloc(sizeof(LQNode));
printf("d");
    Q->near=Q->front;
    Q->front->next=NULL;

    EnterQueue(Q,1);

     EnterQueue(Q,2);
      EnterQueue(Q,3);
       EnterQueue(Q,4);
       int x;
       DeleteQueue(Q,&x);
       printf("%d",x);
       return 0;
}
