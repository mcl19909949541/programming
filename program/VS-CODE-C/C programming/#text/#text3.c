#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

void CreatList(Node *head,int n){//��������
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    p = head;
    for(int i=0;i<n;i++){
        p->next = (Node*)malloc(sizeof(Node));
        scanf("%d",&p->next->data);
        p = p->next;
    }
    p->next = NULL;
}

void Insert(Node *head,int x){//����������
    Node *p,*px;
    p = head;
    px = (Node*)malloc(sizeof(Node));
    px->data = x;
    while(p->next){
        if(p->next->data>=px->data){
            px->next = p->next;
            p->next = px;
           // return ;
        p=px;
        }
        else{
            p = p->next;
        }
    }

}

void OutputList(Node *head){//�������
    Node *p = head->next;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
}

void delectnode(Node *head,int x)
{
    Node *p,*q;
    p = head;
    while(p)
    {
        if(p->next->data==x)
        {
            p->next->next=p->next;
        }
        p=p->next;
    }
    
}

int main()
{
    int n,x;
    scanf("%d",&n);
    Node *head;
    head = (Node*)malloc(sizeof(Node));
    CreatList(head,n);
    scanf("%d",&x);
    //Insert(head,x);
    //delectnode(head,x);
    OutputList(head);
    return 0;
}

