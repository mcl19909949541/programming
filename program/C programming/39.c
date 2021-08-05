#include<stdio.h>
#include<math.h>
int getbit(int n ,int k)
{

scanf("%d%d",&n,&k);
    n=n>>k-1;
    return n;



}
int main()
{
    int n,k;



    printf("%d",getbit(n,k));
    return 0;
}
