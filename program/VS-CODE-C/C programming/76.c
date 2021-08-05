#include<stdio.h>
int main()
{
    int i,j,n;
    int a[100];
   scanf("%d\n",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        if(a[i]==a[j])a[j]=0,a[i]=0;
    for(i=0;i<n;i++)
        if(a[i]!=0) printf("%d ",a[i]);
        return 0;
}
