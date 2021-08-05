#include<stdio.h>
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int N,n[105],c[105],v[105],dp[105][105],p=0,V;
   scanf("%d%d",&N,&V);
    for(int i=1;i<=N;i++)
    {
         scanf("%d%d%d",&v[i],&c[i],&n[i]);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=V;j>=0;j--)
        {
            for(int k=0;k<=n[i];k++)
            {
                if(j>=k*v[i])
                {
                    dp[i][j]=max(dp[i][j],dp[i-1][j-k*v[i]]+k*c[i]);
                }
            }
        }
    }
    p=dp[N][V];
    printf("%d",p);
}

