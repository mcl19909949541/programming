#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;
const int maxn=105;
const int inf=0xfffff;
typedef struct Node//�ڽӱ��ͷ
{
    int val;
    int to;
    struct Node *next;
}Node,*List;

typedef struct dis//Դ�㵽������ľ���
{
    int index;
    int val;
}Distance;

Distance dis[maxn];
bool vis[maxn];

int n,m;
List G[maxn];

int cmp(struct dis a,struct dis b)//sort cmp ��С����
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
void Dijkstra(int s)//�ȳ�ʼ��dis���飬
{
    for (int i = 1; i <= n; i++)
    {
       dis[i].index=i;
       dis[i].val=inf;
       vis[i]=false;
    }
    int u=s;
    dis[s].val=0;
    while(!vis[u])//��u��ѡ����һ����С��Ȩֵ����ĵ�
    {
        vis[u]=true;//�������СΪ���ľ�������dis�Ѿ��������ˣ����ٷ���
        for (List k=G[u];k;k=k->next)
        {
            int v=k->to;//�������Ϊ���ĵ��ڽӱ�ĸ�������Ȩֵ
            if(!vis[u]&&dis[v].val>dis[u].val+k->val)//�Ƿ�����Ϊ����������ԭ�㵽δȷ��dis�ĵ����
            {
                dis[v].val=k->val+dis[u].val;//����dis
            }
            int tag=0xfffff;
            for (int i = 1; i <= n; i++)
            {
                if(!vis[i] && dis[i].val < tag)//ѡ����һ����Сֵ��
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