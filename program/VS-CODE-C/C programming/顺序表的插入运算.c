#include<stdio.h>
#include<stdlib.h>

typedef struct node{
 int data;
 struct node *next;
}Node;

void createlist(Node *head,int n)
{
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    p=head;
    for(int i=0;i<n;i++)
    {
        p->next = (Node*)malloc(sizeof(Node));
        scanf("%d",&p->next->data);
        p = p->next;
    }
    p->next = NULL;

}
void insert(Node *head , int x)
{
    Node *p,*px;
    p = head;
    px = (Node*)malloc(sizeof(Node));
    px->data = x;
    while(p->next)
    {
        if(p->next->data>=px->data)
        {
            px->next = p->next;
            p->next = px;
            return ;
        }
        else{
            p = p->next;
        }

    }
    p->next = px;
    px->next = NULL;


}
void outputlist(Node *head)
{
    Node *p = head->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}
int main()
{
    int n,x;
    scanf("%d",&n);
    Node *head;
    head = (Node*)malloc(sizeof(Node));
    createlist(head,n);
    scanf("%d",&x);
    insert(head,x);
    outputlist(head);
    return 0;
}
