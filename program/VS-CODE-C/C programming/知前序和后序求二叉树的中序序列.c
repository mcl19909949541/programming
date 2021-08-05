#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct Node{
char data;
struct Node *Lchild;
struct Node *Rchild;
}BiTNode,*Bitree;

void PreTree(Bitree T)
{   if(T==NULL) return;

     PreTree(T->Lchild);
     PreTree(T->Rchild);
     printf("%c",T->data);

}
char pre[MAX];
char mid[MAX];

int MidFind(int left,int right,char MID)
{
    for(int i=left;i<=right;i++)
    {
        if(mid[i]==MID) return i;
    }
    return 0;
}

void Create(int left,int right,int *i,BiTNode **T)
{
    *T=(Bitree)malloc(sizeof(BiTNode));
    (*T)->data=pre[*i];
    (*T)->Lchild=NULL;
    (*T)->Rchild=NULL;
    (*i)++;
    int midnumber =  MidFind(left,right,(*T)->data);
    if(midnumber>left)
    {
        Create(left,midnumber-1,i,(&((*T)->Lchild)));
    }
    if(midnumber<right)
    {
        Create(midnumber+1,right,i,(&((*T)->Rchild)));
    }

}

BiTNode* Create2(int left,int right,int *i)
{   BiTNode *T;
    T=(Bitree)malloc(sizeof(BiTNode));
    T->data=pre[*i];
    T->Lchild=NULL;
    T->Rchild=NULL;
    (*i)++;
    int midnumber =  MidFind(left,right,T->data);
    if(midnumber>left)
    {
        T->Lchild = Create2(left,midnumber-1,i);
    }
    if(midnumber<right)
    {
        T->Rchild = Create2(midnumber+1,right,i);
    }
    return T;

}


int main()
{
    memset(pre,0,MAX);
     memset(mid,0,MAX);
     gets(pre);
     gets(mid);
     int left,right,len,i=0;
     len=strlen(pre);
     left=0;
     right=len-1;

     BiTNode *T;//=(Bitree)malloc(sizeof(BiTNode));
     T = Create2(left,right,&i);

     PreTree(T);
     return 0;
}
