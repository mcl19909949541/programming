#include<stdio.h>
#include <sys/types.h>

int max(int a,int b)
{
    return a>b?a:b;

}
int a[20];
int f[20][20];
int main()
{
    int n,i,j,s=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(j=1;j<n;j++)
        f[0][0]=a[0],f[0][j]=f[0][j-1]*a[j];
        for(i=1;i<n;i++)
        {
            f[i][i-1]=1;
            for(j=i;j<n;j++)
                f[i][j]=f[i][j-1]*a[j];

        }
        for(i=0;i<n;i++)
            for(j=i;j<n;j++)
            s=max(s,f[i][j]);
        if(s==0)printf("-1\n");
        else printf("%d\n",s);
        return 0;

}
