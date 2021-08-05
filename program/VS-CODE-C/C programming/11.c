#include<stdio.h>
int main()
{
    double l,x,r;
    scanf("%lf %lf",&l,&r);
    while((2*l*l*l-4*l*l+3*l-6)!=0&&(2*r*r*r-4*r*r+3*r-6)!=0){
        x=(l+r)/2;
        if((2*l*l*l-4*l*l+3*l-6)*(2*x*x*x-4*x*x+3*x-6)<=0)
            r=x;
            else l=x;
    }
    if(2*l*l*l-4*l*l+3*l-6) printf("%.2lf",l);
    else printf("%.2lf",r);
    return 0;

}
