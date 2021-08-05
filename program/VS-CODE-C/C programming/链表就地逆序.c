#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Node{//�����struct node Ϊ�ṹ������������������������������
    ElemType data;
    struct Node *next;
}Node,*LinkList;//LinkList �� Node* ����һ���������Node ��LinkList����Ϊ����������

void CreatFromTail(Node *head)
{
    Node *p;                  //β�巨
    int flag=1;
    p=head;
    char c,d;
    while(flag)
    {
        c=getchar();
        d=getchar();//Ҫ������ʱ�Ŀո��ȥ
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

void OutputList(Node *head){//�������
    Node *p = head->next;
    while(p){
        printf("%c ",p->data);
        p = p->next;
    }
}

Node* InversionList(LinkList head)//���������򣬷���β�ڵ�
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
