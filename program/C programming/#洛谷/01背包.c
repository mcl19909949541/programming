#include<stdio.h>
#define N 1005

int dp[N][N];  //dp[i][j]表示前i个物品，背包容量是j的情况下的最大价值。
int w[N];//记录每件物品的重量
int v[N];//记录每件物品的价值

int max( int a, int b)
    {
        return (a > b? a : b);
    }


int main()
{
	int n,m;
	scanf("%d %d",&n,&m);//n为物品，m为背包大小
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
