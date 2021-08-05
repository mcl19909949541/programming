#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct TreeNode{
char data;
struct TreeNode *Lchild;
struct TreeNode *Rchild;
}BiTNode,*Bitree;

typedef BiTNode* QueueElemType;//���ڶ���ɶ���û��Զ���������

typedef struct Node
{
    QueueElemType data;
    struct Node *next;
}LQNode;

typedef struct {
LQNode *front;
LQNode *near;
}LinkQueue;

void CreateBinTree(BiTNode **T)
{
    char ch;
    ch=getchar();
   if(ch=='#'){ *T=NULL;return;}

            *T=(BiTNode*)malloc(sizeof(BiTNode));
            (*T)->data=ch;
        CreateBinTree(&((*T)->Lchild));
        CreateBinTree(&((*T)->Rchild));
}
void PreTree(Bitree T)
{   if(T==NULL) return;
    printf("%c ",T->data);
     PreTree(T->Lchild);
     PreTree(T->Rchild);
}

//����Ϊ���������еĻ���������ע�����������Ӧ

void initilize(LinkQueue *Q) { //��ʼ������
     Q->front=(LQNode*)malloc(sizeof(LQNode));
     Q->near=Q->front;
    Q->front->next=NULL;
}


void EnterQueue(LinkQueue *Q,BiTNode *x)//���
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

BiTNode *DeleteQueue(LinkQueue *Q)//����
{
    LQNode *p;
    p=Q->front->next;
    Q->front->next=p->next;
    if(Q->near==p)  //��ֻ��һ��Ԫ��
    {
        Q->front=Q->near;
    }

    return p->data;
}

int Isempty(LinkQueue *Q)
{
    return Q->front==Q->near;
}

void LayerOrder(LinkQueue *Q,BiTNode *T)//�������Ĳ�α���
{

    BiTNode *p;
    EnterQueue(Q,T);
    while(!Isempty(Q))
    {
        p=DeleteQueue(Q);
        printf("%c ",p->data);//������׽��
        if(p->Lchild) EnterQueue(Q,p->Lchild);//��Pop���Ľ������ӽ��������
        if(p->Rchild) EnterQueue(Q,p->Rchild);//��Pop���Ľ������ӽ��������
    }
}

int main()
{
    BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));
    CreateBinTree(&T);
    //PreTree(T);

    LinkQueue *Q=(LinkQueue*)malloc(sizeof(LinkQueue));
    initilize(Q);

    LayerOrder(Q,T);
    return 0;

}




