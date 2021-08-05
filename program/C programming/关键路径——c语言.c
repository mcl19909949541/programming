#include <stdio.h>
#define max 100
#define mc 10000000
#define false -1
#define ok 1
typedef struct{	//定义图
	char vex[max];
	int arc[max][max];
	int vexnum,arcnum;
}AmGraph;
int locatedv(AmGraph G,char a)	//输入的顶点找到位置
{
	int i=0;
	for(i=1;i<=G.vexnum;i++)
		{
			if(a==G.vex[i])
				return i;
		}
	return false;
}

void createG(AmGraph G)	//创建图
	{	int i,num,x,y,j;
		char a,b;
		printf("请输入顶点数和边数：");
		scanf("%d%d",&G.vexnum ,&G.arcnum);
		getchar();
		for(i=0;i<=G.vexnum;i++)		//对矩阵进行初始化
			for(j=0;j<=G.vexnum;j++)
				G.arc[i][j]=mc;
		printf("请输入顶点：");
		for(i=1;i<=G.vexnum;i++)
			{scanf("%c",&G.vex[i]);
			getchar();
			}
		printf("请输入边以及权重：");
		for(i=1;i<=G.arcnum;i++)
			{	scanf("%c",&a);
				getchar();
				scanf("%c%d",&b,&num);
				getchar();
				x=locatedv(G,a);
				y=locatedv(G,b);
				G.arc[x][y]=num;	//无向图
			}
		return ;
	}
int Topo_sort(AmGraph G,int s[])//拓扑排序
{
	int t[G.vexnum+1],i,j,count=0,count1=1;
	for(i=1;i<=G.vexnum;i++)
		t[i]=0;
	for(i=1;i<=G.vexnum;i++)
		{
			for(j=1;j<=G.vexnum;j++)
				{
					if(G.arc[j][i]!=mc)
						t[i]++;
				}
		}
for(i=1;i<=G.vexnum;i++)
		printf("%d ",t[i]);
		printf("\n");
	while(count<G.vexnum)
	{
		for(i=1;i<=G.vexnum;i++)
			{
				if(t[i]==0)
					{	s[count1]=i;
						count1++;
						t[i]--;
						for(j=1;j<=G.vexnum;j++)
							{
								if(G.arc[i][j]!=mc)
									t[j]--;
							}
						count++;
						break;
					}
			}
		/*	for(j=1;j<=G.vexnum;j++)
				printf("%d ",t[j]);
				printf("\n");*/
	}
	for(j=1,count=0;j<=G.vexnum;j++)
		{
			if(t[j]>0)
				count++;
		}
	if(count>0)
			return false;
	return ok;
}
void criticalPath(AmGraph G)
{	int s[G.vexnum+1],i,j,a[G.vexnum+1][G.vexnum+1];//存放拓扑排序的顺序存储的位置，按照拓扑排序序列做的矩阵
	int ve[G.vexnum+1],vl[G.vexnum+1],e[G.arcnum+1],l[G.arcnum+1];//事件最早发生时间，事件最晚发生时间，活动最早发生时间，活动最晚发生时间
	if(Topo_sort(G,s)!=1)
		{
			printf("不存在关键路径");
			return ;
		}
	else {
		/*for(i=1;i<=G.vexnum;i++)
			printf("%d ",s[i]);	*/
		ve[s[1]]=0;
		for(i=1;i<=G.vexnum;i++)//数组初始化
			{
			 ve[i]=0;
			}
		for(i=1;i<=G.vexnum;i++)//计算事件最早发生事件
			{
				for(j=1;j<=G.vexnum;j++)
					{
						if(G.arc[s[i]][j]!=mc)
							{
								if(ve[s[i]]+G.arc[s[i]][j]>ve[j])
									ve[j]=ve[s[i]]+G.arc[s[i]][j];
							}
					}
			}
		printf("\n事件最早发生时间为：");
		for(i=1;i<=G.vexnum;i++)
			printf("%d ",ve[i]);
		for(i=G.vexnum;i>=1;i--)	//初始化数组
			vl[i]=ve[s[G.vexnum]];
		for(i=G.vexnum;i>=1;i--)//计算事件最早发生事件
			{
				for(j=1;j<=G.vexnum;j++)
					{
						if(G.arc[j][s[i]]!=mc)
							{
								if(vl[s[i]]-G.arc[j][s[i]]<vl[j])
									vl[j]=vl[s[i]]-G.arc[j][s[i]];
							}
					}
			}
		printf("\n事件最迟发生时间为：");
		for(i=1;i<=G.vexnum;i++)
			printf("%d ",vl[i]);
		printf("\n关键路径为：");
		for(i=1;i<=G.vexnum;i++)
			{
				for(j=1;j<=G.vexnum;j++)
					{
						if(G.arc[s[i]][j]!=mc)
							{
								if(ve[s[i]]==vl[j]-G.arc[s[i]][j])
									{
										printf("(%c %c %d) ",G.vex[s[i]],G.vex[j],G.arc[s[i]][j]);
										i=j;//直接从找到的顶点往下找
									}
							}
					}
			}
	}
 }
int main()
{
	AmGraph G;
	createG(G);

	criticalPath(G);
	return 0;
 }
