#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//����һ�����
//�߱�
struct edgeNode
{
    int headVex;//���ڶ����ֶ�
    int weight;//Ȩ��
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

struct step{
    int flags[1000];
    int stepN[1000];
};

//����������ֹ��warning

void createNewGraphList (struct graphList *gList);
void clearVexNodes (struct graphList *gList);
void createNewEdgeNode (int n,struct graphList *gList);
void Dikstra(struct step *S,struct graphList *gList);
void clearStep(struct step *S,struct graphList *gList);
void initializeStep(struct step *S,struct graphList *gList);
int judgeStep(struct step *S,struct graphList *gList);
int findMinStepN(struct step *S,struct graphList *gList);
void updateStepN(struct step *S,struct graphList *gList,int min);
void print(struct step *S,struct graphList *gList);
void swap(int *a,int *b);
void quicksort(int array1[],int array2[],int maxlen,int begin,int end);



void createNewGraphList (struct graphList *gList)//����ͼ
{
    scanf ("%d%d",&(gList->vexNum),&(gList->edgeNum));

    clearVexNodes (gList);//ע��˴�����&

    int i,vex;
    for (i=0;i<gList->edgeNum;i++)//��ӽ��
    {
        scanf ("%d",&vex);
        gList->vex[vex-1].vex=vex;
        createNewEdgeNode (vex-1,gList);//�½����
    }
}
void createNewEdgeNode (int n,struct graphList *gList)//�½����
{
    struct edgeNode *p,*q;
    int headVex;
    p=(struct edgeNode *)malloc(sizeof(struct edgeNode));
    scanf ("%d",&headVex);//����β
    p->headVex=headVex-1;//��һ�˴�����Ϊ������0Ϊ�߱��һ��λ�ã�����Ҫ-1
    scanf ("%d",&(p->weight));//����Ȩ��
    p->next=NULL;
    //����β��
    if (gList->vex[n].head==NULL)//���߱�����Ԫ��
    {
        gList->vex[n].head=p;
    }
    else//�߱���Ԫ�أ�������λ���ƶ����˱߱�β��
    {
        q=gList->vex[n].head;
        while (q->next)
        {
            q=q->next;
        }
        q->next=p;//β��
    }
}



void clearVexNodes (struct graphList *gList)//ͼ�ĳ�ʼ��
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        gList->vex[i].vex=0;//�߱���Ϣ��Ϊ0
        gList->vex[i].head=NULL;//�߱�����ΪNULL
    }
}


void Dijkstra(struct step *S,struct graphList *gList)//�㷨����
{
    int min;
    clearStep (S,gList);//��ʼ��������ղ���
    initializeStep (S,gList);//��ʼ��
    while (judgeStep (S,gList))//�жϲ���
    {
        min=findMinStepN (S,gList);//����С��
        updateStepN (S,gList,min);//���²���

    }
}
void clearStep(struct step *S,struct graphList *gList)//��ʼ��������ղ���
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        S->flags[i]=-1;//-1��·��0���ҵ����·����1δ�ҵ����·��
        S->stepN[i]=0;//���˽ڵ�Ĳ���Ϊ0
    }
}

void initializeStep(struct step *S,struct graphList *gList)//��ʼ����������Ԫ�طŽ�ѭ����ʼ�ж�
{
    struct edgeNode *p;
    p=gList->vex[0].head;
    while (p)//ѭ���߱�
    {
        S->flags[p->headVex]=1;//����Ϊδ�ҵ����·��
        S->stepN[p->headVex]=p->weight;//���õ��˽ڵ㲽��
        p=p->next;
    }
}

int judgeStep(struct step *S,struct graphList *gList)//�жϲ��裨Ҫʹ����Ԫ�ض�����ѭ���������ҵ���С������
{
    int i;
    for (i=1;i<gList->vexNum;i++)//ѭ�����нڵ�
    {
        if (S->flags[i]==1)//���нڵ㱻��Ϊδ�ҵ����·��
        {
            return 1;//����1������ѭ��
        }
    }
    return 0;//����0������ѭ��
}

