
#include <stdio.h>
#include <stdlib.h>

struct graphList
{
    int vexNum;
    int graph[120][120];
};

struct step
{
    int flags[3000];
    int stepN[3000];
};
//����������ֹ��warning
void createNewGraphList(struct graphList *gList);//��ʼ���ڽ�ͼ
void Dijkstra(struct step *gStep,struct graphList *gList);
void clearStep(struct step *gStep,struct graphList *gList);
void initializeStep(struct step *gStep,struct graphList *gList);
int judgeStep(struct step *gStep,struct graphList *gList);//�鿴�Ƿ�ȫ��ѭ����
int findMinStepN(struct step *gStep,struct graphList *gList);//���´�ѭ���Ĵ�����Ԫ��
void updateStepN(struct step *gStep,struct graphList *gList,int min);//���²���

void createNewGraphList(struct graphList *gList)//��ʼ���ڽ�ͼ
{
    int i,j;
    scanf ("%d",&(gList->vexNum));
    for (i=0;i<gList->vexNum;i++)
    {
        for (j=0;j<gList->vexNum;j++)
        {
            scanf ("%d",&(gList->graph[i][j]));
        }
    }
}
void Dijkstra(struct step *gStep,struct graphList *gList)
{
    int end,endStep;
    int min;
    clearStep(gStep,gList);
    initializeStep (gStep,gList);
    scanf ("%d",&end);
    endStep=gStep->stepN[end];//��ʼ�����ղ���
    while (judgeStep (gStep,gList))
    {
        min=findMinStepN (gStep,gList);
        updateStepN (gStep,gList,min);
        if (gStep->flags[end])//�����ڿɴ����ڻ�δ����
        {
            if (endStep!=gStep->stepN[end])//������ղ�����һ�£��������С·���ı�
            {
                endStep=gStep->stepN[end];//������С·��
                printf ("%d\n",min);//����˴��ĵ㣬Ϊʲô������ô������Ϊͼ��ͨ·�Ժ����ǵ�ǰ��������ͬ���ı���С·������һ����ض��˴��ĵ�����С·����
            }
        }
        else//���������������˳�ѭ����������
        {
            printf ("%d\n",min);
            break;
        }
    }
}

void clearStep(struct step *gStep,struct graphList *gList)
{
    for(int i=0;i<=gList->vexNum;i++)
    {
        gStep->flags[i]=-1;//-1ΪΪ�������û����ͨ������1Ϊ�ɴ���0Ϊ�Ѵ���
        gStep->stepN[i]=0;//��������
    }
}

void initializeStep(struct step *gStep,struct graphList *gList)
{
    int i;
    int start;
    scanf ("%d",&start);
    printf ("%d\n",start);
    for (i=0;i<gList->vexNum;i++)
    {
        if (gList->graph[start][i]!=10000)//����ͨ
        {
            gStep->flags[i]=1;//����ɴ���
            gStep->stepN[i]=gList->graph[start][i];//��ʼ������Ԫ���������Ĳ���
        }
    }
    gStep->flags[start]=-1;//��Ԫ�ر�Ϊδ����
    gStep->stepN[start]=0;
}

int judgeStep(struct step *gStep,struct graphList *gList)//�鿴�Ƿ�ȫ��ѭ����
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        if (gStep->flags[i]==1)
        {
            return 1;
        }
    }
    return 0;
}

int findMinStepN(struct step *gStep,struct graphList *gList)//���´�ѭ���Ĵ�����Ԫ��
{
    int i,min=99999,n=-1;
    for (i=0;i<gList->vexNum;i++)
    {
        if (gStep->flags[i]==1)
        {
            if (gStep->stepN[i]<min)
            {
                min=gStep->stepN[i];
                n=i;
            }
        }
    }
    return n;
}

void updateStepN(struct step *gStep,struct graphList *gList,int min)//���²���
{
    int i;
    int minStepN=gStep->stepN[min];
    gStep->flags[min]=0;//���˴δ���Ԫ�ر��Ϊ�Ѵ�������Ժ�ѭ�����ٴ���
    for (i=0;i<gList->vexNum;i++)
    {
        if (gStep->flags[i]==1)//���ʹ˴δ���Ԫ���������ҿɴ���
        {
            if (gStep->stepN[i]>gList->graph[min][i]+minStepN)//����ǰ��������֪��С����С
            {
                gStep->stepN[i]=gList->graph[min][i]+minStepN;//���²���
            }
        }
        else
        {
            if (gStep->flags[i]==-1)//���ʹ˴δ���Ԫ��������Ϊ����
            {
                gStep->flags[i]=1;//����
                gStep->stepN[i]=gList->graph[min][i]+minStepN;//���²���
            }
        }
    }
}


int main()
{
      struct graphList gList;
      struct step gStep;
      createNewGraphList (&gList);
      Dijkstra(&gStep,&gList);
      return 0;
}
