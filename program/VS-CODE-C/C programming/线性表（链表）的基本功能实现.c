#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Node{//这里的struct node 为结构体类型名，可以用来给变量赋类型
    ElemType data;
    struct Node *next;
}Node,*LinkList;//LinkList 与 Node* 作用一样，这里的Node 和LinkList都可为变量赋类型

void CreatFromHead(LinkList head)//这里往函数传头指针，用Node *head一样，都是传地址
{                           //头插法
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

Node *Get(LinkList head,int i)//查找第i个结点，返回结点
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


void OutputList(Node *head){//输出链表
    Node *p = head->next;
    while(p){
        printf("%c ",p->data);
        p = p->next;
    }
}

void InsList(LinkList head,int i,char e)//在第i个结点后插入e
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

void DelList(LinkList head,int i,char *e)//删除第i个结点并用e返回其值
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
void DestroyList(LinkList head)//销毁链表
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
     head->next=NULL;  //此步是头插法必须的，尾插法不必须
    printf("头插法建表（输入数据为）:\n");
    CreatFromTail(head);
    OutputList(head);
    printf("输出前三个数据的地址:\n");
    for(int i=1;i<4;i++)printf("%d ",&*Get(head,i));//注意要取结点的地址
    printf("当前链表长度为%d\n",ListLength(head));
    printf("在第二个元素后插入K后链表为:\n");
    InsList(head,2,'K');
    OutputList(head);
    printf("删除第4个元素后链表为:\n");
    DelList(head,4,&e);
    OutputList(head);
    printf("删除的元素值为%c\n",e);
    printf("销毁链表！");
    DestroyList(head);
    return 0;
}
