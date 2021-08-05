#include<stdio.h>
int f[1000];
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        f[i]=a+b;
    }
    for(i=0;i<n;i++)
    {
        if(f[i]>100)f[i]=f[i]/10%10*10+f[i]%10,
        printf("%d\n",f[i]);
        else printf("%d\n",f[i]);

}
return 0;


}
