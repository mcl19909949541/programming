#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct DNode
{
    ElemType data;
    struct DNode *pre,*next;//����ǰ��ָ�������ָ��
}DNode,*DoubleList;


void CreatFromTail(DNode *head)  //β�巨����˫������
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

void DInsList(DoubleList head,int i,char e)//�ڵ�i���������e
{
   DNode *p,*s;
   int k;
   if(i<=0) return;
   p=head;
   k=0;
   while(p!=NULL&&k<i+1)//�˴��뵥����һ��
   {
       p=p->next;
       k=k+1;
   }
   if(p==NULL)
   {
       printf("WRONG PLACE");
       return ;
   }
   s=(DNode*)malloc(sizeof(DNode));//��һ���˫����һ��
   s->data=e;
   s->pre=p->pre;
   p->pre->next=s;
   s->next=p;
   p->pre=s;
   return;

}
void DDelList(DoubleList head,int i,char *e)//ɾ����i����㲢��e������ֵ
{
    DNode *p,*r;
    int k;
    p=head;
    k=0;
    while(p->next!=NULL&&k<i)//�˴��뵥����ͬ
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

void OutputList(DNode *head){//�������
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

