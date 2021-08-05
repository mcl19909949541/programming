#include<stdio.h>
int main()
{
    char xxx;
    int a,b,c,d,m,n,i,f;
    scanf("%d/%d%c%d/%d",&c,&a,&xxx,&d,&b);
    if(xxx=='+')f=1;
    if(xxx=='-')f=-1;
    m=b*c+f*a*d;
    n=a*b;
    if(m==0)printf("0");
    else
    {
        for(i=((m>n)?n:m); i>=2; i--)
        {
            if(m%i==0&&n%i==0)break;}

            m=m/i;
            n=n/i;
            if(m>0)printf("%d/%d",m,n);

        }

        return 0;
    }

