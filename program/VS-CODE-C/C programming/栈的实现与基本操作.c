#include<stdio.h>
#include<stdlib.h>

typedef int StackElementType;
#define Stack_size 100

typedef struct
{
    StackElementType elem[Stack_size];
    int top;
}SeqStack;

void InitStack(SeqStack *S)
{
    S->top=-1;
}

void Push(SeqStack *S,StackElementType x)//��ջ
{
    if(S->top==Stack_size-1) return;
    S->top++;
    S->elem[S->top]=x;
    return ;
}
void Pop(SeqStack *S,int *e)//��ջ����e����ֵ
{
    if(S->top==-1)
    {
        printf("STACK EMPTY");
        return ;
    }
    else{
        *e=S->elem[S->top];
        S->top--;
        return ;
    }
}

void GetTop(SeqStack *S,int *e)//����ջ��Ԫ�أ�����ɴ�S��ȥ����Ϊ���Ƕ�S�޸Ķ�ֻ��ȡ
{
    if(S->top==-1)
    {
        printf("STACK EMPTY");
        return ;
    }
    else{
        *e=S->elem[S->top];
        return ;
    }
}

int main()
{    int e;
    SeqStack S;
    InitStack(&S);
    Push(&S,10);
    Pop(&S,&e);
    printf("%d\n",e);
    GetTop(&S,&e);
    return 0;

}
