#include<stdio.h>
int main()
{
    double sum,ans;
    int n,v;
    int t[1001];
    scanf("%d",&n);
    int x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        t[i]=x*1001+i;
    }
    for(int i=1;i<=n;i++)
        if(t[i]>t[i+1]) v=t[i],t[i]=t[i+1],t[i+1]=t[i];
    for(int j=1;j<=n;j++)
    {

    }

}
