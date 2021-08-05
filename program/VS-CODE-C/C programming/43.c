#include<stdio.h>
int main()
{
    int a[100][100],n,i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
            for(j=0;j<n;j++)scanf("%d",&a[i][j]);
   for(i=0;i<n;i++)
   {
       for(j=0;j<=i;j++)printf("%d ",a[i][j]);
       for(j=i+1;j<n;j++)printf(" ");printf("\n");
   }
    return 0;

}
