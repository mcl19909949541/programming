#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 1000
int main()
{
    char s1[M],s2[M],s[M];
    int a[M],b[M],c[M];
    int i ,j,m,n,k;
    while(scanf("%s %s",s1,s2))
    {
        memset(c,0,sizeof(c)-1);
        n=strlen(s1);
        m=strlen(s2);
        k=n+m;
        for(i=0;i<n;i++) a[i]=s1[n-1-i]-'0';
        for(i=0;i<m;i++) b[i]=s2[n-1-i]-'0';
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            c[i+j]=a[i]*b[j];
        for(i=0;i<=k;i++)
        {
            if(c[i]>=10)
            {
                c[i+1]+=c[i]/10;
                c[i]%=10;
            }
        }
        i=k;
        while(c[i]==0)i--;
        if(i<0) printf("0");
        for(;i>=0;i--)
            printf("%d",c[i]);


    }
    return 0;
}
