#include<stdio.h>
#define N 1005

int dp[N][N];  //dp[i][j]��ʾǰi����Ʒ������������j������µ�����ֵ��
int w[N];//��¼ÿ����Ʒ������
int v[N];//��¼ÿ����Ʒ�ļ�ֵ

int max( int a, int b)
    {
        return (a > b? a : b);
    }


int main()
{
	int n,m;
	scanf("%d %d",&n,&m);//nΪ��Ʒ��mΪ������С
	for(int i=1;i<=n;i++)
		scanf("%d%d",&v[i],&w[i]);
		dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			dp[i][j]=dp[i-1][j];
			if(j>=v[i])
				dp[i][j]=max(dp[i][j],dp[i-1][j-v[i]]+w[i]);
		}
	}
	printf("%d",dp[n][m]);
	return 0;
}
