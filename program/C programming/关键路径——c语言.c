#include <stdio.h>
#define max 100
#define mc 10000000
#define false -1
#define ok 1
typedef struct{	//����ͼ
	char vex[max];
	int arc[max][max];
	int vexnum,arcnum;
}AmGraph;
int locatedv(AmGraph G,char a)	//����Ķ����ҵ�λ��
{
	int i=0;
	for(i=1;i<=G.vexnum;i++)
		{
			if(a==G.vex[i])
				return i;
		}
	return false;
}

void createG(AmGraph G)	//����ͼ
	{	int i,num,x,y,j;
		char a,b;
		printf("�����붥�����ͱ�����");
		scanf("%d%d",&G.vexnum ,&G.arcnum);
		getchar();
		for(i=0;i<=G.vexnum;i++)		//�Ծ�����г�ʼ��
			for(j=0;j<=G.vexnum;j++)
				G.arc[i][j]=mc;
		printf("�����붥�㣺");
		for(i=1;i<=G.vexnum;i++)
			{scanf("%c",&G.vex[i]);
			getchar();
			}
		printf("��������Լ�Ȩ�أ�");
		for(i=1;i<=G.arcnum;i++)
			{	scanf("%c",&a);
				getchar();
				scanf("%c%d",&b,&num);
				getchar();
				x=locatedv(G,a);
				y=locatedv(G,b);
				G.arc[x][y]=num;	//����ͼ
			}
		return ;
	}
int Topo_sort(AmGraph G,int s[])//��������
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
{	int s[G.vexnum+1],i,j,a[G.vexnum+1][G.vexnum+1];//������������˳��洢��λ�ã��������������������ľ���
	int ve[G.vexnum+1],vl[G.vexnum+1],e[G.arcnum+1],l[G.arcnum+1];//�¼����緢��ʱ�䣬�¼�������ʱ�䣬����緢��ʱ�䣬�������ʱ��
	if(Topo_sort(G,s)!=1)
		{
			printf("�����ڹؼ�·��");
			return ;
		}
	else {
		/*for(i=1;i<=G.vexnum;i++)
			printf("%d ",s[i]);	*/
		ve[s[1]]=0;
		for(i=1;i<=G.vexnum;i++)//�����ʼ��
			{
			 ve[i]=0;
			}
		for(i=1;i<=G.vexnum;i++)//�����¼����緢���¼�
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
		printf("\n�¼����緢��ʱ��Ϊ��");
		for(i=1;i<=G.vexnum;i++)
			printf("%d ",ve[i]);
		for(i=G.vexnum;i>=1;i--)	//��ʼ������
			vl[i]=ve[s[G.vexnum]];
		for(i=G.vexnum;i>=1;i--)//�����¼����緢���¼�
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
		printf("\n�¼���ٷ���ʱ��Ϊ��");
		for(i=1;i<=G.vexnum;i++)
			printf("%d ",vl[i]);
		printf("\n�ؼ�·��Ϊ��");
		for(i=1;i<=G.vexnum;i++)
			{
				for(j=1;j<=G.vexnum;j++)
					{
						if(G.arc[s[i]][j]!=mc)
							{
								if(ve[s[i]]==vl[j]-G.arc[s[i]][j])
									{
										printf("(%c %c %d) ",G.vex[s[i]],G.vex[j],G.arc[s[i]][j]);
										i=j;//ֱ�Ӵ��ҵ��Ķ���������
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
