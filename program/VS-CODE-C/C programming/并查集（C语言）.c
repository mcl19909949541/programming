#include<stdio.h>
int c[100005]={0};
int get(int root)//找同一个根节点
{
    if(c[root]==root)//表示已找到
        return root;
    else
    {
        c[root]=get(c[root]);//递归，直到找到为止
        return c[root];
    }
}
void join(int a,int b)
{
    int t1,t2;//分别为两人的根节点
    t1=get(a);
    t2=get(b);
    if(t1!=t2)//判断这两个根节点是否在同一朋友圈
    {
        c[t2]=t1;
    }
    return;
}
int main()
{
    int n,m,i,a,b,sum;
    while(~scanf("%d%d",&n,&m))
    {
        sum=0;
        for(i=1;i<=n;i++)
            c[i]=i;
        while(m--)
        {
            scanf("%d%d",&a,&b);
            join(a,b);
        }
        for(i=1;i<=n;i++)
        {
            if(c[i]==i)
                sum++;
        }
        printf("%d\n",sum);
    }
    return 0;
}
