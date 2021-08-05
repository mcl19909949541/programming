#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct TreeNode{
char data;
struct TreeNode *Lchild;
struct TreeNode *Rchild;
}BiTNode,*Bitree;

typedef struct stack
{
    BiTNode *s[MAXSIZE];
    int top;
}Stack;

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

void PreTree(Bitree T)//中序输出
{   if(T==NULL) return;

     PreTree(T->Lchild);
      printf("%c ",T->data);
     PreTree(T->Rchild);

}
void inorder(BiTNode *T)//中序输出非递归
{
    BiTNode *s[MAXSIZE];//模拟栈
    int top=0;
    BiTNode *p;
    p=T;
    do{
        while(p!=NULL)
        {
            if(top>MAXSIZE) return ;
            top++;
            s[top]=p;
            p=p->Lchild;
        }//遍历左子树
        if(top!=0)
        {
            p=s[top];
            top--;
            printf("%c ",p->data);//访问根结点
            p=p->Rchild;//遍历右子树
        }
    }while(p!=NULL||top!=0);
}
//以下为建立栈的基本操作，注意与二叉树对应
void InitStack(Stack *S)//初始化
{
    S->top=0;
}

void Push(Stack *S,BiTNode *T)//压栈
{
    S->top++;
    S->s[S->top]=T;
}

BiTNode *Pop(Stack *S)//出栈
{
    BiTNode *p;
    p=S->s[S->top];
    S->top--;
    return p;
}
void gettop(Stack *S,BiTNode **T)//取栈头
//注意修改树一律用二级指针
{
    (*T)=S->s[S->top];
}

int Isempty(Stack *S)
{
    if(S->top==0) return 1;
    else return 0;
}
void inordermoder2(BiTNode *T)
{
    Stack S;
    InitStack(&S);
    BiTNode *p;
    p=T;
   while(p!=NULL||!Isempty(&S))
    {
        if(p!=NULL)//遍历左子树
        {
            Push(&S,p);
            p=p->Lchild;
            printf("0");
        }
        else{
                 printf("1");
            p=Pop(&S);
            printf("%c ",p->data);
            p-p->Rchild;
        }
    }

}
void PreTree2(Bitree T)//后序输出
{   if(T==NULL) return;

     PreTree(T->Lchild);

     PreTree(T->Rchild);

     printf("%c ",T->data);

}
void PostOrder(BiTNode *T)//后序输出非递归
{
    Stack S;
    BiTNode *q,*p;
    q=NULL;
    p=T;
    InitStack(&S);
    while(p!=NULL||!Isempty(&S))
    {
        if(p!=NULL)
        {
            Push(&S,p);
            p=p->Lchild;
        }//遍历左子树
        else{
                gettop(&S,&p);
                if(p->Rchild==NULL||(p->Rchild==q))
                {
                    printf("%c ",p->data);
                    q=p;
                    p=Pop(&S);
                    p=NULL;
                }
                else{
                    p=p->Rchild;
                }
        }
    }
}

int main()
{
    BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));
    CreateBinTree(&T);
    PreTree2(T);
    printf("\n");
    //inordermoder2(T);
    PostOrder(T);
    return 0;
}
