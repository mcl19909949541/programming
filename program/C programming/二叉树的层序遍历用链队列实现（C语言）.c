#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct TreeNode{
char data;
struct TreeNode *Lchild;
struct TreeNode *Rchild;
}BiTNode,*Bitree;

typedef BiTNode* QueueElemType;//终于懂了啥叫用户自定义类型了

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

//以下为建立链队列的基本操作，注意与二叉树对应

void initilize(LinkQueue *Q) { //初始化队列
     Q->front=(LQNode*)malloc(sizeof(LQNode));
     Q->near=Q->front;
    Q->front->next=NULL;
}


void EnterQueue(LinkQueue *Q,BiTNode *x)//入队
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

BiTNode *DeleteQueue(LinkQueue *Q)//出队
{
    LQNode *p;
    p=Q->front->next;
    Q->front->next=p->next;
    if(Q->near==p)  //若只有一个元素
    {
        Q->front=Q->near;
    }

    return p->data;
}

int Isempty(LinkQueue *Q)
{
    return Q->front==Q->near;
}

void LayerOrder(LinkQueue *Q,BiTNode *T)//二叉树的层次遍历
{

    BiTNode *p;
    EnterQueue(Q,T);
    while(!Isempty(Q))
    {
        p=DeleteQueue(Q);
        printf("%c ",p->data);//输出队首结点
        if(p->Lchild) EnterQueue(Q,p->Lchild);//把Pop掉的结点的左子结点加入队列
        if(p->Rchild) EnterQueue(Q,p->Rchild);//把Pop掉的结点的右子结点加入队列
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




