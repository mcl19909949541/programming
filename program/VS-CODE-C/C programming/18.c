#include<stdio.h>
int main()
{
    int a,b,t;
    scanf("%d %d",&a,&b);
    if(a>b)t=a,a=b,b=t;
    for(;a<b;a++){
        for(t=2;t<a;t++)if(a%t==0)break;
        if(t==a)printf("%d ",a);

    }
    return 0;
}
