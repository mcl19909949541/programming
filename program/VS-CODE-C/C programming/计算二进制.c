#include<stdio.h>
int b[100];
int i=0;
void zhuanhuan(int a)
{
    int j,k;
    while(a!=0)
    {
        b[i]=a%2;
        i++;
        a/=2;
    }
}
int main()
{
    int a;
    scanf("%d",&a);
    zhuanhuan(a);
i--;
    for(;i>=0;i--)
        printf("%d",b[i]);
    return 0;
}
