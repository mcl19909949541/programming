#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

void CreatList(Node *head,int n){//创建链表
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

void Insert(Node *head,int x){//插入链表函数
    Node *p,*px;
    p = head;
    px = (Node*)malloc(sizeof(Node));
    px->data = x;
    while(p->next){
        if(p->next->data>=px->data){
            px->next = p->next;
            p->next = px;
           return ;
           p=px;
        }
        else{
            p = p->next;
        }
    }

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
    int n,x;
    scanf("%d",&n);
    Node *head;
    head = (Node*)malloc(sizeof(Node));
    CreatList(head,n);
    scanf("%d",&x);
    Insert(head,x);
    OutputList(head);
    return 0;
}

