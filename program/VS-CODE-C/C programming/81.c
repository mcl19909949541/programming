#include<stdio.h>
int main()
{
    int a,b,s;
    scanf("%d%d",&a,&b);
    s=((a%9)*(b%9)%9);
    if(s!=0)printf("%d\n",s);
    else printf("%d\n",s);
    return 0;


}
