#include<stdio.h>
int main()
{
    int a[100]={0};
    int n,m,i,j,k;
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<k;i++)
    {
        j=a[n-1];
        for(m=n-1;m>0;m--)
        {
            a[m]=a[m-1];
        }
        a[0]=j;
    }
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}
