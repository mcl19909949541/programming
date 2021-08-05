#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;
const int maxn=105;
const int inf=0xfffff;
typedef struct Node//邻接表表头
{
    int val;
    int to;
    struct Node *next;
}Node,*List;

typedef struct dis//源点到其他点的距离
{
    int index;
    int val;
}Distance;

Distance dis[maxn];
bool vis[maxn];

int n,m;
List G[maxn];

int cmp(struct dis a,struct dis b)//sort cmp 从小到大
{
    if(a.val==b.val) return a.index < b.index;
    return a.val<b.val;
}
void InitGraph(List *G)
{
    for (int i = 1; i <=n; i++)
    {
        G[i]=(List)malloc(sizeof(Node));
        G[i]=NULL;
    }  
}
void addedge(int from,int to,int val)
{
    List p = (List)malloc(sizeof(Node));
    p->to = to;
    p->val = val;
    p->next = G[from];
    G[from] = p;

}
void Dijkstra(int s)//先初始化dis数组，
{
    for (int i = 1; i <= n; i++)
    {
       dis[i].index=i;
       dis[i].val=inf;
       vis[i]=false;
    }
    int u=s;
    dis[s].val=0;
    while(!vis[u])//用u来选择下一个最小的权值距离的点
    {
        vis[u]=true;//以这个最小为中心就算他的dis已经定下来了，不再访问
        for (List k=G[u];k;k=k->next)
        {
            int v=k->to;//以这个点为中心的邻接表的各个弧的权值
            if(!vis[u]&&dis[v].val>dis[u].val+k->val)//是否能因为这个点可以让原点到未确定dis的点更近
            {
                dis[v].val=k->val+dis[u].val;//更新dis
            }
            int tag=0xfffff;
            for (int i = 1; i <= n; i++)
            {
                if(!vis[i] && dis[i].val < tag)//选择下一个最小值点
                {
                    tag = dis[i].val;
                    u = i;
                }
            }
        }       
    }
}

int main()
{
    int u,v,e;
    scanf("%d %d",&n,&m);
    InitGraph(G);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&e);
        addedge(u,v,e);
    }
    int s = 1;
    Dijkstra(s);
    sort(dis+2,dis+n,cmp);
    for(int i=2;i<=n;i++)
    {
        if(dis[i].val != 0xfffff)
        printf("%d %d %d\n",s,dis[i].index,dis[i].val);
        else 
        printf("%d %d -1\n",s,dis[i].index);
    }
    return 0;
    
}