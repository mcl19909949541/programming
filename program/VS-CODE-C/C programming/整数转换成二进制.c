#include<stdio.h>
int main()
{
    int num[20],n,i,j;
    scanf("%d",&n);
   do{
    i++;
    num[i]=n%2;
    n=n/2;
   }while(n!=0);
    for(j=i;j>0;j--)
        printf("%d ",num[j]);
    return 0;
}
