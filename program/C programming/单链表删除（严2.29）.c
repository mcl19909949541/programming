#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Node{//这里的struct node 为结构体类型名，可以用来给变量赋类型
    ElemType data;
    struct Node *next;
}Node,*LinkList;

void CreatFromTail(Node *head ,int e)
{
    Node *p;                  //尾插法
    p=head;
    for(int  i=0;i<e;i++)
    {

        p->next=(Node*)malloc(sizeof(Node));
         scanf("%d",&p->next->data);
           p=p->next;
    }
    p->next =NULL;
}


int Get(LinkList head,int i)//查找第i个结点
   { int j=0;
    Node *p;
    if(i<=0) return -1;
    p=head;

    while(p->next!=NULL&&(j<i))
    {
        p=p->next;
        j++;
    }
    if(i=j) return p->data;
    else return -1;
}

void DelList(LinkList head,int i)//删除第i个结点并用e返回其值
{
    Node *pre,*r;
    int k;
    pre=head;
    k=0;
    while(pre->next!=NULL&&k<i-1)
    {
        pre=pre->next;
        k=k+1;
    }
    if(pre->next==NULL)
    {
        printf("WRONG PLACE");
        return;
    }
    r=pre->next;
    pre->next=r->next;
    free(r);
    return;
}
void OutputList(Node *head){//输出链表
    Node *p = head->next;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
}



int main()
{
    int m,n,p;
    Node *A,*B,*C;
   scanf("%d %d %d",&m,&n,&p);
     A = (Node*)malloc(sizeof(Node));
      B = (Node*)malloc(sizeof(Node));
       C= (Node*)malloc(sizeof(Node));
       A->next=NULL;  B->next=NULL;  C->next=NULL;

    CreatFromTail(A,m);
    CreatFromTail(B,n);
    CreatFromTail(C,p);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        for(int k=1;k<=p;k++)
    {
        if(Get(A,i)==Get(B,j)&&Get(A,i)==Get(C,k)) DelList(A,i);
    }
   OutputList(A);
   return 0;

}


