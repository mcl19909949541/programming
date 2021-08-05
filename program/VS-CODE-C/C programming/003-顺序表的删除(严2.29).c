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

void *DuplicateRemoval(Node *head_a, Node *head_b, Node *head_c){//������ȥ�أ���B C�������ظ�Ԫ�ش���������У�����A�����н���ȥ��
     //����
    Node *pb,*pc;
    int duplicate[100]={-999999},i=0,j=1;//���ｫ����Ԫ��ȫ����ʼ��Ϊ���������ֵ����,j��i��1����ΪD[i=0]Ҫ��Ϊһ���������ݣ��ظ�Ԫ�ش�i=1��ʼ��¼
    pb = head_b->next;
    pc = head_c->next;
    while(pb && pc){//��BC������Ϊ��ʱ
        while(pb!=NULL && pc!=NULL && pb->data!=pc->data){//��BC�ڵ�ֵ���ظ���ѭ���ƶ��ڵ���أ�ע��Ҫ��ѭ���в����ж�BC�����Ƿ�Ϊ��
            if(pb->data < pc->data){//C�ڵ�data��B�ڵ�����
                pb = pb->next;
            }
            else{//B�ڵ�data��С��C�ڵ�����
                pc = pc->next;
            }
        }
        //��ʱ��һ���ǲ��ҵ����ظ��ڵ㣬����ǳ����˿ձ�
        if(pb==NULL || pc==NULL){//��BC�����пձ��������ٳ����ظ�Ԫ���ˣ��˳�ѭ��
            break;
        }
        //��ʱ��һ���ǲ��ҵ����ظ��ڵ㣬���Ǽ�¼����
        else{
            while(pb->data==duplicate[i] || pc->data==duplicate[i]){//�˴���һ�����ٹ��������ظ�Ԫ�ص�ѭ������Ȳ����˶�ͨ�����ѭ���ﵽ����Ŀ�ĵĸ��Ӷ�Ҫ��
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

    //ȥ��
    Node *pa;
    pa = head_a;
    while(pa->next){
        while(pa->next!=NULL && pa->next->data<duplicate[j]){//��A�ڵ�ֵ�������ظ�Ԫ�أ�ѭ���ƶ��ڵ���أ�ע��Ҫ��ѭ���в����ж�A�����Ƿ�Ϊ��
            pa = pa->next;
        }
        //��ʱһ����A�ڵ�Ԫ��Ϊ�ظ�Ԫ�أ������A����Ϊ�ձ�
        if(pa->next!=NULL && pa->next->data==duplicate[j]){//��A�ڵ�Ԫ��Ϊ�ظ�Ԫ��
            Node *q = pa->next;
            pa->next = q->next;
            free(q);//�ǵ��ͷ�ɾ���Ľڵ�
        }
        j++;
    }
}




void PrintList(Node *head){//�������
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
