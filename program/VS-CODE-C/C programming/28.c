#include<stdio.h>
int main()
{
    int x,y,a,b,L;
    double t;
    scanf("%d%d%d%d%d",&x,&y,&a,&b,&L);
    if(a==b) printf("impossible\n");
    else if(x>y){
        if(a>b)y=L-x+y,t=(double)y/(a-b);
        else y=x-y,t=(double)y/(b-a);
        if((int)t==t)printf("%d\n",(int)t);
        else printf("%lf\n",t);

    }
    else{
        if(a>b)y=y-x,t=(double)y/(a-b);
        else y=L-y+x,t=(double)y/(b-a);
        if((int)t==t)printf("%d\n",(int)t);
        else printf("%lf\n",t);

    }
    return 0;
}
