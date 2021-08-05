#include<stdio.h>
#define min(a,b)  (a>b?b:a)
int  n,a,b,ans=1000;
int to[200];
int vis[200];
void dfs(int now,int sum)
{
    if(now==b) ans=min(ans,sum);
    if(sum>ans) return ;
    vis[now]=1;
    if(now+to[now]<=n&&!vis[now+to[now]]) dfs(now+to[now],sum+1);
   if(now-to[now]<=n&&!vis[now-to[now]]) dfs(now-to[now],sum+1);
   vis[now]=0;
}
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++)
    scanf("%d",&to[i]);
    vis[a]=1;
    dfs(a,0);
    if(ans!=1000) printf("%d",ans);
        else printf("-1");
    return 0;
}

