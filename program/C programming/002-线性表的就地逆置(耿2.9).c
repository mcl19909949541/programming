#include<stdio.h>
#include<stdlib.h>

#define MAX 100
void createarray(int A[],int n)
{
   for(int i=0;i<n;i++)
   {
       scanf("%d",&A[i]);
   }
}

void inversionarray(int A[],int n)
{
    for(int i=0;i<n/2;i++)
    {
        int temp=A[i];
        A[i]=A[n-i-1];
        A[n-i-1] = temp;
    }
}

void printarray(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }
}

typedef struct node
{
    int data;
    struct node *next;
}Node;

void createlist(Node *head,int n,int A[])
{
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    p=head;
    for(int i=0;i<n;i++)
    {
        p->next=(Node*)malloc(sizeof(Node));
        p->next->data = A[i];
        p=p->next;
    }
    p->next = NULL;
}

void inversionlist(Node *head)
{
    Node *p,*q;
    p = head->next;
    head->next = NULL;
    while(p)
    {
        q= p;
        p=p->next;
        q->next = head->next;
        head->next = q;
    }
}

void printlist(Node *head)
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
    int n,A[MAX]={100};
    Node *head;
    head=(Node*)malloc(sizeof(Node));
    scanf("%d",&n);
    createarray(A,n);
    createlist(head,n,A);

    inversionarray(A,n);
    printarray(A,n);
    printf("\n");

    inversionlist(head);
    printlist(head);
    return 0;
}
