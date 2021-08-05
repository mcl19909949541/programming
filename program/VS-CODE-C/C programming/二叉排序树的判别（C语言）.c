
#include<stdio.h>
#include<stdlib.h>

typedef struct BinTreeNode
{
    int data;
    struct BinTreeNode *Lchild;
    struct BinTreeNode *Rchild;
}BinTreeNode,*BinTree;

void CreateTree(BinTreeNode **T)//����������
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

void InsertBinTree(BinTreeNode **T,int elem)//���������������㣨��ΪҪ��������һ��һ���ң�����һ��ֻ�ܲ�һ�������ܵݹ飩
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

void CreateBinTree(BinTreeNode **T)//������
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

BinTreeNode* SelectTree(BinTreeNode *T,int elem)//���Ҷ����������е�Ԫ��
{
    if(T==NULL) return NULL;
    else if(T->data==elem) return T;
    else if(T->data>elem) return (SelectTree(T->Lchild,elem));
    else return (SelectTree(T->Rchild,elem));
}

void SelectRangeelem(BinTreeNode *T,int a,int b)//���ҷ�Χ��Ԫ��
{
    if(T)
    {
        SelectRangeelem(T->Lchild,a,b);
        if(T->data>a&&T->data<b) printf("%d ",T->data);
        SelectRangeelem(T->Rchild,a,b);
    }
}


int SelectBinSortTree(BinTreeNode *T)//�ж��Ƿ�Ϊ����������
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

void printOrder(BinTreeNode *T)//�����
{
    if(T==NULL)return;
    printOrder(T->Lchild);
    printf("%d ",T->data);
    printOrder(T->Rchild);
}

void DelBST(BinTreeNode *T,int key)//�ڶ�����������ɾ�����
{//��Ϊһ�����һ��������������Ҫ���������Ҵ�С��������������������������������
    BinTreeNode *p,*f,*s,*q;
    p=T;
    f=NULL;
    while(p)//����Ϊkey�Ĵ�ɾ�����
    {
        if(p->data==key) break;//�ҵ���break
        f=p;//fָ��p��˫�׽��
        if(p->data>key) p=p->Lchild;
        else p=p->Rchild;
    }
    if(p==NULL) return ;//�Ҳ������˳�
    if(p->Lchild==NULL)//��p��������
    {
        if(f==NULL) free(p);//pΪԭ���ĸ�
        else if(f->Lchild==p)//pΪf��������
            f->Lchild=p->Rchild;//��p������������f����������
        else//pΪf��������
            f->Rchild=p->Rchild;//��p������������f����������
        free(p);
    }
    else//p��������
    {
        q=p;
        s=q->Lchild;
        while(s->Rchild)
        {
            q=s;
            s=s->Rchild;//��p���������в��������½�㣨�˽ڵ�Ϊ�׸��ȴ�ɾ�����С�Ľ�㣬���ܼ縺�����ִ�С������
        }
        if(q==p) q->Lchild=s->Lchild;
        else q->Rchild=s->Lchild;//��s������������s��˫�׽��p�����������ƿ�s��
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
