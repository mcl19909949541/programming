
#include<stdio.h>
#include<stdlib.h>

typedef struct BinTreeNode
{
    int data;
    struct BinTreeNode *Lchild;
    struct BinTreeNode *Rchild;
}BinTreeNode,*BinTree;

void CreateTree(BinTreeNode **T)//建立二叉树
{
    int elem;
    scanf("%d",&elem);
   if(elem==-1) *T=NULL;
     else{
            *T=(BinTreeNode*)malloc(sizeof(BinTreeNode));
            (*T)->data=elem;
        CreateTree(&((*T)->Lchild));
        CreateTree(&((*T)->Rchild));
     }
}

void InsertBinTree(BinTreeNode **T,int elem)//插入二叉排序树结点（因为要从上往下一步一步找，所以一次只能插一个，不能递归）
{
    if(*T==NULL)
    {
       *T=(BinTreeNode*)malloc(sizeof(BinTreeNode));
       (*T)->data=elem;
       (*T)->Lchild=NULL;
       (*T)->Rchild=NULL;
    }
    else if(elem<(*T)->data)
        InsertBinTree(&((*T)->Lchild),elem);
    else if(elem>(*T)->data)
        InsertBinTree(&((*T)->Rchild),elem);

}

void CreateBinTree(BinTreeNode **T)//建立树
{
    int elem;
    (*T)=NULL;
    scanf("%d",&elem);
    while(elem!=-1)
    {
        InsertBinTree(T,elem);
        scanf("%d",&elem);
    }
}

BinTreeNode* SelectTree(BinTreeNode *T,int elem)//查找二叉排序树中的元素
{
    if(T==NULL) return NULL;
    else if(T->data==elem) return T;
    else if(T->data>elem) return (SelectTree(T->Lchild,elem));
    else return (SelectTree(T->Rchild,elem));
}

void SelectRangeelem(BinTreeNode *T,int a,int b)//查找范围内元素
{
    if(T)
    {
        SelectRangeelem(T->Lchild,a,b);
        if(T->data>a&&T->data<b) printf("%d ",T->data);
        SelectRangeelem(T->Rchild,a,b);
    }
}


int SelectBinSortTree(BinTreeNode *T)//判断是否为二叉排序树
{
    if(T==0) return 1;
    else if(T->Lchild&&T->Rchild)
    {
        if(T->data<T->Lchild->data||T->data>T->Rchild->data) return 0;
        else return(SelectBinSortTree(T->Lchild)&&SelectBinSortTree(T->Rchild));
    }
    else if(T->Lchild)
    {
        if(T->data<T->Lchild->data) return 0;
        else return(SelectBinSortTree(T->Lchild));
    }
    else if(T->Rchild)
    {
        if(T->data<T->Rchild->data) return 0;
        else return(SelectBinSortTree(T->Rchild));
    }
    return 1;
}

void printOrder(BinTreeNode *T)//输出树
{
    if(T==NULL)return;
    printOrder(T->Lchild);
    printf("%d ",T->data);
    printOrder(T->Rchild);
}

void DelBST(BinTreeNode *T,int key)//在二叉排序树中删除结点
{//因为一个结点一旦有左子树，就要有区分左右大小的任务，所以以有无左子树来分类讨论
    BinTreeNode *p,*f,*s,*q;
    p=T;
    f=NULL;
    while(p)//查找为key的待删除结点
    {
        if(p->data==key) break;//找到则break
        f=p;//f指向p的双亲结点
        if(p->data>key) p=p->Lchild;
        else p=p->Rchild;
    }
    if(p==NULL) return ;//找不到则退出
    if(p->Lchild==NULL)//若p无左子树
    {
        if(f==NULL) free(p);//p为原树的根
        else if(f->Lchild==p)//p为f的左子树
            f->Lchild=p->Rchild;//把p的右子树链到f的左子树上
        else//p为f的右子树
            f->Rchild=p->Rchild;//把p的右子树链到f的右子树上
        free(p);
    }
    else//p有左子树
    {
        q=p;
        s=q->Lchild;
        while(s->Rchild)
        {
            q=s;
            s=s->Rchild;//在p的左子树中查找最右下结点（此节点为首个比待删除结点小的结点，它能肩负起区分大小的任务）
        }
        if(q==p) q->Lchild=s->Lchild;
        else q->Rchild=s->Lchild;//把s的左子树链到s的双亲结点p的右子树（绕开s）
        p->data=s->data;
        free(s);
    }

}
void CombineTree(BinTreeNode **T1,BinTreeNode **T2)
{
    if(*T2)
    {
        CombineTree(&(*T1),&((*T2)->Lchild));
        InsertBinTree(&(*T1),(*T2)->data);
         CombineTree(&(*T1),&((*T2)->Rchild));
    }
}


int main()
{
   BinTreeNode *T1,*T2;
   CreateTree(&T1);
   CreateTree(&T2);
   CombineTree(&T1,&T2);
    printOrder(T1);
    /*
     BinTreeNode *T;
    int a,b,elem,key;
    CreateTree(&T);
    scanf("%d %d",&a,&b);
    scanf("%d",&elem);
    scanf("%d",&key);
    SelectRangeelem(T,a,b);
    printf("\n");
    InsertBinTree(&T,elem);
    printOrder(T);
    printf("\n");
    DelBST(T,key);
    printOrder(T);
    */
    //CreateBinTree(&T);
    //printOrder(T);
    //DelBST(T,12);
    //printOrder(T);
    //BinTreeNode *Tfind;
    //Tfind=SelectTree(T,48);
    //printf("  %d",Tfind->data);
    //if(SelectBinSortTree(T))
    //{
    //    printf("yes");
    //}
   // else printf("no");
    return 0;
}
