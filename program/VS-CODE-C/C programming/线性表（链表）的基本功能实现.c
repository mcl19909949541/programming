#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Node{//�����struct node Ϊ�ṹ������������������������������
    ElemType data;
    struct Node *next;
}Node,*LinkList;//LinkList �� Node* ����һ���������Node ��LinkList����Ϊ����������

void CreatFromHead(LinkList head)//������������ͷָ�룬��Node *headһ�������Ǵ���ַ
{                           //ͷ�巨
    Node *s;
    char c;
    int flag=1;
    while(flag)
    {
        c=getchar();
        if(c!='$')
        {
            s=(Node*)malloc(sizeof(Node));
            s->data=c;
            s->next=head->next;
            head->next=s;
        }
        else {flag=0;
               }
    }
}

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

Node *Get(LinkList head,int i)//���ҵ�i����㣬���ؽ��
{
    int j;
    Node *p;
    if(i<=0) return NULL;
    p=head;
    j=0;
    while(p->next!=NULL&&(j<i))
    {
        p=p->next;
        j++;
    }
    if(i=j) return p;
    else return NULL;
}

int ListLength(LinkList head)
{
    Node *p;
    p=head->next;
     int j=0;
    while(p!=NULL)
    {
        p=p->next;
        j++;
    }
    return j;

}


void OutputList(Node *head){//�������
    Node *p = head->next;
    while(p){
        printf("%c ",p->data);
        p = p->next;
    }
}

void InsList(LinkList head,int i,char e)//�ڵ�i���������e
{
   Node *pre,*s;
   int k;
   if(i<=0) return;
   pre=head;
   k=0;
   while(pre!=NULL&&k<i)
   {
       pre=pre->next;
       k=k+1;
   }
   if(pre==NULL)
   {
       printf("WRONG PLACE");
       return ;
   }
   s=(Node*)malloc(sizeof(Node));
   s->data=e;
   s->next=pre->next;
   pre->next=s;
   return;

}

void DelList(LinkList head,int i,char *e)//ɾ����i����㲢��e������ֵ
{
    Node *pre,*r;
    int k;
    pre=head;
    k=0;
    while(pre->next!=NULL&&k<i-1)
    {
        pre=pre->next;
        k=k+1;
    }
    if(pre->next==NULL)
    {
        printf("WRONG PLACE");
        return;
    }
    r=pre->next;
    *e=r->data;
    pre->next=r->next;
    free(r);
    return;
}
void DestroyList(LinkList head)//��������
{
    Node *p;
    while(head->next!=NULL)
    {
        p=head->next;
        head->next=p->next;
        free(p);
    }
}
int main()
{   char e;
    Node *head;
    head = (Node*)malloc(sizeof(Node));
     head->next=NULL;  //�˲���ͷ�巨����ģ�β�巨������
    printf("ͷ�巨������������Ϊ��:\n");
    CreatFromTail(head);
    OutputList(head);
    printf("���ǰ�������ݵĵ�ַ:\n");
    for(int i=1;i<4;i++)printf("%d ",&*Get(head,i));//ע��Ҫȡ���ĵ�ַ
    printf("��ǰ������Ϊ%d\n",ListLength(head));
    printf("�ڵڶ���Ԫ�غ����K������Ϊ:\n");
    InsList(head,2,'K');
    OutputList(head);
    printf("ɾ����4��Ԫ�غ�����Ϊ:\n");
    DelList(head,4,&e);
    OutputList(head);
    printf("ɾ����Ԫ��ֵΪ%c\n",e);
    printf("��������");
    DestroyList(head);
    return 0;
}
