#include<stdio.h>
int main()
{
    int n=1;
    double a1=1, a2=2,a3=3,sum=2;
    while(n<=19){
    a3=a1+a2;
    sum=sum+a3/a2;
    a1=a2;
    a2=a3;
    n++;}
    printf("%lf\n",sum);
    return 0;


}
