#include<stdio.h>
#include<math.h>
int main()
{
    int a=1;
    double b=1,pi=0,c=1;
    while(fabs(c)>=1e-6)
        pi=pi+c,b=b+2,a=-a,c=a/b;
    pi=pi*4;
    printf("%lf\n",pi);
    return 0;
}

