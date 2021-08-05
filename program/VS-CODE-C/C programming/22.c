#include<stdio.h>
int main()
{
    int x=192,y,z,a,b,c,d,e,f,g,h,i;
    for(;x<328;x++)
    {
        y=2*x;
        z=3*x;
        a=x/100%10;
        b=x/10%10;
        c=x%10;
        d=y/100%10;
        e=y/10%10;
        f=y%10;
        g=z/100%10;
        h=z/10%10;
        i=z%10;
        if(a==b||a==c||a==d||a==e||a==f||a==g||a==h||a==i||a==0) continue;
        if(b==c||b==d||b==e||b==f||b==g||b==h||b==i||b==0) continue;
        if(c==d||c==e||c==f||c==g||c==h||c==i||c==0) continue;
        if(d==e||d==f||d==g||d==h||d==i||d==0) continue;
        if(e==f||e==g||e==h||e==i||e==0) continue;
        if(f==g||f==h||f==i||f==0) continue;
        if(g==h||g==i||g==0) continue;
        if(h==i||h==0) continue;
        printf("%d %d %d\n",x,y,z);


    }
    return 0;
}
