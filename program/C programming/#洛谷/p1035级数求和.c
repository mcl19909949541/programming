#include<stdio.h>
double fun(double sum,double n,double k)
{
     sum+=1/n;
     if(sum<=k) return fun(sum,n+1,k);
     return n;
}
int main()
{
    double k,n=1.00,sum=0;
    scanf("%lf",&k);
    printf("%lf",fun(sum,n,k));
    return 0;


}
