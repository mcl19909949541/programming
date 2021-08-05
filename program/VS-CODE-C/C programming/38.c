#include<stdio.h>
int sum(int n)
{
    int s=0;
    for(int i=1; i<n; i++)
        if(n%i==0)
            s+=i;
    return s;
}
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    if(sum(m)==n&&sum(n)==m)
        printf("YES");
    else
        printf("NO");
    return 0;
}


