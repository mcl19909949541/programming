#include<stdio.h>
int main()
{
    int i,j,N,sum=0;
    scanf("%d",&N);

    for(j=1;j<N;j++)
        for(i=1;i<=j;i++)
    {
        if(N==i*j+j+i)sum++;
    }
printf("%d",sum);
    return 0;

}
