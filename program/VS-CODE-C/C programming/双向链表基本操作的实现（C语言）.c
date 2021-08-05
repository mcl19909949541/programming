#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct DNode
{
    ElemType data;
    struct DNode *pre,*next;//有向前的指针和向后的指针
}DNode,*DoubleList;


void CreatFromTail(DNode *head)  //尾插法建立双向链表
{
    DNode *p,*q;
    p=(DNode*)malloc(sizeof(DNode));
    p=head;
    int flag=1;
    char c,b;
    while(flag)
    {
        c=getchar();
        b=getchar();
        if(c!='$')
        {
            q=(DNode*)malloc(sizeof(DNode));
            q->data=c;
            p->next=q;
            q->pre=p;
            p=q;
        }
        else {
            flag=0;
            p->next=NULL;
        }

    }
}

void DInsList(DoubleList head,int i,char e)//在第i个结点后插入e
{
   DNode *p,*s;
   int k;
   if(i<=0) return;
   p=head;
   k=0;
   while(p!=NULL&&k<i+1)//此处与单链表不一样
   {
       p=p->next;
       k=k+1;
   }
   if(p==NULL)
   {
       printf("WRONG PLACE");
       return ;
   }
   s=(DNode*)malloc(sizeof(DNode));//这一块和双链表不一样
   s->data=e;
   s->pre=p->pre;
   p->pre->next=s;
   s->next=p;
   p->pre=s;
   return;

}
void DDelList(DoubleList head,int i,char *e)//删除第i个结点并用e返回其值
{
    DNode *p,*r;
    int k;
    p=head;
    k=0;
    while(p->next!=NULL&&k<i)//此处与单链表不同
    {
        p=p->next;
        k=k+1;
    }
    if(p->next==NULL)
    {
        printf("WRONG PLACE");
        return;
    }
    *e=p->data;
    p->pre->next=p->next;
    p->next->pre=p->pre;
    free(p);
    return;
}

void OutputList(DNode *head){//输出链表
    DNode *p = head->next;
    while(p){
        printf("%c ",p->data);
        p = p->next;
    }
}

int main()
{
    int e;
    DNode *head;
    head = (DNode*)malloc(sizeof(DNode));
    CreatFromTail(head);
    DInsList(head,2,'A');
    DDelList(head,4,&e);
    OutputList(head);
    return 0;
}

