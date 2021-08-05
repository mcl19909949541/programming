#include<stdio.h>
int getfloor(double x)
{
    scanf("%lf",&x);
    if(x>=0) x=(int)x;
    else x=(int)x-1;
    return x;
}
int main()
{
    double x;
    printf("%d\n",getfloor(x));
    return 0;
}
