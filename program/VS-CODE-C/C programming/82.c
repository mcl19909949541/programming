#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int p[10],i,cnt,n;
    scanf("%d",&n);
    void prime()
    {
        p[0]=1,p[1]=1;
        for(int i=2;i<10;i++)p[i]=i*p[i-1];
    }
    prime();
    for(i=0;i<pow(2,9);i++)
    {
        int t=i,cnt=9;
        int sum=0;
        while(cnt>0)
        {
            sum=sum+t%2*p[cnt];
            if(sum>=n)break;
            t=t/2;
            cnt--;
        }
        if(sum==n){printf("YES");break;}
    }
    if(i>=pow(2,9))printf("NO");
    return 0;

}
