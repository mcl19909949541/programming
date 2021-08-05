#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef struct Node{
char data;
struct Node *Lchild;
struct Node *Rchild;
}BiTNode,*Bitree;

typedef struct queue{
    BiTNode *numQ[MAXSIZE];//注意此处为关键。我们用的队列要与我们的ADT类型相同！！
    int front;
    int rear;
}Queue;//在这里我选择用数组来操作



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


//以下为建立队列的基本操作，注意与二叉树对应
void initilize(Queue *Q) { //初始化队列
    Q->front = 0;
    Q->rear = 0;
}

void Push(Queue *Q,BiTNode *T)//入队
//我还是比较喜欢用带*的来表示指针，比较直观
{
    Q->rear++;
    Q->numQ[Q->rear]=T;
}

BiTNode *Pop(Queue *Q)//出队
{
    Q->front++;
    return Q->numQ[Q->front];
}

int Isempty(Queue *Q)//判断是否为空
{
    return Q->front==Q->rear;
}

void LayerOrder(Queue *Q,BiTNode *T)//二叉树的层次遍历
{

    BiTNode *p;
    Push(Q,T);
    while(!Isempty(Q))
    {
        p=Pop(Q);
        printf("%c ",p->data);//输出队首结点
        if(p->Lchild) Push(Q,p->Lchild);//把Pop掉的结点的左子结点加入队列
        if(p->Rchild) Push(Q,p->Rchild);//把Pop掉的结点的右子结点加入队列
    }


}
int main()
{
    struct Node *T=(BiTNode*)malloc(sizeof(BiTNode));
    CreateBinTree(&T);
    Queue Q;
    initilize(&Q);
    //PreTree(T);
    LayerOrder(&Q,T);
    return 0;
}


