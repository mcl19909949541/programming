#include <stdio.h>
#include <stdlib.h>

#define Min(a,b) ((a)<(b)?(a):(b))//手打min提高效率
#define Max(a,b) ((a)>(b)?(a):(b))//同上，切记括号千万不能漏


struct graphList
{
    int vexNum;
    int graph[120][120];
};

void createNewGraphList(struct graphList *gList,int Num)
{
    int i,j;
    int x,y;
    gList->vexNum=Num;
    for(i=1;i<=Num;i++)
        for(j=1;j<=Num;j++)//初始化
    {
       if(i!=j) gList->graph[i][j]=1000;
       else gList->graph[i][j]=0;
    }

    for(i=1;i<=Num-1;i++)
       {scanf("%d %d",&x,&y);
       gList->graph[x][y]=1;//父亲到孩子距离为1
       gList->graph[y][x]=2;//孩子到父亲距离为2
       }

}


void floydAlgorithm(struct graphList *gList)
{
      int v,w,k;
    //这里是弗洛伊德算法的核心部分
    //k为中间点
    for(k=1;k<=gList->vexNum;k++)
    {//v为起点
         for(v=1;v<=gList->vexNum;v++)
         { //w为终点
             for(w=1;w<=gList->vexNum;w++)
             {
                 if(gList->graph[v][w]>gList->graph[v][k]+gList->graph[k][w])
                 {
                     gList->graph[v][w]=gList->graph[v][k]+gList->graph[k][w];//更新最小路径
                 }
             }
         }
    }
}

void FindDepthAndWidth(struct graphList *gList)
{
     int maxsum=0,maxd=0,maxn=1;
     int b[1000];
    for(int i=2;i<=gList->vexNum;i++)
    {
        maxsum=Max(maxsum,gList->graph[1][i]);//深度
        b[gList->graph[1][i]]++;//同时统计每一层的节点数
        maxn=Max(maxn,gList->graph[i][1]);
    }
    for(int i=1;i<=maxn;i++)
        maxd=Max(maxd,b[i]);//宽度

    printf("%d\n%d\n",maxsum+1,maxd);
}

int main()
{
    struct graphList gList;
    int x,y,Num;
    scanf("%d",&Num);
    createNewGraphList(&gList,Num);
    floydAlgorithm(&gList);
    scanf("%d %d",&x,&y);
    FindDepthAndWidth(&gList);
    printf("%d",gList.graph[x][y]);
    return 0;
}
