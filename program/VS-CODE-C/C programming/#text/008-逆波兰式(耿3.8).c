#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

typedef struct node
{
    char data;
    struct node *next;
}Node;

BOOL isempty(Node *S)
{
    if(S->next==NULL)
    {
        return TRUE;
    }
    return FALSE;
}

void push(Node *S,char x)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->next = S->next;
    S->next= temp;
}

void pop(Node *S)
{
    Node *temp = S->next;
    S->next = S->next->next;
    free(temp);
}

char gettop(Node *S)
{
    return S->next->data;
}

BOOL isalpha(char x)
{
    if(x>='a'&&x<='z'||x>='A'&&x=<'Z')
    {
        return TRUE;
    }
    return FALSE;
}

BOOL islower(char x1,char x2)
{
    if(x1=='+'||x1=='-')
    {
        if(x2=='*'||x2=='/'||x2=='(')
        {
            return TRUE;
        }

     else return FALSE;
    }
  else if(x1=='*' || x1=='/'){
        if(x2=='('){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else if(x1=='(' || x1=='#'){
         return TRUE;
    }
    else{
        return FALSE;

    }
}

BOOL isequal(char x1,char x2)
{
    if(x1=='('&&x2==')')
    {
        return TRUE;
    }
    return FALSE;
}

int main()
{
    Node *S;
    S=(Node*)malloc(sizeof(Node));
    S->next=NULL;
    push(S,'#');

    char c;
    char top;
     BOOL flag=TRUE;
     while(TRUE)
     {
         if(flag){
            scanf("%c",&c);
         }
         if(c=='\n') break;
         flag=TRUE;
         if(isalpha(c)) printf("%c",c);
         else{
            top=gettop(S);
            if(isequal(top,c)){
                pop(S);
            }

            else if(islower(top,c)){
                    push(S,c);
            }

            else
            {
                printf("%c",top);
                pop(S);
                flag=FALSE;
            }
         }


     }
     while(!isempty(S)&&gettop(S)!='#')
     {
         printf("%c",gettop(S));
         pop(S);
     }
     return 0;
}
