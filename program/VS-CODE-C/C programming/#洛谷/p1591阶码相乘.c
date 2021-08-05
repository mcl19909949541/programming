#include<stdio.h>
#include<string.h>
int main()
{
    int flag,t,n,m,sum,j,k,i,jw,a[10000];
    scanf("%d",&t);
    for(k=0;k<t;k++)
    {    scanf("%d %d",&n,&flag);
        for(i=0;i<=10000;i++) a[i]=0;
        a[0]=1;
        for(j=2;j<=n;j++)
            {
                for(i=0;i<10000;i++) a[i]*=j;
            for(i=0;i<10000;i++)
            {
                if(a[i]>=10) { a[i+1]+=a[i]/10;a[i]%=10;}
            }
            }


        sum=0;
        for(i=0;i<10000;i++)
        {
            if(a[i]==flag) sum++;
        }
        printf("%d",sum);
        printf("\n");

    }
    return 0;
}
