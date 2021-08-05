/*#include<stdio.h>
#include<string.h>
#define max 100
int main()
{
    char a[max],b[max];
    int c[max],aa[max],bb[max],len_a,len_b,i,j,n,len_c,cnt;
    gets(a);
    gets(b);
    len_a=strlen(a);
    len_b=strlen(b);
    len_c=(len_a>len_b?len_a:len_b);
    for(i=0;i<len_a;i++) aa[i]=a[len_a-i]-'0';
    for(i=0;i<len_b;i++) bb[i]=b[len_b-i]-'0';
    for(i=0;i<len_c+1;i++)
    {
        c[i]=aa[i]+bb[i];
        if(c[i]>=10) {aa[i+1]++;c[i]%=10;}
    }
    for(i=0;i<len_c+1;i++)
    {
        printf("%d",c[i]);
    }
    return 0;

}
*/


//大数加法2
#include<stdio.h>
#include<string.h>
#define M 100005
char s1[M],s2[M];
int a[M],b[M],c[M];
int main()
{
    int i,j,k,n,m;
    while(scanf("%s%s",s1,s2))
    {
        memset(c,0,sizeof(c));
        n=strlen(s1);
        m=strlen(s2);

 /* 把字符串s1和s2逆序用数字排列*/
        for(i=0; i<n; i++)
            a[i]=s1[n-i-1]-'0';
        for(i=0; i<m; i++)
            b[i]=s2[m-i-1]-'0';
        /*加运算*/
        if(n>m) k=n;
        else k=m;
        for(i=0; i<=k; i++)
        {
            c[i]+=a[i]+b[i];
            if(c[i]>9)
            {
                c[i+1]++;
                c[i]%=10;
            }
        }
        /*去除前导0*/
        i=k;
        while(c[i]==0) i--;
  /*判断两个非负数之和是否为0，以及逆序打印c[]*/
        if(i<0) printf("0");
        else
        {
            for(; i>=0; i--)
                printf("%d",c[i]);
        }
        printf("\n");
    }
    return 0;
}
