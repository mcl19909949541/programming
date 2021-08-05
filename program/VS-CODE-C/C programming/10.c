#include<stdio.h>
int main()
{
    double  x,y;
    scanf("%lf,%lf",&x,&y);
    if((x-2)*(x-2)+(y-2)*(y-2)<=1) printf("10");
    else if((x-2)*(x-2)+(y+2)*(y+2)<=1)printf("10");
    else if((x+2)*(x+2)+(y-2)*(y-2)<=1)printf("10");
    else if((x-2)*(x-2)+(y+2)*(y+2)<=1)printf("10");
        else if((x+2)*(x+2)+(y+2)*(y+2)<=1)printf("10");
    else printf("10");
    return 0;
}
