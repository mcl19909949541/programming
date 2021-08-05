#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//����һ�����
//�߱�
struct edgeNode
{
    int headVex;//���ڶ����ֶ�
    struct edgeNode *next;//���ֶ�
};
//����һ��ͷ�ڵ�
//�����
struct vexNode
{
    int vex;//������Ϣ
    struct edgeNode *head;//�߱�ͷָ��
};
//����ͼ
struct graphList
{
    struct vexNode vex[MAX];
    int vexNum;//������
    int edgeNum;//�߸���
};
//�������
struct edgeNodeQueue
{
    int nodeQueue[MAX];
    int n;
};
//�Ѻ�����ǰ�������ٱ��ö�warning��
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


void createNewGraphList (struct graphList *gList)//����ͼ
{
    scanf ("%d%d",&(gList->vexNum),&(gList->edgeNum));//����ͼ�Ľ������ͱ���

    clearVexNodes (gList);//����ע�����ﲻ�ü�&

    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        scanf ("%d",&(gList->vex[i].vex));//���붥����Ϣ
    }

    int vex,n;
    for (i=0;i<gList->edgeNum;i++)
    {
        scanf ("%d",&vex);//����Ҫ��Ѱ�ıߵ�ͷ
        n=findVex (vex,gList);//�ҵ�������
        createNewEdgeNode (n,gList);//������
    }
}

void clearVexNodes (struct graphList *gList)//��ʼ�������
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        gList->vex[i].vex=0;
        gList->vex[i].head=NULL;
    }
}

int findVex (int vex,struct graphList *gList)//������������Ӧ��λ��
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

void createNewEdgeNode (int n,struct graphList *gList)//������
{
    struct edgeNode *p,*q;
    int vex;
    p=(struct edgeNode *)malloc(sizeof(struct edgeNode));
    scanf ("%d",&vex);
    p->headVex=findVex (vex,gList);//�ҵ���֮��Ӧ��λ�ã�����ÿ�����洢��ֵΪ������������Ӧ��λ��
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

void existWay (struct graphList *gList)//�鿴�Ƿ��з��������·��
{
    int vi,cur,find;
    scanf ("%d%d",&vi,&find);
    cur=findVex (vi,gList);//curΪvi���ֵ����Ӧ�Ķ��������Ӧ��λ��

    char flags[MAX]={0};//��־�����ж��Ƿ����

    struct edgeNodeQueue queue;
    clearQueue (&queue);//���г�ʼ��
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
    pushQueue(queue,headVex);//���
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

void clearQueue(struct edgeNodeQueue *queue)//���г�ʼ��
{
    int i;
    for (i=0;i<=99;i++)
    {
        queue->nodeQueue[i]=0;
    }
    queue->n=-1;
}

void pushQueue (struct edgeNodeQueue *queue,int vex)//���
{
    (queue->n)++;
    queue->nodeQueue[queue->n]=vex;
}

void unshiftQueue (struct edgeNodeQueue *queue)//����
{
    int i;
    for (i=1;i<=queue->n;i++)
    {
        queue->nodeQueue[i-1]=queue->nodeQueue[i];
    }
    (queue->n)--;
}
