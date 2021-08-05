#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int tag;//0则为原子结点，1则为表结点
    union{
        char atom;
        struct Node *head;
    }ptr;
    struct Node *tail;
}GList;

void CreatList(GList *GL);
int GetDepth(GList *GL);

void CreatList(GList *GL)
{
    char s;
    s =getchar();
    if(s=='('){ //s='('时，则构造子表
        GL->tag=1;
        GL->ptr.head=(GList*)malloc(sizeof(GList));
        CreatList(GL->ptr.head);//GL->ptr.head为构建子表
     }

    else{//判断易知，此时s只能为字母、')'或者','
        if(s==')'){ //s=')'时，令GL->tail=NULL，同时退出本层递归
            GL=NULL;
            return;
        }
        if(s==','){ //s=','时，构造后继表(当前表的后一个）
            GL->tail=(GList*)malloc(sizeof(GList));
            CreatList(GL->tail);//GL->tail为构造后继表
            return;
        }
        GL->tag=0;//s为字母
        GL->ptr.atom=s;
       }
       //下一个字母s只能为')'或者','
    s=getchar();
    if(s==')'||s=='\n')//s=')'时结束
    {
        GL->tail=NULL;
    }
    else{//s=','时，构造后继表
        GL->tail=(GList*)malloc(sizeof(GList));
        CreatList(GL->tail);
    }
    return;
}

int GetDepth(GList *GL)
{
    int max=0,depth;
    GList *p;
    if(GL->tag==0)//原子结点深度返回0
    {
        return 0;
    }
    p=GL->ptr.head;//进入子表
    if(p==NULL)
    {
        return 1;
    }
    while(p)
    {
        if(p->tag==1)
        {
            depth = GetDepth(p);

        if(depth>max){
                max = depth;
            }
        }
        p=p->tail;//进入后继表
    }
    return max+1;

}

void PrintGList(GList *GL)//先子表，再数据，再后继表
{
    if(GL->tag==1)//要是为表结点
    {
        printf("(");
        if(GL->ptr.head!=NULL)//子表不为空，递归输出子表
        {
            PrintGList(GL->ptr.head);
        }
        printf(")");
    }
    else
    {
      printf("%c",GL->ptr.atom);
    }
    if(GL->tail!=NULL)//后继表不为空，继续递归输出后继表
    {
        printf(",");
        PrintGList(GL->tail);
    }
}
int main()
{
    GList *GL;
    GL = (GList*)malloc(sizeof(GList));
    CreatList(GL);
    PrintGList(GL);
    int depth;
    depth = GetDepth(GL);
    printf("%d\n%d",depth,depth);
    return 0;
}
