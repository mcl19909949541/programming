#include<stdio.h>
int main()/*������ⲻ̫�������������д��ͦ����*/
{
    int  m,n,x,i,sum=0;
    while(scanf("%d",&m)!=EOF)
    { sum=0;
        for(i=1;i<=m;i++) sum+=i;
        printf("%d\n",sum);

    }
    return 0;
}
