
#include<stdio.h>
#include<stdlib.h>
int depth;
typedef struct Node{
char data;
struct Node *Lchild;
struct Node *Rchild;
}BiTNode,*Bitree;

void CreateBinTree(BiTNode **T)
{
    char ch;
    ch=getchar();
   if(ch=='.'){ *T=NULL;return;}

            *T=(BiTNode*)malloc(sizeof(BiTNode));
            (*T)->data=ch;
        CreateBinTree(&((*T)->Lchild));
        CreateBinTree(&((*T)->Rchild));

}

Bitree CreateBinTree2()
{      BiTNode *T;
    char ch;
    ch=getchar();
   if(ch=='.'){ return NULL;}

            T=(BiTNode*)malloc(sizeof(BiTNode));
            T->data=ch;
       T->Lchild= CreateBinTree2();
       T->Rchild= CreateBinTree2();
        //return T;
}

void PreTree(Bitree T)
{   if(T==NULL) return;
    printf("%c ",T->data);
     PreTree(T->Lchild);
     PreTree(T->Rchild);

}
int  PostTreeDepth(BiTNode *T)//求树的深度(后序遍历）
{
    int hl,hr,max;
    if(T!=NULL)
    {
        hl=PostTreeDepth(T->Lchild);
        hr=PostTreeDepth(T->Rchild);
        max=hl>hr?hl:hr;
        return (max+1);
    }
    else return 0;

}
void PreTreeDepth(BiTNode *T,int h)//求树的深度（先序遍历）depth为全局变量
{
    if(T!=NULL)
    {
        if(h>depth) depth=h;
        PreTreeDepth(T->Lchild,h+1);
        PreTreeDepth(T->Rchild,h+1);

    }
}


int main()
{
    BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));

    T=CreateBinTree2();

    PreTree(T);
    printf("%d",PostTreeDepth(T));

    return 0;
}
