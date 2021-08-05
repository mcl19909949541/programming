#include<stdio.h>
int main()
{
    int a,b,i,j,k,cnt=0;
    scanf("%d%d",&a,&b);
    for(i=1;i<=a;i++)
    {
        k=i;
        for(;k!=0;)
        {
            j=k%10;
            k=k/10;
            if(j==b) cnt++;

        }
    }
    printf("%d",cnt);
    return 0;
}
