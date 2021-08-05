#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}Node;

void creailist(int n,Node *head)
{
    Node *p;
    p=(Node*)malloc(sizeof(Node));
    p=head;
    for(int i=0;i<n;i++)
    {
        p->next=(Node*)malloc(sizeof(Node));
        scanf("%d",&p->next->data);
        p=p->next;
    }
    p->next=NULL;
}

void printlist(Node *head)
{
    Node *p=head->next;
    while(p){

    printf("%d ",p->data);
    p=p->next;
    }
}

Node *paixu(Node *head_a,Node *head_b)
{
    Node *p,*q,*temp,*head_new;
    p=head_a->next;
    q=head_b->next;
    head_new=head_a;
    head_new->next=NULL;
    while(p&&q)
    {
        if(p->data<=q->data)
        {
            temp=p;
            p=p->next;
            temp->next=head_new->next;
            head_new->next=temp;
        }
        else
        {
            temp=q;
            q=q->next;
             temp->next=head_new->next;
            head_new->next=temp;
        }
    }
    while(p)
    {
        temp = p;
        p = p->next;
        temp->next = head_new->next;
        head_new->next = temp;
    }
    while(q)

    {
       temp = q;
        q = q->next;
        temp->next = head_new->next;
        head_new->next = temp;
    }
    free(head_b);
    return head_new;

}

int main()
{
    int m,n;
    Node *head_a,*head_b;
     head_a = (Node*)malloc(sizeof(Node));
    head_b = (Node*)malloc(sizeof(Node));
    scanf("%d %d",&m,&n);
    creailist(m,head_a);
    creailist(n,head_b);
    printlist(paixu(head_a,head_b));
    return 0;
}
