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

void *DuplicateRemoval(Node *head_a, Node *head_b, Node *head_c){//查重与去重，将B C链表中重复元素储存进数组中，并在A链表中进行去除
     //查重
    Node *pb,*pc;
    int duplicate[100]={-999999},i=0,j=1;//这里将数组元素全部初始化为非链表可能值即可,j比i大1，因为D[i=0]要作为一个测试数据，重复元素从i=1开始记录
    pb = head_b->next;
    pc = head_c->next;
    while(pb && pc){//当BC链表都不为空时
        while(pb!=NULL && pc!=NULL && pb->data!=pc->data){//若BC节点值不重复，循环移动节点查重，注意要在循环中不断判断BC链表是否为空
            if(pb->data < pc->data){//C节点data大，B节点右移
                pb = pb->next;
            }
            else{//B节点data不小，C节点右移
                pc = pc->next;
            }
        }
        //此时，一定是查找到了重复节点，亦或是出现了空表
        if(pb==NULL || pc==NULL){//当BC链表有空表，不可能再出现重复元素了，退出循环
            break;
        }
        //此时，一定是查找到了重复节点，我们记录即可
        else{
            while(pb->data==duplicate[i] || pc->data==duplicate[i]){//此处是一个快速过滤链表重复元素的循环，这比不过滤而通过外层循环达到过滤目的的复杂度要低
                if(pb->data==duplicate[i]){
                    pb = pb->next;
                }
                if(pc->data==duplicate[i]){
                    pc = pc->next;
                }
            }
        }
        duplicate[i+1] = pb->data;
        i++;
        pb = pb->next;
        pc = pc->next;
    }

    //去重
    Node *pa;
    pa = head_a;
    while(pa->next){
        while(pa->next!=NULL && pa->next->data<duplicate[j]){//若A节点值不属于重复元素，循环移动节点查重，注意要在循环中不断判断A链表是否为空
            pa = pa->next;
        }
        //此时一定是A节点元素为重复元素，亦或是A链表为空表
        if(pa->next!=NULL && pa->next->data==duplicate[j]){//若A节点元素为重复元素
            Node *q = pa->next;
            pa->next = q->next;
            free(q);//记得释放删除的节点
        }
        j++;
    }
}




void PrintList(Node *head){//输出链表
    Node *p = head->next;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
}

int main(){
    int m,n,p;
    struct node *head_a=NULL,*head_b=NULL,*head_c=NULL;
    head_a = (Node*)malloc(sizeof(Node));
    head_b = (Node*)malloc(sizeof(Node));
    head_c = (Node*)malloc(sizeof(Node));
    scanf("%d %d %d",&m,&n,&p);
    CreatList(head_a,m);
    CreatList(head_b,n);
    CreatList(head_c,p);
    DuplicateRemoval(head_a,head_b,head_c);
    PrintList(head_a);
    return 0;
}





/*
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
int data;
struct node *next;
}Node;

void creatlist(Node *head,int n)
{
    Node *p;
    p=(Node*)malloc(sizeof(Node));
    p=head;
    for(int i=0;i<n;i++)
    {
        p->next=(Node*)malloc(sizeof(Node));
        scanf("%d",p->next->data);
        p=p->next;
    }
    p->next==NULL;
}

void printlist(Node *head)
{
    Node *p;
    p=head->next;
    while(p)
    {
        printf("%d",p->data);
        p=p->next;
    }
}

void duplicateremoval(Node *head_a,Node *head_b,Node *head_c)
{
    Node *pb,*pc;
    int dup[100]={-1},i=0,j=1;
    pb=head_b->next;
    pc=head_c->next;
    while(pb&&pc)
    {
        while(pb!=NULL &&pc!=NULL &&pb->data!=pc->data)
        {
            if(pb->data<pc->data)
            {
                pb=pb->next;
            }
            else{
                 pc=pc->next;
            }
        }
        if(pb==NULL||pc==NULL)
        {
            break;
        }
        else{
             while(pb->data==dup[i]||pc->data==dup[i])
        {
            if(pb->data==dup[i])
            {
                pb=pb->next;
            }
            if(pc->data==dup[i])
            {
                pc=pc->next;
            }

        }
    }

    dup[i+1]=pb->data;
    i++;
    pb=pb->next;
    pc=pc->next;
    }
    Node *pa;
    pa=head_a->next;
    while(pa->next)
    {
        while(pa->next!=NULL&&pa->next->data<dup[j])
        {
            pa=pa->data;
        }
        if(pa->data!=NULL&&pa->next->data==dup[j])
        {
            Node *q=pa->next;
            pa->next=q->next;
            free(q);
        }
        j++;
    }

}

int main()
{
    int m,n,p;
   struct node *head_a=NULL,*head_b=NULL,*head_c=NULL;
    head_a = (Node*)malloc(sizeof(Node));
    head_b = (Node*)malloc(sizeof(Node));
    head_c = (Node*)malloc(sizeof(Node));
    scanf("%d %d %d",&m,&n,&p);
    creatlist(head_a,m);
         creatlist(head_b,n);
              creatlist(head_c,p);
    duplicateremoval(head_a,head_b,head_c);
        printlist(head_a);
        return 0;

}
*/
