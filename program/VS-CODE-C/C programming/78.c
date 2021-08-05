#include<stdio.h>
int main()
{
    int a[100];
    int n,i,j,t,cnt;
    scanf("%d\n",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
        if(a[j]>a[j+1]) t=a[j],a[j]=a[j+1],a[j+1]=t,cnt++;
    printf("%d",cnt);
    return 0;
}
