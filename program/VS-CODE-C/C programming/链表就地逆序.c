#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Node{//这里的struct node 为结构体类型名，可以用来给变量赋类型
    ElemType data;
    struct Node *next;
}Node,*LinkList;//LinkList 与 Node* 作用一样，这里的Node 和LinkList都可为变量赋类型

void CreatFromTail(Node *head)
{
    Node *p;                  //尾插法
    int flag=1;
    p=head;
    char c,d;
    while(flag)
    {
        c=getchar();
        d=getchar();//要将输入时的空格除去
        if(c!='$')
        {
        p->next = (Node*)malloc(sizeof(Node));
        p->next->data=c;
        p = p->next;
        }
        else
        {
            flag=0;
            p->next=NULL;
        }
    }
}

void OutputList(Node *head){//输出链表
    Node *p = head->next;
    while(p){
        printf("%c ",p->data);
        p = p->next;
    }
}

Node* InversionList(LinkList head)//单链表逆序，返回尾节点
{
    Node *p,*q,*r;
    p=head;
    q=p->next;
    while(q)
    {
        r=q->next;
        q->next=p;
        p=q;
        q=r;
    }
    head->next=NULL;
    head->data=' ';
    Node *rhead;
    rhead=(Node*)malloc(sizeof(Node));
    rhead->next=p;

    return rhead;

}

int main()
{
    Node *head,*rhead;
    head = (Node*)malloc(sizeof(Node));
    CreatFromTail(head);
    rhead=InversionList(head);
    OutputList(rhead);
    return 0;
}
