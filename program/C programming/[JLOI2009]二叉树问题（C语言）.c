#include <stdio.h>
#include <stdlib.h>

#define Min(a,b) ((a)<(b)?(a):(b))//�ִ�min���Ч��
#define Max(a,b) ((a)>(b)?(a):(b))//ͬ�ϣ��м�����ǧ����©


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
        for(j=1;j<=Num;j++)//��ʼ��
    {
       if(i!=j) gList->graph[i][j]=1000;
       else gList->graph[i][j]=0;
    }

    for(i=1;i<=Num-1;i++)
       {scanf("%d %d",&x,&y);
       gList->graph[x][y]=1;//���׵����Ӿ���Ϊ1
       gList->graph[y][x]=2;//���ӵ����׾���Ϊ2
       }

}


void floydAlgorithm(struct graphList *gList)
{
      int v,w,k;
    //�����Ǹ��������㷨�ĺ��Ĳ���
    //kΪ�м��
    for(k=1;k<=gList->vexNum;k++)
    {//vΪ���
         for(v=1;v<=gList->vexNum;v++)
         { //wΪ�յ�
             for(w=1;w<=gList->vexNum;w++)
             {
                 if(gList->graph[v][w]>gList->graph[v][k]+gList->graph[k][w])
                 {
                     gList->graph[v][w]=gList->graph[v][k]+gList->graph[k][w];//������С·��
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
        maxsum=Max(maxsum,gList->graph[1][i]);//���
        b[gList->graph[1][i]]++;//ͬʱͳ��ÿһ��Ľڵ���
        maxn=Max(maxn,gList->graph[i][1]);
    }
    for(int i=1;i<=maxn;i++)
        maxd=Max(maxd,b[i]);//���

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
