#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

void CreatList(node *head,int n)
{
    int k;
    node *p;
    p = (node*)malloc(sizeof(node));
    p=head;
    for(int i=0;i<n;i++)
    {
        p->next = (node*)malloc(sizeof(node));
        scanf("%d",&k);
        p->next->data = k;
        p = p->next;
    }
    p->next=NULL;
}

void insert(node *head,int m)
{
    node *p;
    for(p=head;p!=NULL;p=p->next)
    {
        if(m<=p->next->data)
        {
            node *px = (node*)malloc(sizeof(node));
            px->data = m;
            px->next = p->next;
            p->next = px;
            return;
        }
    }
}

void putout(node *head)
{

    for(node *p=head->next;p!=NULL;p=p->next)
    {
        printf("%d ",p->data);
    }
}

void Delectnode(node *head,int m)
{
    node *p=head;
    while(p->next!=NULL)
    {
        if(p->next->data==m)
        {
            node *q=p->next;
            p->next=q->next;
            //return;
        }
        printf("x ");
        p=p->next;
    }

}
int main()
{
    int n,m;
    node *head;
    head = (node*)malloc(sizeof(node));
    scanf("%d",&n);
    CreatList(head,n);
    scanf("%d",&m);
    Delectnode(head,m);
    putout(head);
    return 0;
}
