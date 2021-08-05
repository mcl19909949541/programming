
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
//函数申明防止报warning
void createNewGraphList(struct graphList *gList);//初始化邻接图
void Dijkstra(struct step *gStep,struct graphList *gList);
void clearStep(struct step *gStep,struct graphList *gList);
void initializeStep(struct step *gStep,struct graphList *gList);
int judgeStep(struct step *gStep,struct graphList *gList);//查看是否全部循环过
int findMinStepN(struct step *gStep,struct graphList *gList);//找下次循环的待处理元素
void updateStepN(struct step *gStep,struct graphList *gList,int min);//更新步数

void createNewGraphList(struct graphList *gList)//初始化邻接图
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
    endStep=gStep->stepN[end];//初始化最终步数
    while (judgeStep (gStep,gList))
    {
        min=findMinStepN (gStep,gList);
        updateStepN (gStep,gList,min);
        if (gStep->flags[end])//若是在可处理环节或未激活
        {
            if (endStep!=gStep->stepN[end])//如果最终步数不一致，则代表最小路径改变
            {
                endStep=gStep->stepN[end];//更新最小路径
                printf ("%d\n",min);//输出此处的点，为什么可以这么做？因为图的通路性和我们的前进放向相同，改变最小路径方向一次则必定此处的点在最小路径上
            }
        }
        else//处理过，则输出并退出循环结束程序
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
        gStep->flags[i]=-1;//-1为为激活（即还没有联通到），1为可处理，0为已处理
        gStep->stepN[i]=0;//步数清零
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
        if (gList->graph[start][i]!=10000)//若联通
        {
            gStep->flags[i]=1;//放入可处理
            gStep->stepN[i]=gList->graph[start][i];//初始化和首元素相连结点的步数
        }
    }
    gStep->flags[start]=-1;//首元素变为未激活
    gStep->stepN[start]=0;
}

int judgeStep(struct step *gStep,struct graphList *gList)//查看是否全部循环过
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

int findMinStepN(struct step *gStep,struct graphList *gList)//找下次循环的待处理元素
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

void updateStepN(struct step *gStep,struct graphList *gList,int min)//更新步数
{
    int i;
    int minStepN=gStep->stepN[min];
    gStep->flags[min]=0;//将此次处理元素标记为已处理过，以后循环不再处理
    for (i=0;i<gList->vexNum;i++)
    {
        if (gStep->flags[i]==1)//若和此次处理元素相连而且可处理
        {
            if (gStep->stepN[i]>gList->graph[min][i]+minStepN)//若当前步数比已知最小步数小
            {
                gStep->stepN[i]=gList->graph[min][i]+minStepN;//更新步数
            }
        }
        else
        {
            if (gStep->flags[i]==-1)//若和此次处理元素相连但为激活
            {
                gStep->flags[i]=1;//激活
                gStep->stepN[i]=gList->graph[min][i]+minStepN;//更新步数
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
