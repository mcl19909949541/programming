#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//定义一个结点
//边表
struct edgeNode
{
    int headVex;//相邻顶点字段
    int weight;//权重
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

struct step{
    int flags[1000];
    int stepN[1000];
};

//函数申明防止报warning

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



void createNewGraphList (struct graphList *gList)//创建图
{
    scanf ("%d%d",&(gList->vexNum),&(gList->edgeNum));

    clearVexNodes (gList);//注意此处不加&

    int i,vex;
    for (i=0;i<gList->edgeNum;i++)//添加结点
    {
        scanf ("%d",&vex);
        gList->vex[vex-1].vex=vex;
        createNewEdgeNode (vex-1,gList);//新建结点
    }
}
void createNewEdgeNode (int n,struct graphList *gList)//新建结点
{
    struct edgeNode *p,*q;
    int headVex;
    p=(struct edgeNode *)malloc(sizeof(struct edgeNode));
    scanf ("%d",&headVex);//输入尾
    p->headVex=headVex-1;//逐一此处，因为我们以0为边表第一个位置，所以要-1
    scanf ("%d",&(p->weight));//输入权重
    p->next=NULL;
    //此用尾插
    if (gList->vex[n].head==NULL)//若边表本来无元素
    {
        gList->vex[n].head=p;
    }
    else//边表有元素，将操作位置移动到此边表尾部
    {
        q=gList->vex[n].head;
        while (q->next)
        {
            q=q->next;
        }
        q->next=p;//尾插
    }
}



void clearVexNodes (struct graphList *gList)//图的初始化
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        gList->vex[i].vex=0;//边表信息设为0
        gList->vex[i].head=NULL;//边表结点设为NULL
    }
}


void Dijkstra(struct step *S,struct graphList *gList)//算法主体
{
    int min;
    clearStep (S,gList);//初始化，即清空步数
    initializeStep (S,gList);//初始化
    while (judgeStep (S,gList))//判断步骤
    {
        min=findMinStepN (S,gList);//找最小步
        updateStepN (S,gList,min);//更新步数

    }
}
void clearStep(struct step *S,struct graphList *gList)//初始化，即清空步数
{
    int i;
    for (i=0;i<gList->vexNum;i++)
    {
        S->flags[i]=-1;//-1无路，0以找到最短路径，1未找到最短路径
        S->stepN[i]=0;//到此节点的步数为0
    }
}

void initializeStep(struct step *S,struct graphList *gList)//初始化，即把首元素放进循环开始判断
{
    struct edgeNode *p;
    p=gList->vex[0].head;
    while (p)//循环边表
    {
        S->flags[p->headVex]=1;//设置为未找到最短路径
        S->stepN[p->headVex]=p->weight;//设置到此节点步数
        p=p->next;
    }
}

int judgeStep(struct step *S,struct graphList *gList)//判断步骤（要使所有元素都进行循环并处理找到最小步数）
{
    int i;
    for (i=1;i<gList->vexNum;i++)//循环所有节点
    {
        if (S->flags[i]==1)//若有节点被设为未找到最短路径
        {
            return 1;//返回1，继续循环
        }
    }
    return 0;//返回0，结束循环
}

int findMinStepN(struct step *S,struct graphList *gList)//找最小步（找这次循环要处理的元素）
{
    int i,min=99999,n=-1;
    for (i=1;i<gList->vexNum;i++)//循环所有节点
    {
        if (S->flags[i]==1)//若被设为未找到最短路径
        {
            if (S->stepN[i]<min)//若比已知最小小，就替换
            {
                min=S->stepN[i];
                n=i;
            }
        }
    }
    return n;//返回得到的最小步数的节点的编号
}

void updateStepN(struct step *S,struct graphList *gList,int min)//更新步数
{
    struct edgeNode *p;
    int minStepN=S->stepN[min];
    p=gList->vex[min].head;
    S->flags[min]=0;//将此次循环的元素列为处理过的，以后的循环就不再处理它）
    while (p)//循环边表（循环要此次处理的元素）
    {
        if (S->flags[p->headVex]==1)//若未找到最短路径（即还未处理过，我们知道进入循环，处理过的元素必定是找到最小路径的）
        {
            if (p->weight+minStepN<S->stepN[p->headVex])//若新的走法的步数较少
            {
                S->stepN[p->headVex]=p->weight+minStepN;//就更新到此节点的步数
            }
        }
        else
        {
            if (S->flags[p->headVex]==-1)//若此节点无路到达
            {
                S->flags[p->headVex]=1;//放到下次循环里
                S->stepN[p->headVex]=p->weight+minStepN;//新的走法有路到达，更新其步数
            }
        }
        p=p->next;
    }
}

void print(struct step *S,struct graphList *gList)//输出步骤
{
    int i;
    int nList[3000]={0};//步数
    int noList[3000]={0};//节点编号
    for (i=1;i<gList->vexNum;i++)
    {
        if (S->flags[i]==-1)//若无路到达，步数就是-1
        {
            nList[i]=-1;
        }
        else
        {
            nList[i]=S->stepN[gList->vex[i].vex-1];//否则就是步数
        }
        noList[i]=i+1;//节点编号赋值
    }
    quicksort (nList,noList,gList->vexNum,1,gList->vexNum-1);//将步数从小到大排，编号随之改变
    for (i=1;i<gList->vexNum;i++)
    {
        if (nList[i]>0)//先输出有路到达的
        {
            printf ("1 %d %d\n",noList[i],nList[i]);
        }
    }
    for (i=1;i<gList->vexNum;i++)
    {
        if (nList[i]==-1)//再输出无路到达的
        {
            printf ("1 %d %d\n",noList[i],nList[i]);
        }
    }
}
void swap(int *a,int *b)//交换数值
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void quicksort(int array1[],int array2[],int maxlen,int begin,int end)//以array1排序，同时改变array2
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
