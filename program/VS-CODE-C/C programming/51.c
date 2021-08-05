#include<stdio.h>
#include<string.h>>
#include<math.h>
int main()
{
char a[1000];
    int i,U=0,S=0;
    gets(a);
    int cnt=strlen(a);
    for(int i=0;i<cnt;i++){
        if(a[i]=='U') U++;
            if(a[i]=='S') S++;
            }


    if(S>0) printf("WA\n");
    else
    if(fabs(1.0*U/cnt-0.5)<=0.003){
        int i;
        for(i=U;i>=1;i--)
            if(U%i==0&&cnt%i==0) break;
        printf("%d%d\n",U/i,cnt/i);
    }
    else printf("Fail\n");
    return 0;
}
