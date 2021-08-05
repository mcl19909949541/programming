

void createNewGraphList (struct graphList *gList)
    scanf ("%d%d",&(gList->vexNum),&(gList->edgeNum));

    clearVexNodes (gList);

    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        scanf ("%d",&(gList->vex[i].vex));
    }

    int vex,n;
    for (i=0;i<gList->edgeNum;i++)
    {
        scanf ("%d",&vex);

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

int findVex (int vex,struct graphList *gList)//找与输入边的首数据符合的头节点
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
    p->headVex=findVex (vex,gList);
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

void existWay (struct graphList *gList)
{
    int vi,cur,find;
    scanf ("%d%d",&vi,&find);
    cur=findVex (vi,gList);

    char flags[MAX]={0};

    struct edgeNodeQueue queue;
    clearQueue (&queue);
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
    pushQueue(queue,headVex);
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

void clearQueue(struct edgeNodeQueue *queue)
{
    int i;
    for (i=0;i<=2999;i++)
    {
        queue->nodeQueue[i]=0;
    }
    queue->n=-1;
}

void pushQueue (struct edgeNodeQueue *queue,int vex)
{
    (queue->n)++;
    queue->nodeQueue[queue->n]=vex;
}

void unshiftQueue (struct edgeNodeQueue *queue)
{
    int i;
    for (i=1;i<=queue->n;i++)
    {
        queue->nodeQueue[i-1]=queue->nodeQueue[i];
    }
    (queue->n)--;
}

int main()
{
   struct graphList gList;//定义图时没有*，即直接分配空间了
    createNewGraphList (&gList);//注意传的是&
    existWay (&gList);
    return 0;
}
