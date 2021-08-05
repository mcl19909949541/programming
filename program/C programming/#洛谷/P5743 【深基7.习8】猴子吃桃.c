#include<stdio.h>
int main()
{
    int i,j,n,cnt=1;
    scanf("%d",&n);
    for(i=1;i<n;i++)
    {
        cnt+=1;
        cnt*=2;
    }
    printf("%d",cnt);
    return 0;
}
