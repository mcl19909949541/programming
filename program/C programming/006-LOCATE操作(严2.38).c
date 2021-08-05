/*
#include<stdio.h>

#include<stdlib.h>

typedef struct node{
char data;
struct node *pre;
struct node *next;
int freq;
}Node;

void creatlist(Node *head,int m)
{
    Node *p,*q;
    p=(Node*)malloc(sizeof(Node));
    p=head;
    getchar();
    for(int i=0;i<m;i++)
    {
        q=(Node*)malloc(sizeof(Node));
        scanf("%c",&q->data);
        getchar();
        q->freq=0;
        p->next=q;
        q->pre=p;
        p=q;
    }
    p->next=NULL;
}

void locate(Node *head,int n)
{
    char c;
    for(int i=0;i<n;i++)
    {
        Node *p=head->next;
        scanf("%c",&c);
        getchar();
        while(p!=NULL)
        {
            if(p->data == c)
            {
                p->freq++;
            }
        p=p->next;
        }
    }
}

void printlist(Node *head)
{
    Node *p=head->next;
    while(p)
    {
        printf("1%c ",p->data);
        p=p->next;
    }
}

void bubblesort(Node *head,int m)
{
    Node *p=head->next;
    while(m>1)
    {
        while(p->next!=NULL)
        {
            if(p->freq<p->next->freq)
            {
                char c;
                int f;
                c=p->data;
                f=p->freq;
                p->data=p->next->data;
                p->freq=p->next->freq;
                p->next->data=c;
                p->next->freq=f;
            }
            p=p->next;
        }
        m--;
        p=head->next;
    }
}
int main()
{
    Node *head;
    head=(Node*)malloc(sizeof(Node));
    int m,n;
    scanf("%d %d",&m,&n);
    creatlist(head,m);
    locate(head,n);
    bubblesort(head,m);
    printlist(head);
    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node *pre;
    struct node *next;
    int freq;
}Node;

void CreatList(Node *head, int m) {//˫����Ĵ���
    Node *p,*q;
    p = (Node*)malloc(sizeof(Node));
    p = head;
    getchar();
    for(int i=0;i<m;i++){//���ýڵ�qʵ��˫�����������
        q = (Node*)malloc(sizeof(Node));
        scanf("%c",&q->data);
        getchar();
        q->freq = 0;
        p->next = q;
        q->pre = p;
        p = q;
    }
    p->next = NULL;
}

void Locate(Node *head,int n){
    char c;
    for(int i=0;i<n;i++){
        Node *p = head->next;
        scanf("%c",&c);
        getchar();
        while(p!=NULL){//�����������Ȩ��freq������
            if(p->data == c){
                p->freq++;
            }
            p = p->next;
        }
    }
}

void BubbleSort(Node *head,int m){ //���ǱȽϼ򵥵Ľ���������ɵ�ð�����򣬵�û��ʹ��˫�����˫������,�ƻ���˫����preָ��
    Node *p = head->next;
    while (m > 1) {
        while (p->next != NULL) {
            if (p->freq < p->next->freq) {
                char c;
                int f;
                c = p->data;
                f = p->freq;
                p->data = p->next->data;
                p->freq = p->next->freq;
                p->next->data = c;
                p->next->freq = f;
            }
            p = p->next;
        }
        m--;
        p = head->next;
    }
}

void Sort(Node *head,int m){  //������˫�����ָ�뽻������ģ����������һЩ���⣬�����������У����ṩ˼·�����Ա���û��ʹ�ñ�����
    Node *p = head->next;
    Node *q;
    for(int i=1;i<m;i++){
        p = head->next;
        for(int j=1;j<=m-i&&p->next;j++){
            if(p->freq < p->next->freq){
                if(p->next->next==NULL){
                    q = p->next;
                    p->pre->next = q;
                    q->pre = p->pre;
                    p->pre = q;
                    p->next = NULL;
                    q->next = p;
                }
                q = p->next;
                p->pre->next = q;
                q->pre = p->pre;
                p->pre = q;
                p->next = q->next;
                q->next->pre = p;
                q->next = p;
            }
            p = p->next;
        }
    }
}

void PrintList(Node *head){//�������
    Node *p = head->next;
    while(p){
        printf("%1c ",p->data);
        p = p->next;
    }
}

int main(){
    Node *head;
    head = (Node*)malloc(sizeof(Node));
    int m,n;
    scanf("%d %d",&m,&n);
    CreatList(head,m);
    Locate(head,n);
    BubbleSort(head,m);
    PrintList(head);
    return 0;
}

