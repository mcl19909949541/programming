#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int coe1(int n,int k)/*求系数函数*/
{
    int n1=1,n2=1;
    if(k==0||n==k) return 1;
    for(int i=0; i<k; i++)
        n1=n1*(n-i);
    for(int i=1; i<k+1; i++)
        n2=n2*i;
    return (n1/n2);
}
int main()
{
    int a,b,n;
    scanf("%d",&n);
    for(int i=0; i<=n; i++)
    {

        if(i==0) printf("a^%d+",n);
        else if(i==n) printf("b^%d",n);
        else printf("%da^%db^%d+",coe1(n,i),n-i,i);

    }
    return 0;
}
