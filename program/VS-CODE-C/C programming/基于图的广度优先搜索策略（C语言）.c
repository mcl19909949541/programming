#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//定义一个结点
//边表
struct edgeNode
{
    int headVex;//相邻顶点字段
    struct edgeNode *next;//链字段
};
//定义一个头节点
//顶点表
struct vexNode
{
    int vex;//顶点信息
    struct edgeNode *head;//边表头指针
};
//定义图
struct graphList
{
    struct vexNode vex[MAX];
    int vexNum;//顶点数
    int edgeNum;//边个数
};
//定义队列
struct edgeNodeQueue
{
    int nodeQueue[MAX];
    int n;
};
//把函数提前申明会少报好多warning啊
void createNewGraphList (struct graphList *gList);
void clearVexNodes (struct graphList *gList);
int findVex (int vex,struct graphList *gList);
void createNewEdgeNode (int n,struct graphList *gList);
void existWay (struct graphList *gList);
int breadthFirstSearch (char flags[],struct graphList *gList,int cur,int find,struct edgeNodeQueue *queue);
void clearQueue(struct edgeNodeQueue *queue);
void pushQueue (struct edgeNodeQueue *queue,int vex);
void unshiftQueue (struct edgeNodeQueue *queue);

int main()
{
   struct graphList gList;
    createNewGraphList (&gList);
    existWay (&gList);
    return 0;
}


void createNewGraphList (struct graphList *gList)//建立图
{
    scanf ("%d%d",&(gList->vexNum),&(gList->edgeNum));//输入图的结点个数和边数

    clearVexNodes (gList);//！！注意这里不用加&

    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        scanf ("%d",&(gList->vex[i].vex));//输入顶点信息
    }

    int vex,n;
    for (i=0;i<gList->edgeNum;i++)
    {
        scanf ("%d",&vex);//输入要找寻的边的头
        n=findVex (vex,gList);//找到并返回
        createNewEdgeNode (n,gList);//插入结点
    }
}

void clearVexNodes (struct graphList *gList)//初始化顶点表
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        gList->vex[i].vex=0;
        gList->vex[i].head=NULL;
    }
}

int findVex (int vex,struct graphList *gList)//找与输入数对应的位置
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        if (vex==gList->vex[i].vex)
        {
            return i;
        }
    }
    return -1;
}

void createNewEdgeNode (int n,struct graphList *gList)//插入结点
{
    struct edgeNode *p,*q;
    int vex;
    p=(struct edgeNode *)malloc(sizeof(struct edgeNode));
    scanf ("%d",&vex);
    p->headVex=findVex (vex,gList);//找到与之对应的位置，即我每个结点存储的值为输入数据所对应的位置
    p->next=NULL;
    if (gList->vex[n].head==NULL)
    {
        gList->vex[n].head=p;
    }
    else
    {
        q=gList->vex[n].head;
        while (q->next)
        {
            q=q->next;
        }
        q->next=p;
    }
}

void existWay (struct graphList *gList)//查看是否有符合输入的路径
{
    int vi,cur,find;
    scanf ("%d%d",&vi,&find);
    cur=findVex (vi,gList);//cur为vi这个值所对应的顶点表所对应的位置

    char flags[MAX]={0};//标志符，判断是否处理过

    struct edgeNodeQueue queue;
    clearQueue (&queue);//队列初始化
    if (breadthFirstSearch (flags,gList,cur,find,&queue))
    {
        printf ("yes");
    }
    else
    {
        printf ("no");
    }
}

int breadthFirstSearch (char flags[],struct graphList *gList,int cur,int find,struct edgeNodeQueue *queue)
{
    int headVex;
    struct edgeNode *p;
    headVex=cur;
    pushQueue(queue,headVex);//入队
    while (queue->n>=0)
    {
        headVex=queue->nodeQueue[0];
        if (find==gList->vex[headVex].vex)
        {
            return 1;
        }
        if (flags[headVex]==0)
        {
            flags[headVex]=1;
            p=gList->vex[headVex].head;
            while (p)
            {
                pushQueue(queue,p->headVex);
                p=p->next;
            }
        }
        unshiftQueue(queue);
    }
    return 0;
}

void clearQueue(struct edgeNodeQueue *queue)//队列初始化
{
    int i;
    for (i=0;i<=99;i++)
    {
        queue->nodeQueue[i]=0;
    }
    queue->n=-1;
}

void pushQueue (struct edgeNodeQueue *queue,int vex)//入队
{
    (queue->n)++;
    queue->nodeQueue[queue->n]=vex;
}

void unshiftQueue (struct edgeNodeQueue *queue)//出队
{
    int i;
    for (i=1;i<=queue->n;i++)
    {
        queue->nodeQueue[i-1]=queue->nodeQueue[i];
    }
    (queue->n)--;
}
