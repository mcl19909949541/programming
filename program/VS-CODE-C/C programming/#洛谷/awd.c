#include<stdio.h>
int B,P,K;
int qpow(int base,int p)
{
    if(p==1)
    {
        return base;
    }
    else if(p==0)
    {
        return 1;
    }
    else
    {
        int ans=qpow(base,p/2)%K;
        int ansl=(ans%K+ans%K)%K;
        if(p%2==1){
            ansl=(ansl%K+base%K)%K;
        }
        ansl=ansl%K;
        return ansl;
    }
}
int main()
{
    scanf("%11d%11d%11d",&B,&P,&K);
    int ans=qpow(B,P);
    ans=ans%K;
    printf("%11d^%11d mod %11d=%11d",B,P,K,ans);
    return 0;
}
