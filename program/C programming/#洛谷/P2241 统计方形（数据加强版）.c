#include<stdio.h>
#define min(x,y) ((x>y?y:x))
int main()
{
    int n,m,i,j,sum1=0,sum2=0;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            sum1+=j*i;
            sum2+=min(i,j);
        }
    }

    printf("%d %d",sum2,sum1-sum2);
    return 0;
}
