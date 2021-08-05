#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
char data;
struct Node *Lchild;
struct Node *Rchild;
}BiTNode,*Bitree;

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

     PreTree(T->Lchild);
     printf("%c ",T->data);
     PreTree(T->Rchild);

}


int main()
{
    BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));

    CreateBinTree(&T);

    PreTree(T);

    return 0;
}
