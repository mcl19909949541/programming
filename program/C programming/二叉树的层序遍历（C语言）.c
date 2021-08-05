#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef struct Node{
char data;
struct Node *Lchild;
struct Node *Rchild;
}BiTNode,*Bitree;

typedef struct queue{
    BiTNode *numQ[MAXSIZE];//ע��˴�Ϊ�ؼ��������õĶ���Ҫ�����ǵ�ADT������ͬ����
    int front;
    int rear;
}Queue;//��������ѡ��������������



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


//����Ϊ�������еĻ���������ע�����������Ӧ
void initilize(Queue *Q) { //��ʼ������
    Q->front = 0;
    Q->rear = 0;
}

void Push(Queue *Q,BiTNode *T)//���
//�һ��ǱȽ�ϲ���ô�*������ʾָ�룬�Ƚ�ֱ��
{
    Q->rear++;
    Q->numQ[Q->rear]=T;
}

BiTNode *Pop(Queue *Q)//����
{
    Q->front++;
    return Q->numQ[Q->front];
}

int Isempty(Queue *Q)//�ж��Ƿ�Ϊ��
{
    return Q->front==Q->rear;
}

void LayerOrder(Queue *Q,BiTNode *T)//�������Ĳ�α���
{

    BiTNode *p;
    Push(Q,T);
    while(!Isempty(Q))
    {
        p=Pop(Q);
        printf("%c ",p->data);//������׽��
        if(p->Lchild) Push(Q,p->Lchild);//��Pop���Ľ������ӽ��������
        if(p->Rchild) Push(Q,p->Rchild);//��Pop���Ľ������ӽ��������
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


