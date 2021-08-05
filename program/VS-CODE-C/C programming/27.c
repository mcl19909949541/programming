#include<stdio.h>
int main()
{
    int n,x=1234,y=1,a,b,c,d,e,j,f,g,h,i;
    scanf("%d",&n);
    for(;x<49383&&y<98765;x++)
    {
        y=n*x;
        a=x/10000%10;
        b=x/1000%10;
        c=x/100%10;
        d=x/10%10;
        e=x%10;
        f=y/10000%10;
        g=y/1000%10;
        h=y/100%10;
        i=y/10%10;
        j=y%10;
        if(a==b||a==c||a==d||a==e||a==f||a==g||a==h||a==i||a==j) continue;
        if(b==c||b==d||b==e||b==f||b==g||b==h||b==i||b==j) continue;
        if(c==d||c==e||c==f||c==g||c==h||c==i||c==j) continue;
        if(d==e||d==f||d==g||d==h||d==i||d==j) continue;
        if(e==f||e==g||e==h||e==i||e==j) continue;
        if(f==g||f==h||f==i||f==j) continue;
        if(g==h||g==i||g==j) continue;
        if(h==i||h==j) continue;
        if(i==j) continue;
        printf("%05d/%05d=%d\n",y,x,n);


    }
    return 0;
}
