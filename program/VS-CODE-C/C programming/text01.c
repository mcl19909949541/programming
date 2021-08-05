#include<stdio.h>
#include<stdlib.h>

typedef struct treenode
{
    char data;
    struct treenode *left;
    struct treenode *right;
} BitNode;

void createtree(BitNode **A)
{
    char e;
    (*A) = (BitNode *)malloc(sizeof(BitNode));
    (*A)->left = NULL;
    (*A)->right = NULL;
    scanf("%c", &e);
    if(e>='A'&&e<='Z')
    {
        (*A)->data = e;
        createtree(&((*A)->left));//给一个NULL的创建，会出现乱码
        createtree(&((*A)->right));
    }
}

void CreateBinTree(BitNode **T)
{
    char ch;
    ch=getchar();
   if(ch=='#'){ *T=NULL;return;}

            *T=(BitNode*)malloc(sizeof(BitNode));
            (*T)->data=ch;
        CreateBinTree(&((*T)->left));
        CreateBinTree(&((*T)->right));

}

void printtree(BitNode *A)
{
    
    if(A!=NULL)
    {
        printtree(A->left);
        printf("%c ", A->data);
        printtree(A->right);
    }
}

int treeNodeNum(BitNode *A)
{   if(A==NULL)
        return 0;
    if(A->left==NULL&&A->right==NULL) return 1;
    return treeNodeNum(A->right) + treeNodeNum(A->left);
}

int main()
{
    BitNode *A;
    A = (BitNode *)malloc(sizeof(BitNode));
    CreateBinTree(&A);
    printtree(A);
    printf(" %d", treeNodeNum(A));
    return 0;
}