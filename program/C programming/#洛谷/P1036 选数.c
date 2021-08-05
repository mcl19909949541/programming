#include<stdio.h>
#define max(a,b) (((a)>(b))?a:b)
int main()
{
    int N,M;
    char a[100][100];
    int i,j,k,i1,i2,sum=0,MAX=0;
    scanf("%d%d",&N,&M);
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
        scanf("%c",&a[i][j]);
    for( i1=0;i1<N-2;i1++)
    {
        sum=0;
        for(i=0;i<i1;i++)
            for(j=0;j<M;j++)
            if(a[i][j]=='W') sum++;
        for( i2=i1+1;i2<N-1;i2++)
        {
            for(i=i1+1;i<i2;i++)
                for(j=0;j<M;j++)
                if(a[i][j]=='B') sum++;
        }
        for(i=i2;i<N;i++)
           for(j=0;j<M;j++)
            if(a[i][j]=='R') sum++;

        MAX=max(MAX,sum);
    }
    printf("%d",MAX);
    return 0;
}
