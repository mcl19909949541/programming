#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int tag;//0��Ϊԭ�ӽ�㣬1��Ϊ����
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
    if(s=='('){ //s='('ʱ�������ӱ�
        GL->tag=1;
        GL->ptr.head=(GList*)malloc(sizeof(GList));
        CreatList(GL->ptr.head);//GL->ptr.headΪ�����ӱ�
     }

    else{//�ж���֪����ʱsֻ��Ϊ��ĸ��')'����','
        if(s==')'){ //s=')'ʱ����GL->tail=NULL��ͬʱ�˳�����ݹ�
            GL=NULL;
            return;
        }
        if(s==','){ //s=','ʱ�������̱�(��ǰ��ĺ�һ����
            GL->tail=(GList*)malloc(sizeof(GList));
            CreatList(GL->tail);//GL->tailΪ�����̱�
            return;
        }
        GL->tag=0;//sΪ��ĸ
        GL->ptr.atom=s;
       }
       //��һ����ĸsֻ��Ϊ')'����','
    s=getchar();
    if(s==')'||s=='\n')//s=')'ʱ����
    {
        GL->tail=NULL;
    }
    else{//s=','ʱ�������̱�
        GL->tail=(GList*)malloc(sizeof(GList));
        CreatList(GL->tail);
    }
    return;
}

int GetDepth(GList *GL)
{
    int max=0,depth;
    GList *p;
    if(GL->tag==0)//ԭ�ӽ����ȷ���0
    {
        return 0;
    }
    p=GL->ptr.head;//�����ӱ�
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
        p=p->tail;//�����̱�
    }
    return max+1;

}

void PrintGList(GList *GL)//���ӱ������ݣ��ٺ�̱�
{
    if(GL->tag==1)//Ҫ��Ϊ����
    {
        printf("(");
        if(GL->ptr.head!=NULL)//�ӱ�Ϊ�գ��ݹ�����ӱ�
        {
            PrintGList(GL->ptr.head);
        }
        printf(")");
    }
    else
    {
      printf("%c",GL->ptr.atom);
    }
    if(GL->tail!=NULL)//��̱�Ϊ�գ������ݹ������̱�
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
