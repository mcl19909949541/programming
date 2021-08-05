#include<stdio.h>
int main()/*和你的题不太相符，不过这样写还挺好玩*/
{
    int  m,n,x,i,sum=0;
    while(scanf("%d",&m)!=EOF)
    { sum=0;
        for(i=1;i<=m;i++) sum+=i;
        printf("%d\n",sum);

    }
    return 0;
}