int findMinStepN(struct step *S,struct graphList *gList)//����С���������ѭ��Ҫ�����Ԫ�أ�
{
    int i,min=99999,n=-1;
    for (i=1;i<gList->vexNum;i++)//ѭ�����нڵ�
    {
        if (S->flags[i]==1)//������Ϊδ�ҵ����·��
        {
            if (S->stepN[i]<min)//������֪��СС�����滻
            {
                min=S->stepN[i];
                n=i;
            }
        }
    }
    return n;//���صõ�����С�����Ľڵ�ı��
}

void updateStepN(struct step *S,struct graphList *gList,int min)//���²���
{
    struct edgeNode *p;
    int minStepN=S->stepN[min];
    p=gList->vex[min].head;
    S->flags[min]=0;//���˴�ѭ����Ԫ����Ϊ������ģ��Ժ��ѭ���Ͳ��ٴ�������
    while (p)//ѭ���߱�ѭ��Ҫ�˴δ����Ԫ�أ�
    {
        if (S->flags[p->headVex]==1)//��δ�ҵ����·��������δ�����������֪������ѭ�����������Ԫ�رض����ҵ���С·���ģ�
        {
            if (p->weight+minStepN<S->stepN[p->headVex])//���µ��߷��Ĳ�������
            {
                S->stepN[p->headVex]=p->weight+minStepN;//�͸��µ��˽ڵ�Ĳ���
            }
        }
        else
        {
            if (S->flags[p->headVex]==-1)//���˽ڵ���·����
            {
                S->flags[p->headVex]=1;//�ŵ��´�ѭ����
                S->stepN[p->headVex]=p->weight+minStepN;//�µ��߷���·��������䲽��
            }
        }
        p=p->next;
    }
}

void print(struct step *S,struct graphList *gList)//�������
{
    int i;
    int nList[3000]={0};//����
    int noList[3000]={0};//�ڵ���
    for (i=1;i<gList->vexNum;i++)
    {
        if (S->flags[i]==-1)//����·�����������-1
        {
            nList[i]=-1;
        }
        else
        {
            nList[i]=S->stepN[gList->vex[i].vex-1];//������ǲ���
        }
        noList[i]=i+1;//�ڵ��Ÿ�ֵ
    }
    quicksort (nList,noList,gList->vexNum,1,gList->vexNum-1);//��������С�����ţ������֮�ı�
    for (i=1;i<gList->vexNum;i++)
    {
        if (nList[i]>0)//�������·�����
        {
            printf ("1 %d %d\n",noList[i],nList[i]);
        }
    }
    for (i=1;i<gList->vexNum;i++)
    {
        if (nList[i]==-1)//�������·�����
        {
            printf ("1 %d %d\n",noList[i],nList[i]);
        }
    }
}
void swap(int *a,int *b)//������ֵ
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void quicksort(int array1[],int array2[],int maxlen,int begin,int end)//��array1����ͬʱ�ı�array2
{
    int i,j;
    if(begin<end)
    {
        i=begin + 1;
        j=end;
        while(i<j)
        {
            if(array1[i]>array1[begin])
            {
                swap(&array1[i],&array1[j]);
                swap(&array2[i],&array2[j]);
                j--;
            }
            else
            {
                i++;
            }
        }
        if(array1[i]>=array1[begin])
        {
            i--;
        }
        swap(&array1[begin],&array1[i]);
        swap(&array2[begin],&array2[i]);
        quicksort(array1,array2,maxlen,begin,i);
        quicksort(array1,array2,maxlen,j,end);
    }
}

int main()
{
    struct graphList gList;
    struct step S;
    createNewGraphList(&gList);
    Dijkstra(&S,&gList);
     print (&S,&gList);

}
