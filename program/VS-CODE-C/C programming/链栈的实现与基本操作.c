#include<stdio.h>
#include<stdlib.h>

typedef int StackElementType;

typedef struct Node{
StackElementType data;
struct Node *next;
}Node,*LinkList;

void Push(LinkList S,char x)//ÈëÕ»
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = S->next;
    temp->data=x;
    S->next=temp;
    return;
}

void Pop(Node *S,int *x)//³öÕ»
{
    Node *temp=S->next;
    if(temp==NULL) {printf("WRONG\n");return ;}
    S->next=temp->next;
    *x=temp->data;
    free(temp);
    return ;
}
void GetTop(Node *S,int *x)
{
    if(S->next==NULL) {printf("EMPTY\n");return ;}
    *x=S->next->data;
    return ;
}

int main()
{
    Node *S=(Node*)malloc(sizeof(Node));
    S->next=NULL;
    char x;
    Push(&S,'A');
    GetTop(&S,&x);
    printf("%d\n",x);
    Pop(&S,&x);
    GetTop(&S,&x);
    return ;

}
